#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point(int valueX, int valueY) // only in public section!
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
    Point b(2, 4);
    a.Print();
    b.Print();

    return 0;
}
