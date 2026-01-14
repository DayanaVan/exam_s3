#include <iostream>
using namespace std;

class Cat;
class Dog;

class Visitor { // посетитель (интерфейс)
public:
    virtual void visitCat(Cat* c) = 0;
    virtual void visitDog(Dog* d) = 0;
};

class Animal { // элемент (интерфейс)
public:
    virtual void accept(Visitor* v) = 0;
};

class Cat : public Animal { // конкретный элемент 2
public:
    void accept(Visitor* v) override {
        v->visitCat(this);
    }
};

class Dog : public Animal { // конкретный элемент 2
public:
    void accept(Visitor* v) override {
        v->visitDog(this);
    }
};

class ConcreteVisitor : public Visitor { // конкретный посетитель
public:
    void visitCat(Cat*) override {
        cout << "Cat says meow\n";
    }

    void visitDog(Dog*) override {
        cout << "Dog says woof\n";
    }
};

int main()
{
    Cat cat;
    Dog dog;

    ConcreteVisitor cv;

    cat.accept(&cv);
    dog.accept(&cv);
}
