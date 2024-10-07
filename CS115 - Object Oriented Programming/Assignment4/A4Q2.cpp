#include <iostream>

using namespace std;

void counter(const char *inp);

int main(){
    const int size = 100;
    char input[size];

    cout << "Input a string, max size of 100 characters in all lowercase letters: ";
    cin.getline(input, size);

    counter(input);

    return 0;
}

void counter(const char *inp){
    int vowels = 0;
    int consonants = 0;

    while(*inp != '\0'){
        if(*inp >= 'a' && *inp <= 'z'){
            if(*inp == 'a' || *inp == 'e' || *inp == 'i' || *inp == 'o' || *inp == 'u'){
                vowels++;
            } else {
                consonants++;
            }
        }
        *inp++;
    }

    cout << "Number of vowels: " << vowels << endl;
    cout << "Number of consonants: " << consonants << endl;
}
