#include <utility>      // std::move
#include <string>       // std::string
#include <stdexcept>    // std::invalid_argument

// написать template функцию с двумя итераторами на входе и унарным оператором, которая ходит между итераторами и
// выполняет оператор для каждого элемента
template<class ForwardIt, class Func>
void iterate(ForwardIt first, ForwardIt last, Func f)
{
    auto it = first;
    while (it != last) {
		f(*it);
		++it;
    }
}

// написать класс с move-конструктором
template<class T> class AcceptsMoveInit
{
	T val;
	
public:
	AcceptsMoveInit(AcceptsMoveInit&& other) noexcept
		: val(std::move(other.val))		// нужно ли обернуть other.val в std::move? upd 220716: да
	{
	}
};

// задание на рефакторинг. 
// - дан класс. интерфейс менять нельзя. всё остальное можно и нужно поменять. в продакшене должно работать без проблем
// - добавить конструктор копирования и оператор присваивания
/*
class Pair {
public:
	Pair(const char *b, const char *q) {
		b_ = new char[strlen(b)];
		strcpy(b_, b);
		
		q_ = new char[strlen(q)];
		strcpy(q_, q);
	}
private:
	char * b_;	// base
	char * q_;	// quoted
};

int main() {
	
	return 0;
}
*/
// ------------------------------------

class Pair {
public:
	Pair(const char *b, const char *q) {	
		if (!b || !q)
			throw std::invalid_argument("null parameter in Pair constructor");
		
		b_ = std::string(b);
		q_ = std::string(q);
	}
    Pair(std::string b, std::string q)      // TODO why should I pass by value and do std::move?
        : b_(std::move(b)), q_(std::move(q)) {}
	Pair(const Pair& other) = default;      // TODO default for trivial copy/move constructors / assignment operators
    Pair(Pair&& other) = default;
	Pair& operator=(const Pair& other) = default;
    Pair& operator=(Pair&& other) = default;
	
private:
	std::string b_;	// base
	std::string q_;	// quoted
};

int main() {
	return 0;
}
