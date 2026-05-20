#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string UKR_LOWER = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
const string UKR_UPPER = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";
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

void printVigenereTable() {
    cout << "\n=== ТАБЛИЦЯ ВІЖЕНЕРА ===\n\n";
    cout << "    ";

    UTF8String alphabet(UKR_LOWER);

    for (int i = 0; i < ALPHA_SIZE; i++) {
        cout << alphabet[i] << "  ";
    }
    cout << "\n";

    cout << "    ";
    for (int i = 0; i < ALPHA_SIZE; i++) {
        cout << "---";
    }
    cout << "\n";

    for (int i = 0; i < ALPHA_SIZE; i++) {
        cout << alphabet[i] << " | ";

        for (int j = 0; j < ALPHA_SIZE; j++) {
            int pos = (i + j) % ALPHA_SIZE;
            cout << alphabet[pos] << "  ";
        }
        cout << "\n";
    }

    cout << "\n=== ПОЯСНЕННЯ ===\n";
    cout << "Рядок - літера ключа\n";
    cout << "Стовпець - літера тексту\n";
    cout << "На перетині - зашифрована літера\n\n";
}

int getLetterPosition(const string &ch) {
    UTF8String lower(UKR_LOWER);
    UTF8String upper(UKR_UPPER);

    int pos = lower.find(ch);
    if (pos != -1) return pos;

    pos = upper.find(ch);
    if (pos != -1) return pos;

    return -1;
}

string getLetterByPosition(int pos, bool isUpper = false) {
    UTF8String lower(UKR_LOWER);
    UTF8String upper(UKR_UPPER);

    if (isUpper) {
        return upper[pos];
    }
    return lower[pos];
}

vector<string> splitToChars(const string &text) {
    vector<string> chars;
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

        chars.push_back(ch);
    }

    return chars;
}

bool isUkrainianLetter(const string &ch) {
    UTF8String lower(UKR_LOWER);
    UTF8String upper(UKR_UPPER);
    return lower.find(ch) != -1 || upper.find(ch) != -1;
}

bool isUpper(const string &ch) {
    UTF8String upper(UKR_UPPER);
    return upper.find(ch) != -1;
}

string normalizeKey(const string &key) {
    vector<string> chars = splitToChars(key);
    string normalized;

    for (size_t i = 0; i < chars.size(); i++) {
        if (isUkrainianLetter(chars[i])) {
            normalized += chars[i];
        }
    }

    return normalized;
}

string vigenereEncrypt(const string &text, const string &key, bool verbose = false) {
    string result;
    vector<string> textChars = splitToChars(text);
    string normalizedKey = normalizeKey(key);

    if (normalizedKey.empty()) {
        cout << "Помилка: ключ не містить жодної української літери!\n";
        return text;
    }

    vector<int> keyPositions;
    UTF8String lower(UKR_LOWER);

    for (size_t i = 0; i < normalizedKey.length(); i++) {
        string keyChar = splitToChars(normalizedKey)[i];
        string lowerKeyChar;
        for (size_t j = 0; j < keyChar.length(); j++) {
            lowerKeyChar += tolower(keyChar[j]);
        }
        int pos = lower.find(lowerKeyChar);
        if (pos != -1) {
            keyPositions.push_back(pos);
        }
    }

    if (verbose) {
        cout << "\n=== ДЕТАЛІ ШИФРУВАННЯ ===\n";
        cout << "Ключ (нормалізований): " << normalizedKey << "\n";
        cout << "Позиції ключа: ";
        for (size_t i = 0; i < keyPositions.size(); i++) {
            cout << keyPositions[i] << " ";
        }
        cout << "\n\n";
        cout << "Літера тексту -> Літера ключа -> Позиція -> Зашифрована літера\n";
        cout << "-------------------------------------------------------------\n";
    }

    int keyIndex = 0;
    for (size_t i = 0; i < textChars.size(); i++) {
        string ch = textChars[i];

        if (isUkrainianLetter(ch)) {
            bool isUpperLetter = isUpper(ch);
            string lowerCh;
            for (size_t j = 0; j < ch.length(); j++) {
                lowerCh += tolower(ch[j]);
            }

            int textPos = getLetterPosition(lowerCh);
            int shift = keyPositions[keyIndex % keyPositions.size()];
            int newPos = (textPos + shift) % ALPHA_SIZE;

            string keyChar = splitToChars(normalizedKey)[keyIndex % keyPositions.size()];

            if (verbose) {
                cout << ch << " -> " << keyChar << " -> "
                        << textPos << " + " << shift << " = " << newPos
                        << " -> " << getLetterByPosition(newPos, isUpperLetter) << "\n";
            }

            result += getLetterByPosition(newPos, isUpperLetter);
            keyIndex++;
        } else {
            if (verbose && ch != "\n") {
                cout << "\"" << ch << "\" (не літера) -> залишається без змін\n";
            }
            result += ch;
        }
    }

    if (verbose) {
        cout << "-------------------------------------------------------------\n";
    }

    return result;
}

