// server instance: linux_sockets server
// client instance: linux_sockets client

#include <iostream>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <cerrno>
#include <cstdlib>
#include <cmath>
#include <csignal>              // necessary for native Linux build
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <boost/shared_ptr.hpp>
using namespace std;

const char* HOST = "localhost";
static unsigned short PORT = 57767;
const char* MSG = "gopa";

#define BUF ostringstream buf; buf
#define BUF_STR buf.str()

class Socket {
protected:
    int _handle;
    sockaddr_in _addr;          // needed because we are setting some common parameters in constructor
    static bool _exit;
public:
    Socket()
            : _handle(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)), _addr() {
        int optval = 1;
        setsockopt(_handle, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        setsockopt(_handle, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(PORT);
    }
    virtual ~Socket() {
        shutdown(_handle, SHUT_RDWR);
        close(_handle);
    }
    virtual void run() = 0;
    static void exit_command(int sig_val) {
        cout << "received signal | sig_val: " << sig_val << endl;       // only SIGINT
        if (sig_val == SIGINT) {                                        // only SIGINT
            _exit = true;
        }
    }
};
bool Socket::_exit = false;

class ServerSocket : public Socket {
public:
    ServerSocket() {
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        fcntl(_handle, F_SETFL, fcntl(_handle, F_GETFL) | O_NONBLOCK);

        int bind_res = bind(_handle, reinterpret_cast<const sockaddr*>(&_addr), sizeof(_addr));
        if (bind_res < 0) {
            BUF << "bind function signalled error | ret: " << bind_res;
            throw runtime_error(BUF_STR);
        }
    }
    int wait_for_client() {
        char str_addr_inc[INET_ADDRSTRLEN];
        sockaddr_in addr_inc = {};
        socklen_t addr_len = sizeof(addr_inc);

        // waiting for connection
        listen(_handle, 256);

        cout << "waiting for client to connect..." << endl;
        int client_desc = -1;
        while (client_desc == -1) {
            if (_exit) {
                return -1;
            }
            client_desc = accept(_handle, reinterpret_cast<sockaddr*>(&addr_inc), &addr_len);
            if (client_desc == -1 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
                BUF << "accept function signalled error | errno: " << strerror(errno) << endl;
                throw runtime_error(BUF_STR);
            } else if (client_desc >= 0) {
                inet_ntop(AF_INET, &addr_inc.sin_addr, str_addr_inc, INET_ADDRSTRLEN);
                cout << "client connected | host: " << str_addr_inc << ", port: " << ntohs(addr_inc.sin_port) << endl;
            } else {
                sleep(1);
            }
        }
        return client_desc;
    }
    void run() {
        // polling socket
        pollfd poll_data = {};
        poll_data.fd = wait_for_client();     // we should operate with socket that we get by accept function
        poll_data.events = POLLIN | POLLPRI;
        int count = 0;
        static const size_t BUF_SIZE = 1000;
        char sckt_buf[BUF_SIZE];
        
        while (!_exit) {
            int poll_ret = poll(&poll_data, 1, 10000);
            if (poll_ret == -1) {
                BUF << "poll signals error condition | errno: " << strerror(errno) << endl;
                throw runtime_error(BUF_STR);
            }
            if (poll_data.revents & POLLIN) {
                ioctl(poll_data.fd, FIONREAD, &count);
                if (count == 0) {
                    cout << "client disconnected..." << endl;
                    poll_data.fd = wait_for_client();
                } else if (count > BUF_SIZE - 1) {
                    BUF << "read buffer overflow | BUF_SIZE: " << BUF_SIZE << ", ioctl_cnt: " << count << endl;
                    throw runtime_error(BUF_STR);
                } else if (count > 0) {
                    ssize_t read_cnt = read(poll_data.fd, sckt_buf, count);
                    sckt_buf[read_cnt] = 0;
                    cout << "received data | str: " << sckt_buf << endl;
                }
            } else if (poll_data.revents & POLLPRI || poll_data.revents & POLLERR ||
                       poll_data.revents & POLLHUP || poll_data.revents & POLLNVAL) {
                BUF << "poll signals error condition | poll_data.revents: " << poll_data.revents << endl;
                throw runtime_error(BUF_STR);
            }
            sleep(1);
        }
    }
};

class ClientSocket : public Socket {
public:
    ClientSocket() {
        hostent* hst = gethostbyname(HOST);
        if (!hst) {
            BUF << "gethostbyname signalled error | host: " << HOST << endl;
            throw runtime_error(BUF_STR);
        }

        memcpy(&_addr.sin_addr, hst->h_addr, hst->h_length);
        int conn_ret = connect(_handle, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
        if (conn_ret == -1) {
            BUF << "connect signals error | host: " << HOST << ", port: " << PORT << ", msg: "
                << strerror(errno) << endl;
            throw runtime_error(BUF_STR);
        }
    }
    void run() {
        srand(time(NULL));
        while (!_exit) {
            int dice = static_cast<int>(trunc(rand() * 10.0 / RAND_MAX));
            if (dice == 0) {
                write(_handle, MSG, strlen(MSG));
                cout << "written data to socket | str: " << MSG << ", len: " << strlen(MSG) << endl;
            }
            sleep(1);
        }
    }
};

int main(int argc, char* argv[]) {
    static const string SERV = string("server"),
                        CLNT = string("client");


    try {
        // when running in VSCode debugger it adds 2>CON 1>CON <CON to command
        if (argc < 2 || (argv[1] != SERV && argv[1] != CLNT)) {
            BUF << "wrong arguments | only argument should be either 'server' or 'client'" << endl;
            throw runtime_error(BUF_STR);
        }

        boost::shared_ptr<Socket> sckt;
        if (argv[1] == SERV) {
            sckt.reset(new ServerSocket());
        } else if (argv[1] == CLNT) {
            sckt.reset(new ClientSocket());
        }
        signal(SIGINT, Socket::exit_command);
        sckt->run();
    } catch (const runtime_error& err) {
        cerr << err.what() << endl;
    }
}
