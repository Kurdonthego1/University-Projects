#include <iostream>

using namespace std;

int main() {
    const int number = 5;
    int counts[number] = {0};
    int spoiltballot = 0;

    while (true) {
        int candidate;

        cout << "Enter the candiate number 1 to 5 (0 to stop)" << endl;
        cin >> candidate;

        if (candidate == 0) {
            break;
        }

        if (candidate >= 1 && candidate <= 5) {
            counts[candidate - 1]++;
        }

        else {
            spoiltballot++;
        }
    }

    for (int i = 0; i < number; i++) {
        cout << "Candidate " << (i + 1) << ": " << counts[i] << " votes" << endl;
    }

    cout << "Spoilt Ballots: " << spoiltballot << endl;

    return 0;
}
