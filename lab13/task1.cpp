#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

string normalize(const string& word) {
    string result;
    for (char c : word) {
        if (isalpha((unsigned char)c)) {
            result += tolower((unsigned char)c);
        }
    }
    return result;
}

int main() {
    map<string, int> wordCount;
    string line;

    cout << "Enter text (empty line to finish):\n";

    while (getline(cin, line) && !line.empty()) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            string normalized = normalize(word);
            if (!normalized.empty()) {
                wordCount[normalized]++;
            }
        }
    }

    cout << "\n--- Word frequencies (alphabetical order) ---\n";
    for (const auto& [word, count] : wordCount) {
        cout << word << ": " << count << "\n";
    }

    return 0;
}