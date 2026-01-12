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
};

int main()
{
    Point a(1, 1);
    a.Print();

    Point b;
    b.Print();

    return 0;
}
