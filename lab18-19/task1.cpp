#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, double> ukrFreq = {
    {"о", 9.28}, {"а", 8.34}, {"е", 7.89}, {"і", 7.56},
    {"н", 6.95}, {"т", 6.29}, {"с", 5.62}, {"р", 5.01},
    {"л", 4.70}, {"в", 4.48}, {"к", 3.95}, {"м", 3.78},
    {"д", 3.61}, {"п", 3.42}, {"у", 2.90}, {"з", 2.65},
    {"я", 2.47}, {"и", 2.20}, {"б", 1.85}, {"г", 1.70},
    {"ї", 1.49}, {"й", 1.35}, {"х", 1.11}, {"ж", 0.95},
    {"є", 0.82}, {"ч", 0.77}, {"ю", 0.64}, {"ш", 0.59},
    {"ц", 0.52}, {"щ", 0.43}, {"ф", 0.22}, {"ґ", 0.15},
    {"ь", 0.13}
};

const string UKR_ALPHABET = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
const int ALPHA_SIZE = 33;

class UTF8String {
private:
    string data;
public:
    UTF8String(const string &s) : data(s) {
    }

    size_t length() const {
        size_t len = 0;
        for (size_t i = 0; i < data.length(); i++) {
            if ((data[i] & 0xC0) != 0x80) len++;
        }
        return len;
    }

    string operator[](size_t index) const {
        size_t current = 0;
        for (size_t i = 0; i < data.length(); i++) {
            if ((data[i] & 0xC0) != 0x80) {
                if (current == index) {
                    string result;
                    result += data[i];
                    for (size_t j = i + 1; j < data.length() && ((data[j] & 0xC0) == 0x80); j++) {
                        result += data[j];
                    }
                    return result;
                }
                current++;
            }
        }
        return "";
    }

    int find(const string &ch) const {
        size_t current = 0;
        for (size_t i = 0; i < data.length(); i++) {
            if ((data[i] & 0xC0) != 0x80) {
                string currentChar;
                currentChar += data[i];
                for (size_t j = i + 1; j < data.length() && ((data[j] & 0xC0) == 0x80); j++) {
                    currentChar += data[j];
                }

                if (currentChar == ch) {
                    return current;
                }
                current++;
            }
        }
        return -1;
    }

    const string &str() const { return data; }
};

string shiftChar(const string &ch, int shift) {
    UTF8String alphabet(UKR_ALPHABET);
    int pos = alphabet.find(ch);
    if (pos != -1) {
        int newPos = (pos + shift) % ALPHA_SIZE;
        if (newPos < 0) newPos += ALPHA_SIZE;
        return alphabet[newPos];
    }
    return ch;
}

bool isUkrainianLetter(const string &ch) {
    UTF8String alphabet(UKR_ALPHABET);
    return alphabet.find(ch) != -1;
}

string caesarCipher(const string &text, int shift) {
    string result;
    size_t i = 0;

    while (i < text.length()) {
        string ch;
        ch += text[i];

        if ((text[i] & 0x80) != 0) {
            int bytes = 1;
            if ((text[i] & 0xE0) == 0xC0) bytes = 2;
            else if ((text[i] & 0xF0) == 0xE0) bytes = 3;
            else if ((text[i] & 0xF8) == 0xF0) bytes = 4;

            for (int j = 1; j < bytes && i + j < text.length(); j++) {
                ch += text[i + j];
            }
            i += bytes;
        } else {
            i++;
        }

        if (isUkrainianLetter(ch)) {
            result += shiftChar(ch, shift);
        } else {
            string upperCh;
            for (size_t j = 0; j < ch.length(); j++) {
                upperCh += toupper(ch[j]);
            }
            if (isUkrainianLetter(upperCh)) {
                string shiftedLower = shiftChar(ch, shift);
                for (size_t j = 0; j < shiftedLower.length(); j++) {
                    result += toupper(shiftedLower[j]);
                }
            } else {
                result += ch;
            }
        }
    }

    return result;
}
map<string, int> countFrequencies(const string &text) {
    map<string, int> freq;
    size_t i = 0;

    while (i < text.length()) {
        string ch;
        ch += text[i];

        if ((text[i] & 0x80) != 0) {
            int bytes = 1;
            if ((text[i] & 0xE0) == 0xC0) bytes = 2;
            else if ((text[i] & 0xF0) == 0xE0) bytes = 3;
            else if ((text[i] & 0xF8) == 0xF0) bytes = 4;

            for (int j = 1; j < bytes && i + j < text.length(); j++) {
                ch += text[i + j];
            }
            i += bytes;
        } else {
            i++;
        }

        string lowerCh;
        for (size_t j = 0; j < ch.length(); j++) {
            lowerCh += tolower(ch[j]);
        }

        if (isUkrainianLetter(lowerCh)) {
            freq[lowerCh]++;
        }
    }

    return freq;
}

