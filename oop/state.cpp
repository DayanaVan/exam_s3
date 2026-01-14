#include <iostream>
using namespace std;

class State;

class Lamp { // контекст
public:
	State* state;
};

class State { // состояние (интерфейс)
public:
	virtual void use(Lamp* l) = 0;
};

class Off : public State { // состояние 1
public:
	void use(Lamp* l) override;
};

class On : public State { // состояние 2
public:
	void use(Lamp* l) override;
};

Off off;
On on;

void Off::use(Lamp* l) {
	cout << "On\n";
	l->state = &on;
}

void On::use(Lamp* l) {
	cout << "Off\n";
	l->state = &off;
}


int main() {
	Lamp l;
	l.state = &off;

	l.state->use(&l);
	l.state->use(&l);
}
