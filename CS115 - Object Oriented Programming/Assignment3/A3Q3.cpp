#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    string name;
    string number;
    string type;
    double balance;

public:
    BankAccount(const string& n, const string& Num, const string& T, double B) {
        name = n;
        number = Num;
        type = T;
        balance = B;
    }

    void input() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter account number: ";
        cin >> number;
        cout << "Enter account type: ";
        cin >> type;
        cout << "Enter initial balance: $";
        cin >> balance;
    }

    void deposit(double amount) {
        cout << "How much would you like to deposit" << endl;
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount. Please enter a positive amount." << endl;
        }
    }

    void withdraw(double amount) {
        cout << "How much would you like to withdraw" << endl;
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        } if (amount = 0){
            cout << "No withdrawl" << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
        }
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "Account Number: " << number << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int main() {
    BankAccount account("", "", "", 0.0);

    account.input();
    cout << endl;
    account.display();
    cout << endl;
    account.deposit(0.0);
    cout << endl;
    account.withdraw(0.0);
    cout << endl;
    account.display();
    cout << endl;

    return 0;
}
