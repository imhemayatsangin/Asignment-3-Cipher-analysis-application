#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

string replace_cipher_text(const string& cipher_text, const vector<pair<char,char>>& replacement_rule) {
    string plain_text = cipher_text;
    for (char& c : plain_text) {
        if (check_alphabets(c)) {
            char uppercase_c = toupper(c);
            for (auto& pair : replacement_rule) {
                if (pair.first == uppercase_c) {
                    char replacement = pair.second;
                    c = tolower(replacement);
                    break;
                }
            }
        }
    }
    return plain_text;
}

int main() {
      string cipher_text;
    int letter_count[alphabet_size] = {0};

    ifstream file("cipher.txt");

    if (file.is_open()) {
        getline(file, cipher_text);
        file.close();
    } else {
        cout << "Unable to open file";
        return 1;
    }

    for (char c : cipher_text) {
        if (check_alphabets(c)) {
            letter_count[toupper(c) - 'A']++;
        }
    }
cout << "Cipher Text:" << endl;
cout << cipher_text<< endl;
    cout << "Analysis:" << endl;

    // Find the highest frequency
    int highest_frequency = 0;
    for (int i = 0; i < alphabet_size; i++) {
        if (letter_count[i] > highest_frequency) {
            highest_frequency = letter_count[i];
        }
    }

    // Display letters with the highest frequency first
    for (int j = highest_frequency; j > 0; j--) {
        for (int i = 0; i < alphabet_size; i++) {
            if (letter_count[i] == j) {
                char letter = 'A' + i;
                cout << letter << "->" << letter_count[i] << ",";
            }
        }
    }
    cout << endl;

    cout << "Option:" << endl;
    cout << "1) Take replace rule" << endl;
    cout << "2) Exit" << endl;

    int option;
    cout << "Option> ";
    cin >> option;

    if (option == 1) {
        string replace_rule;
        cout << "Enter replacement rule: ";
        cin.ignore();
        getline(cin, replace_rule);

        vector<pair<char,char>> replacement_vec;
        size_t pos = 0;
        while (pos < replace_rule.length()) {
            size_t comma_pos = replace_rule.find(',', pos);
            if (comma_pos == string::npos) {
                break;
            }
            string pair = replace_rule.substr(pos, comma_pos - pos);
            size_t colon_pos = pair.find(':');
            if (colon_pos == string::npos) {
                cout << "Invalid replace rule format. Please try again." << endl;
                return 1;
            }
            char cipher_char = pair[colon_pos - 1];
            char plain_char = pair[colon_pos + 1];
            replacement_vec.push_back(make_pair(toupper(cipher_char), tolower(plain_char)));
            pos = comma_pos + 1;
        }

        string plain_text = replace_cipher_text(cipher_text, replacement_vec);
        cout<<"Plain Text: "<<endl;
        cout << plain_text << endl;
    }

    return 0;
}
