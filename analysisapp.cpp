#include <iostream>
#include <string>

using namespace std;

const int alphabet_size = 26;

bool check_alphabets(char c) {
    static bool look_table[256] = {false};
    static bool initialisation = false;

    if (!initialisation) {
        for (int i = 'a'; i <= 'z'; i++) {
            look_table[i] = true;
        }
        for (int i = 'A'; i <= 'Z'; i++) {
            look_table[i] = true;
        }
        initialisation = true;
    }

    return look_table[(unsigned char) c];
}

int main() {
    string cipher_text;
    int letter_count[alphabet_size] = {0};

    cout << "Enter the cipher text: ";
    getline(cin, cipher_text);

    for (char c : cipher_text) {
        if (check_alphabets(c)) {
            letter_count[toupper(c) - 'A']++;
        }
    }

    cout<<"Analysis:"<<endl;

    for (int i = 0; i < alphabet_size; i++) {
        char letter = 'A' + i;
        if (letter_count[i] > 0) {
            cout << letter << "->" << letter_count[i] << ",";
        }
    }

    return 0;
}
