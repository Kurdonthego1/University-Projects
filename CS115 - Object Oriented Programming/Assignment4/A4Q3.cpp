#include <iostream>

using namespace std;

class Shape{
    public:

    void print(){
        cout << "This is a shape" << endl;
    }
};

class Polygon : public Shape{
    public:

    void print(){
        cout << "This is a polygon" << endl;
    }
};

class Triangle : public Polygon{
    public:

    void print(){
        cout << "Triangle is a polygon" << endl;
    }
};

class Rectangle : public Polygon{
    public:

    void print(){
        cout << "Rectangle is a polygon" << endl;
    }
};

class Square : public Rectangle{
    public:

    void print(){
        cout << "Square is a rectangle" << endl;
    }
};

int main(){
    Shape s;
    Polygon p;
    Triangle t;
    Rectangle r;
    Square sq;

    s.print();
    p.print();
    t.print();
    r.print();
    sq.print();
    
    return 0;
}
