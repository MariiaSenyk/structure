#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

class PolybiusSquare {
private:
    vector<vector<char>> square;
    map<char, pair<int, int>> charToCoord;
    int size;
    string alphabet;

public:

    PolybiusSquare() {
        alphabet = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
        size = ceil(sqrt(alphabet.length()));

        square.resize(size, vector<char>(size, ' '));

        int index = 0;
        for (int i = 0; i < size && index < alphabet.length(); i++) {
            for (int j = 0; j < size && index < alphabet.length(); j++) {
                square[i][j] = alphabet[index];
                charToCoord[alphabet[index]] = {i, j};
                index++;
            }
        }
    }

    PolybiusSquare(const string& customAlphabet) {
        alphabet = customAlphabet;
        size = ceil(sqrt(alphabet.length()));

        square.resize(size, vector<char>(size, ' '));

        int index = 0;
        for (int i = 0; i < size && index < alphabet.length(); i++) {
            for (int j = 0; j < size && index < alphabet.length(); j++) {
                square[i][j] = alphabet[index];
                charToCoord[alphabet[index]] = {i, j};
                index++;
            }
        }
    }
    void printSquare() {
        cout << "\n=== КВАДРАТ ПОЛІБІЯ ===\n\n";

        cout << "    ";
        for (int j = 0; j < size; j++) {
            cout << " " << j + 1 << "  ";
        }
        cout << "\n";

        cout << "    ";
        for (int j = 0; j < size; j++) {
            cout << "---";
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            cout << " " << i + 1 << " | ";
            for (int j = 0; j < size; j++) {
                if (square[i][j] != ' ') {
                    cout << square[i][j] << "  ";
                } else {
                    cout << "   ";
                }
            }
            cout << "\n";
        }
        cout << "=====================\n\n";
    }

    string encrypt(const string& text) {
        string result;

        for (char ch : text) {
            char lowerCh = tolower(ch);

            if (charToCoord.find(lowerCh) != charToCoord.end()) {
                auto coord = charToCoord[lowerCh];
                result += to_string(coord.first + 1) + to_string(coord.second + 1);
                result += " ";  // Роздільник для кращої читабельності
            }
            else if (charToCoord.find(ch) != charToCoord.end()) {
                auto coord = charToCoord[ch];
                result += to_string(coord.first + 1) + to_string(coord.second + 1);
                result += " ";
            }
            else {
                result += ch;
                result += " ";
            }
        }

        return result;
    }

    string decrypt(const string& encryptedText) {
        string result;
        string currentNum;

        for (size_t i = 0; i < encryptedText.length(); i++) {
            char ch = encryptedText[i];

            if (isdigit(ch)) {
                currentNum += ch;
            }
            else {
                if (currentNum.length() == 2) {
                    int row = (currentNum[0] - '0') - 1;
                    int col = (currentNum[1] - '0') - 1;

                    if (row >= 0 && row < size && col >= 0 && col < size) {
                        result += square[row][col];
                    } else {
                        result += '?';
                    }
                    currentNum.clear();
                }

                if (ch != ' ') {
                    result += ch;
                }
            }
        }

        if (currentNum.length() == 2) {
            int row = (currentNum[0] - '0') - 1;
            int col = (currentNum[1] - '0') - 1;

            if (row >= 0 && row < size && col >= 0 && col < size) {
                result += square[row][col];
            }
        }

        return result;
    }

    string encryptCompact(const string& text) {
        string result;

        for (char ch : text) {
            char lowerCh = tolower(ch);

            if (charToCoord.find(lowerCh) != charToCoord.end()) {
                auto coord = charToCoord[lowerCh];
                result += to_string(coord.first + 1) + to_string(coord.second + 1);
            }
            else if (charToCoord.find(ch) != charToCoord.end()) {
                auto coord = charToCoord[ch];
                result += to_string(coord.first + 1) + to_string(coord.second + 1);
            }
            else {
                result += ch;
            }
        }

        return result;
    }

    string decryptCompact(const string& encryptedText) {
        string result;

        for (size_t i = 0; i < encryptedText.length(); i += 2) {
            if (i + 1 < encryptedText.length() &&
                isdigit(encryptedText[i]) && isdigit(encryptedText[i + 1])) {
                int row = (encryptedText[i] - '0') - 1;
                int col = (encryptedText[i + 1] - '0') - 1;

                if (row >= 0 && row < size && col >= 0 && col < size) {
                    result += square[row][col];
                } else {
                    result += '?';
                }
            }
            else {
                result += encryptedText[i];
            }
        }

        return result;
    }

    int getSize() const { return size; }

    string getAlphabet() const { return alphabet; }
};

string readFromFile(const string& filename) {
    string text;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Помилка: не вдалося відкрити файл " << filename << "!\n";
        return "";
    }

    string line;
    while (getline(file, line)) {
        text += line + "\n";
    }
    file.close();

    return text;
}

