#include <iostream>

using namespace std;

class AddAmount {
private:
    double amount;

public:
    AddAmount() {
        amount = 50.00;
    }

    AddAmount(double additionalAmount) {
        amount = 50.00 + additionalAmount;
    }

    void displayAmount() {
        cout << "The final amount in the Piggy Bank is: $" << amount << endl;
    }
    
    void getUserInput() {
        double additionalAmount;
        cout << "Enter the amount to add to the Piggy Bank: $";
        cin >> additionalAmount;
        amount += additionalAmount;
    }
};

int main() {
    AddAmount piggyBank;

    cout << "Initial amount in the Piggy Bank: $50.00" << endl;
    piggyBank.getUserInput();

    piggyBank.displayAmount();

    return 0;
}
