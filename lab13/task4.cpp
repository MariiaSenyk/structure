#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    multimap<char, string> wordGroups;
    string word;

    cout << "Enter words one per line (empty line to finish):\n";

    while (getline(cin, word) && !word.empty()) {
        auto start = word.find_first_not_of(" \t");
        if (start == string::npos) continue;
        word = word.substr(start);
        char key = tolower((unsigned char)word[0]);
        wordGroups.insert({key, word});
    }

    if (wordGroups.empty()) {
        cout << "No words entered.\n";
        return 0;
    }

    cout << "\n--- Words grouped by first letter ---\n";
    char currentKey = '\0';
    for (const auto& [key, w] : wordGroups) {
        if (key != currentKey) {
            currentKey = key;
            cout << "\n[" << (char)toupper(key) << "]\n";
        }
        cout << "  " << w << "\n";
    }

    cout << "\n--- Statistics ---\n";
    char prev = '\0';
    for (const auto& [key, w] : wordGroups) {
        if (key != prev) {
            prev = key;
            cout << (char)toupper(key) << ": " << wordGroups.count(key) << " word(s)\n";
        }
    }

    return 0;
}