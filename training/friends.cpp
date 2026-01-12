#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point() {
        x = 0;
        y = 0;
    } // по умолчанию

    Point(int valueX, int valueY) // с параметрами
    {
        x = valueX;
        y = valueY;
    }

    void Print() {
        cout << "x = " << x << " y = " << y << endl;
    }

    friend void ChangeX(Point& value);
};

void ChangeX(Point& value) {
    value.x = -1;
}

int main()
{
    Point a(5, 12);
    a.Print();
    ChangeX(a);
    a.Print();

    return 0;
}
