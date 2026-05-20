#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cctype>
#include <sstream>

using namespace std;

const wstring ALPHABET = L"абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
const int ALPHA_SIZE = 33;
const string DEFAULT_FILE = "task2.txt";

wstring generateKey() {
    wstring key = ALPHABET;
    srand(time(NULL));
    for (int i = 0; i < ALPHA_SIZE; i++) {
        int j = rand() % ALPHA_SIZE;
        wchar_t temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }
    return key;
}

wstring encrypt(const wstring &text, const wstring &key) {
    wstring result;
    for (wchar_t ch: text) {
        int pos = -1;
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (ALPHABET[i] == towlower(ch)) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            wchar_t enc = key[pos];
            result += iswupper(ch) ? towupper(enc) : enc;
        } else {
            result += ch;
        }
    }
    return result;
}

wstring decrypt(const wstring &text, const wstring &key) {
    wstring result;
    for (wchar_t ch: text) {
        int pos = -1;
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (key[i] == towlower(ch)) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            wchar_t dec = ALPHABET[pos];
            result += iswupper(ch) ? towupper(dec) : dec;
        } else {
            result += ch;
        }
    }
    return result;
}

void printKeyTable(const wstring &key) {
    wcout << L"\nТаблиця заміни:\n";
    wcout << L"Відкрит: ";
    for (int i = 0; i < ALPHA_SIZE; i++) {
        wcout << ALPHABET[i] << L" ";
    }
    wcout << L"\nЗашифр: ";
    for (int i = 0; i < ALPHA_SIZE; i++) {
        wcout << key[i] << L" ";
    }
    wcout << L"\n";
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    wcout.imbue(locale("uk_UA.UTF-8"));
    wcin.imbue(locale("uk_UA.UTF-8"));

    wcout << L"=== Шифр простої заміни ===\n\n";

    wcout << L"Джерело тексту:\n1 - Клавіатура\n2 - Файл (task2.txt)\nВибір (1 або 2): ";

    wstring srcChoiceStr;
    getline(wcin, srcChoiceStr);

    if (srcChoiceStr.empty() || (srcChoiceStr != L"1" && srcChoiceStr != L"2")) {
        wcout << L"Помилка! Потрібно ввести 1 або 2\n";
        return 1;
    }

    int srcChoice = (srcChoiceStr == L"1") ? 1 : 2;

    wstring text;
    if (srcChoice == 2) {
        wcout << L"Читання з файлу task2.txt\n";
        wifstream f(DEFAULT_FILE);
        f.imbue(locale("uk_UA.UTF-8"));

        if (!f.is_open()) {
            wcout << L"Помилка відкриття файлу!\n";
            return 1;
        }

        wstring line;
        while (getline(f, line)) {
            text += line + L"\n";
        }
        f.close();
        wcout << L"Текст завантажено\n";
    } else {
        wcout << L"Введіть текст: ";
        getline(wcin, text);
    }

    wcout << L"\nКлюч:\n1 - Згенерувати автоматично\n2 - Ввести вручну\nВибір (1 або 2): ";

    wstring keyChoiceStr;
    getline(wcin, keyChoiceStr);

    if (keyChoiceStr.empty() || (keyChoiceStr != L"1" && keyChoiceStr != L"2")) {
        wcout << L"Помилка! Потрібно ввести 1 або 2\n";
        return 1;
    }

    int keyChoice = (keyChoiceStr == L"1") ? 1 : 2;

    wstring key;
    if (keyChoice == 1) {
        key = generateKey();
        wcout << L"Згенерований ключ: " << key << L"\n";
    } else {
        wcout << L"Введіть ключ (" << ALPHA_SIZE << L" літер): ";
        getline(wcin, key);

        if (key.length() != ALPHA_SIZE) {
            wcout << L"Невірна довжина, використовуємо згенерований ключ\n";
            key = generateKey();
        }
    }

    printKeyTable(key);

    wstring encrypted = encrypt(text, key);
    wcout << L"\n=== Зашифрований текст ===\n" << encrypted << L"\n";

    wofstream fo(DEFAULT_FILE);
    fo.imbue(locale("uk_UA.UTF-8"));
    fo << encrypted;
    fo.close();
    wcout << L"\nЗашифрований текст збережено у файл " << wstring(DEFAULT_FILE.begin(), DEFAULT_FILE.end()) << L"\n";

    wcout << L"\nДія:\n1 - Дешифрувати зашифрований текст (ключем)\n2 - Вийти\nВибір (1 або 2): ";

    wstring actionStr;
    getline(wcin, actionStr);

    if (actionStr.empty() || (actionStr != L"1" && actionStr != L"2")) {
        wcout << L"Помилка! Потрібно ввести 1 або 2\n";
        return 1;
    }

    int action = (actionStr == L"1") ? 1 : 2;

    if (action == 1) {
        wifstream f(DEFAULT_FILE);
        f.imbue(locale("uk_UA.UTF-8"));

        wstring encryptedText;
        wstring line;
        while (getline(f, line)) {
            encryptedText += line + L"\n";
        }
        f.close();

        wstring decrypted = decrypt(encryptedText, key);
        wcout << L"\n=== Дешифрований текст ===\n" << decrypted << L"\n";
    }

    wcout << L"\nПрограма завершена.\n";
    return 0;
}
