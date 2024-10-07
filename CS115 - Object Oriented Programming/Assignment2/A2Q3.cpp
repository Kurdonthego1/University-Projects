#include <cmath>
#include <iostream>

using namespace std;

class Traingle {
public:
  double a = 3, b = 5, c = 4, s;

  double calcPerimeter() { return s = (a + b + c); }

  double calcArea() {
    s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
  }
};

int main() {
  Traingle T;

  cout << "Perimeter: " << T.calcPerimeter() << endl;
  cout << "Area: " << T.calcArea() << endl;

  return 0;
}