string vigenereDecrypt(const string &text, const string &key, bool verbose = false) {
    string result;
    vector<string> textChars = splitToChars(text);
    string normalizedKey = normalizeKey(key);

    if (normalizedKey.empty()) {
        cout << "Помилка: ключ не містить жодної української літери!\n";
        return text;
    }

    vector<int> keyPositions;
    UTF8String lower(UKR_LOWER);

    for (size_t i = 0; i < normalizedKey.length(); i++) {
        string keyChar = splitToChars(normalizedKey)[i];
        string lowerKeyChar;
        for (size_t j = 0; j < keyChar.length(); j++) {
            lowerKeyChar += tolower(keyChar[j]);
        }
        int pos = lower.find(lowerKeyChar);
        if (pos != -1) {
            keyPositions.push_back(pos);
        }
    }

    if (verbose) {
        cout << "\n=== ДЕТАЛІ ДЕШИФРУВАННЯ ===\n";
        cout << "Ключ (нормалізований): " << normalizedKey << "\n";
        cout << "Позиції ключа: ";
        for (size_t i = 0; i < keyPositions.size(); i++) {
            cout << keyPositions[i] << " ";
        }
        cout << "\n\n";
        cout << "Літера тексту -> Літера ключа -> Позиція -> Дешифрована літера\n";
        cout << "-------------------------------------------------------------\n";
    }

    int keyIndex = 0;
    for (size_t i = 0; i < textChars.size(); i++) {
        string ch = textChars[i];

        if (isUkrainianLetter(ch)) {
            bool isUpperLetter = isUpper(ch);
            string lowerCh;
            for (size_t j = 0; j < ch.length(); j++) {
                lowerCh += tolower(ch[j]);
            }

            int textPos = getLetterPosition(lowerCh);
            int shift = keyPositions[keyIndex % keyPositions.size()];
            int newPos = (textPos - shift) % ALPHA_SIZE;
            if (newPos < 0) newPos += ALPHA_SIZE;

            string keyChar = splitToChars(normalizedKey)[keyIndex % keyPositions.size()];

            if (verbose) {
                cout << ch << " -> " << keyChar << " -> "
                        << textPos << " - " << shift << " = " << newPos
                        << " -> " << getLetterByPosition(newPos, isUpperLetter) << "\n";
            }

            result += getLetterByPosition(newPos, isUpperLetter);
            keyIndex++;
        } else {
            if (verbose && ch != "\n") {
                cout << "\"" << ch << "\" (не літера) -> залишається без змін\n";
            }
            result += ch;
        }
    }

    if (verbose) {
        cout << "-------------------------------------------------------------\n";
    }

    return result;
}

int main() {
    cout << "=== ШИФР ВІЖЕНЕРА ===\n\n";

    printVigenereTable();

    string text;
    string key;
    int srcChoice;

    cout << "Джерело тексту:\n";
    cout << "1 - Введення з клавіатури\n";
    cout << "2 - Зчитати з файлу (task3.txt)\n";
    cout << "Вибір: ";
    cin >> srcChoice;
    cin.ignore();

    if (srcChoice == 2) {
        string filename = "task3.txt";
        cout << "Читання з файлу: " << filename << "\n\n";

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Помилка: не вдалося відкрити файл " << filename << "!\n";
            cout << "Створіть файл " << filename << " з текстом для шифрування.\n";
            return 1;
        }

        string line;
        while (getline(file, line)) {
            text += line + "\n";
        }
        file.close();

        cout << "--- Вміст файлу " << filename << " ---\n";
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

    cout << "\nВведіть ключове слово: ";
    getline(cin, key);

    if (key.empty()) {
        cout << "Помилка: ключове слово не може бути порожнім!\n";
        return 1;
    }

    cout << "\nДія:\n";
    cout << "1 - Шифрування\n";
    cout << "2 - Дешифрування\n";
    cout << "3 - Шифрування з детальним виведенням\n";
    cout << "4 - Дешифрування з детальним виведенням\n";
    cout << "Вибір: ";

    int action;
    cin >> action;
    cin.ignore();

    string result;
    bool verbose = (action == 3 || action == 4);

    if (action == 1 || action == 3) {
        result = vigenereEncrypt(text, key, verbose);
        cout << "\n=== ЗАШИФРОВАНИЙ ТЕКСТ ===\n";
        cout << result << "\n";
        cout << "==========================\n";

        string outFile = "task3.txt";
        ofstream fout(outFile);
        if (fout.is_open()) {
            fout << result;
            fout.close();
            cout << "\nЗашифрований текст збережено у файл: " << outFile << "\n";
        }
    } else if (action == 2 || action == 4) {
        result = vigenereDecrypt(text, key, verbose);
        cout << "\n=== ДЕШИФРОВАНИЙ ТЕКСТ ===\n";
        cout << result << "\n";
        cout << "===========================\n";

        string outFile = "task3.txt";
        ofstream fout(outFile);
        if (fout.is_open()) {
            fout << result;
            fout.close();
            cout << "\nДешифрований текст збережено у файл: " << outFile << "\n";
        }
    } else {
        cout << "Невірний вибір!\n";
        return 1;
    }

    cout << "\nДля перевірки правильності використайте таблицю Віженера вище.\n";
    cout << "Знайдіть на перетині літери тексту та літери ключа.\n";

    return 0;
}
