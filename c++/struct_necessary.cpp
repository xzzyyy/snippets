#include <sys/time.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	struct timeval tv;
	/* struct */ timezone tz;
	gettimeofday(&tv, &tz);
	cout << tv.tv_sec << endl;
	cout << tv.tv_usec << endl;
}