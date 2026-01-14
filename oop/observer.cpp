#include <iostream>

using namespace std;

class Subscriber;

class Publisher { // издатель
public:
	Subscriber* obs;

	void setSubscriber(Subscriber* o) {
		obs = o;
	}

	void change(int v);
};

class Subscriber { // подписчик
public:
	virtual void update(int v) = 0;
};

class ConcreteSubscriber : public Subscriber { // конкретный подписчик
public:
	void update(int v) override {
		cout << "Value is " << v << endl;
	}
};

void Publisher::change(int v) { // метод оповещения
	if (obs != nullptr) {
		obs->update(v);
	}
}

int main() {
	Publisher s;
	ConcreteSubscriber p;

	s.setSubscriber(&p);

	s.change(10);
	s.change(20);
}
