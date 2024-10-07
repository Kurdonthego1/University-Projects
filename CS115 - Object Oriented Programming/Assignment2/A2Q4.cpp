#include <iostream>
#include <string>

using namespace std;

class Car {
private:
  string company;
  string model;
  int year;

public:
  Car(string c, string m, int y) : company(c), model(m), year(y) {}

  string getComp() const { return company; }

  string getModel() const { return model; }

  int getYear() const { return year; }

  void setComp(string c) { company = c; }

  void setModel(string m) { model = m; }

  void setYear(int y) { year = y; }
};

int main() {
  Car TheWhip("Kia", "Soul", 2012);

  cout << "Old car: " << endl;
  cout << "Company: " << TheWhip.getComp() << endl;
  cout << "Model: " << TheWhip.getModel() << endl;
  cout << "Year: " << TheWhip.getYear() << endl;

  TheWhip.setComp("Cadillac");
  TheWhip.setModel("CT4 V BW");
  TheWhip.setYear(2023);

  cout << endl;

  cout << "The new whip: " << endl;
  cout << "Company: " << TheWhip.getComp() << endl;
  cout << "Model: " << TheWhip.getModel() << endl;
  cout << "Year: " << TheWhip.getYear() << endl;

  return 0;
}