int frequencyAnalysis(const string &text) {
    map<string, int> freq = countFrequencies(text);
    int total = 0;

    for (map<string, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        total += it->second;
    }

    if (total == 0) return 0;

    double bestScore = -1e18;
    int bestShift = 0;
    UTF8String alphabet(UKR_ALPHABET);

    for (int shift = 0; shift < ALPHA_SIZE; shift++) {
        double score = 0;

        for (map<string, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
            string ch = it->first;
            int count = it->second;

            int pos = alphabet.find(ch);
            int originalPos = (pos - shift) % ALPHA_SIZE;
            if (originalPos < 0) originalPos += ALPHA_SIZE;
            string originalCh = alphabet[originalPos];

            double expected = 0.0;
            if (ukrFreq.find(originalCh) != ukrFreq.end()) {
                expected = ukrFreq[originalCh];
            }

            score += ((double) count / total) * expected;
        }

        if (score > bestScore) {
            bestScore = score;
            bestShift = shift;
        }
    }

    return bestShift;
}

vector<int> findSubstring(const string &text, const string &pattern) {
    vector<int> positions;
    if (pattern.empty() || text.empty() || pattern.length() > text.length()) return positions;

    for (size_t i = 0; i <= text.length() - pattern.length(); i++) {
        bool found = true;
        for (size_t j = 0; j < pattern.length(); j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            positions.push_back(i);
        }
    }

    return positions;
}

int main() {
    cout << "=== Шифр Цезаря ===\n\n";

    string text;
    int srcChoice;

    cout << "Джерело тексту:\n";
    cout << "1 - Введення з клавіатури\n";
    cout << "2 - Зчитати з файлу (task1.txt)\n";
    cout << "Вибір: ";
    cin >> srcChoice;
    cin.ignore();

    if (srcChoice == 2) {
        string filename = "task1.txt";
        cout << "Читання з файлу: " << filename << "\n";

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Помилка: не вдалося відкрити файл " << filename << "!\n";
            cout << "Переконайтеся, що файл існує в поточній директорії.\n";
            return 1;
        }

        string line;
        while (getline(file, line)) {
            text += line + "\n";
        }
        file.close();

        cout << "\n--- Вміст файлу ---\n";
        cout << text;
        cout << "--- Кінець файлу ---\n";
    } else {
        cout << "Введіть текст: ";
        getline(cin, text);
    }

    if (text.empty()) {
        cout << "Помилка: текст порожній!\n";
        return 1;
    }

    cout << "\nДія:\n";
    cout << "1 - Шифрування\n";
    cout << "2 - Дешифрування (зворотній зсув)\n";
    cout << "3 - Дешифрування (частотний метод)\n";
    cout << "Вибір: ";

    int action;
    cin >> action;
    cin.ignore();

    string result;

    if (action == 1) {
        int shift;
        cout << "Введіть крок зсуву (додатній - вправо, від'ємний - вліво): ";
        cin >> shift;
        cin.ignore();
        result = caesarCipher(text, shift);
        cout << "\n=== ЗАШИФРОВАНИЙ ТЕКСТ ===\n";
        cout << result << "\n";
        cout << "==========================\n";
    } else if (action == 2) {
        int shift;
        cout << "Введіть крок зсуву (що використовувався при шифруванні): ";
        cin >> shift;
        cin.ignore();
        result = caesarCipher(text, -shift);
        cout << "\n=== ДЕШИФРОВАНИЙ ТЕКСТ ===\n";
        cout << result << "\n";
        cout << "===========================\n";
    } else if (action == 3) {
        cout << "\nВиконується частотний аналіз...\n";
        int detectedShift = frequencyAnalysis(text);
        cout << "Визначений зсув: " << detectedShift << "\n";
        result = caesarCipher(text, -detectedShift);
        cout << "\n=== ДЕШИФРОВАНИЙ ТЕКСТ ===\n";
        cout << result << "\n";
        cout << "===========================\n";

        cout << "\nПеревірка за ключовим словом\n";
        cout << "Введіть ключове слово для пошуку: ";
        string keyword;
        getline(cin, keyword);

        vector<int> positions = findSubstring(result, keyword);
        if (positions.empty()) {
            cout << "Ключове слово \"" << keyword << "\" не знайдено.\n";
        } else {
            cout << "Ключове слово знайдено на позиціях: ";
            for (size_t i = 0; i < positions.size(); i++) {
                cout << positions[i] << " ";
            }
            cout << "\nДешифрування успішне!\n";
        }
    }

    cout << "\nЗберегти результат у файл? (1 - так, 0 - ні): ";
    int save;
    cin >> save;
    cin.ignore();

    if (save == 1) {
        string outFile;
        if (action == 1) {
            outFile = "task1.txt";
            cout << "Автоматичне збереження в файл: " << outFile << "\n";
        } else {
            outFile = "task1.txt";
            cout << "Автоматичне збереження в файл: " << outFile << "\n";
        }

        ofstream fout(outFile);
        if (!fout.is_open()) {
            cout << "Помилка: не вдалося створити файл " << outFile << "!\n";
        } else {
            fout << result;
            fout.close();
            cout << "Результат успішно збережено у файл: " << outFile << "\n";
        }
    }

    return 0;
}
