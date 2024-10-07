#include <iostream>
using namespace std;

class Student {
public:
  string name;
  int roll_no;
  Student() {
    name = "John";
    roll_no = 2;
  }
  void display() {
    cout << "Name: " << name << endl;
    cout << "Roll #: " << roll_no;
  }
};

int main() {
  Student s1;
  s1.display();
  return 0;
}