bool saveToFile(const string& filename, const string& text) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Помилка: не вдалося створити файл " << filename << "!\n";
        return false;
    }

    file << text;
    file.close();
    return true;
}

int main() {
    cout << "=== КВАДРАТ ПОЛІБІЯ ===\n\n";

    int alphabetChoice;
    cout << "Виберіть алфавіт:\n";
    cout << "1 - Український (33 літери, 6x6 квадрат)\n";
    cout << "2 - Англійський (26 літер, 5x5 квадрат, I=J)\n";
    cout << "3 - Ввести свій алфавіт\n";
    cout << "Вибір: ";
    cin >> alphabetChoice;
    cin.ignore();

    PolybiusSquare* cipher = nullptr;

    if (alphabetChoice == 1) {
        cipher = new PolybiusSquare();
        cout << "\nВибрано український алфавіт (33 літери)\n";
    }
    else if (alphabetChoice == 2) {
        string englishAlphabet = "abcdefghijklmnopqrstuvwxyz";
        englishAlphabet = "abcdefghiklmnopqrstuvwxyz";
        cipher = new PolybiusSquare(englishAlphabet);
        cout << "\nВибрано англійський алфавіт (25 літер, I=J)\n";
    }
    else {
        string customAlphabet;
        cout << "Введіть свій алфавіт (без пробілів): ";
        getline(cin, customAlphabet);
        cipher = new PolybiusSquare(customAlphabet);
        cout << "\nВибрано користувацький алфавіт (" << customAlphabet.length() << " літер)\n";
    }

    cipher->printSquare();

    string text;
    int srcChoice;

    cout << "Джерело тексту:\n";
    cout << "1 - Введення з клавіатури\n";
    cout << "2 - Зчитати з файлу (task4.txt)\n";
    cout << "Вибір: ";
    cin >> srcChoice;
    cin.ignore();

    if (srcChoice == 2) {
        string filename = "task4.txt";
        cout << "Читання з файлу: " << filename << "\n\n";
        text = readFromFile(filename);

        if (text.empty()) {
            cout << "Помилка: файл порожній або не вдалося прочитати!\n";
            delete cipher;
            return 1;
        }

        cout << "--- Вміст файлу " << filename << " ---\n";
        cout << text;
        cout << "--- Кінець файлу ---\n";
    } else {
        cout << "Введіть текст: ";
        getline(cin, text);
    }

    if (text.empty()) {
        cout << "Помилка: текст порожній!\n";
        delete cipher;
        return 1;
    }

    cout << "\nДія:\n";
    cout << "1 - Шифрування\n";
    cout << "2 - Дешифрування\n";
    cout << "Вибір: ";

    int action;
    cin >> action;
    cin.ignore();

    int formatChoice;
    cout << "\nФормат виведення:\n";
    cout << "1 - З роздільниками (наприклад: 11 12 13)\n";
    cout << "2 - Компактний (наприклад: 111213)\n";
    cout << "Вибір: ";
    cin >> formatChoice;
    cin.ignore();

    string result;

    cout << "\n" << string(50, '=') << "\n";

    if (action == 1) {
        cout << "ВИХІДНИЙ ТЕКСТ:\n";
        cout << text << "\n";

        if (formatChoice == 1) {
            result = cipher->encrypt(text);
        } else {
            result = cipher->encryptCompact(text);
        }
        cout << "\nЗАШИФРОВАНИЙ ТЕКСТ:\n";
        cout << result << "\n";

        string outFile = "task4.txt";
        if (saveToFile(outFile, result)) {
            cout << "\nЗашифрований текст збережено у файл: " << outFile << "\n";
        }
    }
    else if (action == 2) {
        cout << "ЗАШИФРОВАНИЙ ТЕКСТ:\n";
        cout << text << "\n";

        if (formatChoice == 1) {
            result = cipher->decrypt(text);
        } else {
            result = cipher->decryptCompact(text);
        }

        cout << "\nДЕШИФРОВАНИЙ ТЕКСТ:\n";
        cout << result << "\n";

        string outFile = "task4.txt";
        if (saveToFile(outFile, result)) {
            cout << "\nДешифрований текст збережено у файл: " << outFile << "\n";
        }
    }
    else {
        cout << "Невірний вибір!\n";
        delete cipher;
        return 1;
    }

    cout << string(50, '=') << "\n";

    cout << "\n=== ПОЯСНЕННЯ ===\n";
    cout << "Квадрат Полібія: кожна літера замінюється на координати (рядок, стовпець)\n";
    cout << "Розмір квадрату: " << cipher->getSize() << "x" << cipher->getSize() << "\n";
    cout << "Кількість літер в алфавіті: " << cipher->getAlphabet().length() << "\n";

    if (cipher->getAlphabet().length() > cipher->getSize() * cipher->getSize()) {
        cout << "Увага: Деякі літери не помістилися в квадрат!\n";
    }

    delete cipher;
    return 0;
}