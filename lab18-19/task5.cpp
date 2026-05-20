#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const wstring ALPHABET = L"АБВГДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЮЯ";
const int SIZE = 5; //
const string DEFAULT_FILE = "task5.txt";

vector<vector<wchar_t>> createPlayfairMatrix(const wstring& key) {
    vector<vector<wchar_t>> matrix(SIZE, vector<wchar_t>(SIZE));
    wstring used;
    wstring fullKey = key;

    wstring cleanKey;
    for (wchar_t ch : fullKey) {
        ch = towupper(ch);
        if (ch == L'Ь') ch = L'Ї';
        if (ch == L'Ґ') ch = L'Г';
        if (ALPHABET.find(ch) != wstring::npos && cleanKey.find(ch) == wstring::npos) {
            cleanKey += ch;
        }
    }

    wstring alphabet = ALPHABET;
    wstring result = cleanKey;
    for (wchar_t ch : alphabet) {
        if (result.find(ch) == wstring::npos) {
            result += ch;
        }
    }

    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = result[idx++];
        }
    }

    return matrix;
}

void findPosition(const vector<vector<wchar_t>>& matrix, wchar_t ch, int& row, int& col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

wstring prepareText(const wstring& text) {
    wstring result;
    wstring temp;

    for (wchar_t ch : text) {
        wchar_t upper = towupper(ch);
        if (ALPHABET.find(upper) != wstring::npos) {
            temp += upper;
        }
    }

    for (size_t i = 0; i < temp.length(); i++) {
        result += temp[i];
        if (i + 1 < temp.length()) {
            if (temp[i] == temp[i + 1]) {
                result += L'Х';
            }
        } else if (result.length() % 2 == 1) {
            result += L'Х';
        }
    }

    if (result.length() % 2 == 1) {
        result += L'Х';
    }

    return result;
}

wstring encryptPair(const vector<vector<wchar_t>>& matrix, wchar_t a, wchar_t b) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    wstring result;

    if (row1 == row2) {
        result += matrix[row1][(col1 + 1) % SIZE];
        result += matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result += matrix[(row1 + 1) % SIZE][col1];
        result += matrix[(row2 + 1) % SIZE][col2];
    } else {
        result += matrix[row1][col2];
        result += matrix[row2][col1];
    }

    return result;
}

wstring decryptPair(const vector<vector<wchar_t>>& matrix, wchar_t a, wchar_t b) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, row1, col1);
    findPosition(matrix, b, row2, col2);

    wstring result;

    if (row1 == row2) {
        result += matrix[row1][(col1 - 1 + SIZE) % SIZE];
        result += matrix[row2][(col2 - 1 + SIZE) % SIZE];
    } else if (col1 == col2) {
        result += matrix[(row1 - 1 + SIZE) % SIZE][col1];
        result += matrix[(row2 - 1 + SIZE) % SIZE][col2];
    } else {
        result += matrix[row1][col2];
        result += matrix[row2][col1];
    }

    return result;
}

void printMatrix(const vector<vector<wchar_t>>& matrix) {
    wcout << L"\nМатриця шифрування (5x5):\n";
    wcout << L"   ";
    for (int i = 0; i < SIZE; i++) {
        wcout << L" " << i + 1 << L"  ";
    }
    wcout << L"\n";

    for (int i = 0; i < SIZE; i++) {
        wcout << L" " << i + 1 << L" ";
        for (int j = 0; j < SIZE; j++) {
            wcout << L"| " << matrix[i][j] << L" ";
        }
        wcout << L"|\n";
        if (i < SIZE - 1) {
            wcout << L"   ";
            for (int j = 0; j < SIZE; j++) {
                wcout << L"+---";
            }
            wcout << L"+\n";
        }
    }
    wcout << L"\n";
}

wstring encryptPlayfair(const wstring& text, const wstring& key) {
    auto matrix = createPlayfairMatrix(key);
    wstring prepared = prepareText(text);
    wstring result;

    for (size_t i = 0; i < prepared.length(); i += 2) {
        result += encryptPair(matrix, prepared[i], prepared[i + 1]);
    }

    return result;
}

wstring decryptPlayfair(const wstring& text, const wstring& key) {
    auto matrix = createPlayfairMatrix(key);
    wstring prepared = prepareText(text);
    wstring result;

    for (size_t i = 0; i < prepared.length(); i += 2) {
        result += decryptPair(matrix, prepared[i], prepared[i + 1]);
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    wcout.imbue(locale("uk_UA.UTF-8"));
    wcin.imbue(locale("uk_UA.UTF-8"));

    wcout << L"=== Шифр Плейфера ===\n\n";

    wcout << L"Джерело тексту:\n1 - Введення з клавіатури\n2 - Читання з файлу (task5.txt)\nВибір (1 або 2): ";
    wstring choiceStr;
    getline(wcin, choiceStr);

    wstring text;
    if (choiceStr == L"2") {
        wcout << L"Читання з файлу " << wstring(DEFAULT_FILE.begin(), DEFAULT_FILE.end()) << L"\n";

        wifstream file(DEFAULT_FILE);
        if (!file.is_open()) {
            wcout << L"Помилка відкриття файлу " << wstring(DEFAULT_FILE.begin(), DEFAULT_FILE.end()) << L"!\n";
            return 1;
        }

        file.imbue(locale("uk_UA.UTF-8"));
        wstring line;
        while (getline(file, line)) {
            text += line + L"\n";
        }
        file.close();
        wcout << L"Текст завантажено з файлу\n";
    } else {
        wcout << L"Введіть текст для шифрування: ";
        getline(wcin, text);
    }

    wcout << L"\nОригінальний текст:\n" << text << L"\n";

    wcout << L"\nВведіть ключове слово або фразу: ";
    wstring key;
    getline(wcin, key);

    auto matrix = createPlayfairMatrix(key);
    printMatrix(matrix);

    wcout << L"\nВиберіть дію:\n1 - Шифрування\n2 - Дешифрування\nВибір (1 або 2): ";
    getline(wcin, choiceStr);

    wstring result;
    if (choiceStr == L"1") {
        result = encryptPlayfair(text, key);
        wcout << L"\n=== Зашифрований текст ===\n" << result << L"\n";
    } else {
        result = decryptPlayfair(text, key);
        wcout << L"\n=== Дешифрований текст ===\n" << result << L"\n";
    }

    wcout << L"\nЗберегти результат у файл " << wstring(DEFAULT_FILE.begin(), DEFAULT_FILE.end()) << L"? (1 - так, 0 - ні): ";
    wstring saveChoice;
    getline(wcin, saveChoice);

    if (saveChoice == L"1") {
        wofstream file(DEFAULT_FILE);
        if (file.is_open()) {
            file.imbue(locale("uk_UA.UTF-8"));
            file << result;
            file.close();
            wcout << L"Результат збережено у файл " << wstring(DEFAULT_FILE.begin(), DEFAULT_FILE.end()) << L"\n";
        } else {
            wcout << L"Помилка збереження файлу!\n";
        }
    }

    wcout << L"\nПрограма завершена.\n";
    return 0;
}