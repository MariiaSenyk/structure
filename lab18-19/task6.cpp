#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

map<wchar_t, string> morseCode = {
    {L'а', ".-"},    {L'б', "-..."},  {L'в', ".--"},   {L'г', "--."},
    {L'ґ', "--.-"},  {L'д', "-.."},   {L'е', "."},     {L'є', "..-.."},
    {L'ж', "...-"},  {L'з', "--.."},  {L'и', ".."},    {L'і', ".."},
    {L'ї', ".---."}, {L'й', ".---"},  {L'к', "-.-"},   {L'л', ".-.."},
    {L'м', "--"},    {L'н', "-."},    {L'о', "---"},   {L'п', ".--."},
    {L'р', ".-."},   {L'с', "..."},   {L'т', "-"},     {L'у', "..-"},
    {L'ф', "..-."},  {L'х', "...."},  {L'ц', "-.-."},  {L'ч', "---."},
    {L'ш', "----"},  {L'щ', "--.-"},  {L'ь', "-..-"},  {L'ю', "..--"},
    {L'я', ".-.-"},

    {L'0', "-----"}, {L'1', ".----"}, {L'2', "..---"}, {L'3', "...--"},
    {L'4', "....-"}, {L'5', "....."}, {L'6', "-...."}, {L'7', "--..."},
    {L'8', "---.."}, {L'9', "----."},

    {L'.', ".-.-.-"}, {L',', "--..--"}, {L'?', "..--.."}, {L'!', "-.-.--"},
    {L';', "-.-.-."}, {L':', "---..."}, {L'\'', ".----."}, {L'"', ".-..-."},
    {L'(', "-.--."},  {L')', "-.--.-"}, {L' ', "/"}
};

map<string, wchar_t> reverseMorse;

void initReverseMorse() {
    for (auto& pair : morseCode) {
        reverseMorse[pair.second] = pair.first;
    }
}

class UTF8String {
private:
    string data;

public:
    UTF8String(const string& s) : data(s) {}

    vector<wchar_t> toWideString() const {
        vector<wchar_t> result;
        size_t i = 0;

        while (i < data.length()) {
            if ((data[i] & 0x80) == 0) {
                result.push_back(static_cast<wchar_t>(data[i]));
                i++;
            }
            else if ((data[i] & 0xE0) == 0xC0) {
                wchar_t ch = ((data[i] & 0x1F) << 6) | (data[i+1] & 0x3F);
                result.push_back(ch);
                i += 2;
            }
            else if ((data[i] & 0xF0) == 0xE0) {
                wchar_t ch = ((data[i] & 0x0F) << 12) | ((data[i+1] & 0x3F) << 6) | (data[i+2] & 0x3F);
                result.push_back(ch);
                i += 3;
            }
            else {
                i++;
            }
        }
        return result;
    }

    static string fromWideChar(wchar_t ch) {
        string result;
        if (ch < 0x80) {
            result += static_cast<char>(ch);
        }
        else if (ch < 0x800) {
            result += static_cast<char>(0xC0 | (ch >> 6));
            result += static_cast<char>(0x80 | (ch & 0x3F));
        }
        else {
            result += static_cast<char>(0xE0 | (ch >> 12));
            result += static_cast<char>(0x80 | ((ch >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (ch & 0x3F));
        }
        return result;
    }
};
void playMorseSound(const string& morse, int dotDuration = 200) {
    int dashDuration = dotDuration * 3;
    int symbolPause = dotDuration;

    for (char c : morse) {
        if (c == '.') {
            cout << "● ";
            cout << '\a' << flush;
            this_thread::sleep_for(chrono::milliseconds(dotDuration));
        }
        else if (c == '-') {
            cout << "■ ";
            cout << '\a' << flush;
            this_thread::sleep_for(chrono::milliseconds(dashDuration));
        }
        else if (c == ' ') {
            cout << " ";
            this_thread::sleep_for(chrono::milliseconds(symbolPause));
        }
        else if (c == '/') {
            cout << " / ";
            this_thread::sleep_for(chrono::milliseconds(dotDuration * 7));
        }

        if (c != ' ' && c != '/') {
            this_thread::sleep_for(chrono::milliseconds(symbolPause));
        }
    }
}

string textToMorse(const string& text) {
    string result;
    UTF8String utf8Text(text);
    vector<wchar_t> wideText = utf8Text.toWideString();

    for (size_t i = 0; i < wideText.size(); i++) {
        wchar_t ch = wideText[i];
        wchar_t lowerCh = towlower(ch);

        if (morseCode.find(lowerCh) != morseCode.end()) {
            result += morseCode[lowerCh];

            if (i < wideText.size() - 1 && wideText[i + 1] != L' ') {
                result += " ";
            }
        }
        else if (lowerCh == L' ') {
            result += " / ";
        }
        else {
            result += "?";
            if (i < wideText.size() - 1 && wideText[i + 1] != L' ') {
                result += " ";
            }
        }
    }

    return result;
}

string morseToText(const string& morse) {
    string result;
    stringstream ss(morse);
    string token;

    while (ss >> token) {
        if (token == "/") {
            result += UTF8String::fromWideChar(L' ');
        }
        else if (reverseMorse.find(token) != reverseMorse.end()) {
            result += UTF8String::fromWideChar(reverseMorse[token]);
        }
        else {
            result += '?';
        }
    }

    return result;
}

string readFromFile(const string& filename) {
    string text;
    ifstream file(filename);

    if (!file.is_open()) {
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
        return false;
    }

    file << text;
    file.close();
    return true;
}

void printMorseTable() {
    cout << "\n=== ТАБЛИЦЯ АЗБУКИ МОРЗЕ (УКРАЇНСЬКА) ===\n\n";
    cout << "Літера -> Код Морзе\n";
    cout << "-------------------\n";

    vector<pair<wchar_t, string>> table;
    for (auto& pair : morseCode) {
        if (iswalpha(pair.first) || iswdigit(pair.first)) {
            table.push_back(pair);
        }
    }

    for (size_t i = 0; i < table.size(); i++) {
        string ch = UTF8String::fromWideChar(table[i].first);
        cout << "  " << ch << "       -> " << table[i].second << "\n";
        if ((i + 1) % 10 == 0 && i < table.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\nСпеціальні символи:\n";
    cout << "  пробіл -> /\n";
    cout << "  . -> .-.-\n";
    cout << "  , -> --..--\n";
    cout << "  ? -> ..--..\n";
    cout << "  ! -> -.-.--\n";
    cout << "====================================\n\n";
}

int main() {
    cout << "=== АЗБУКА МОРЗЕ (УКРАЇНСЬКА) ===\n\n";
    initReverseMorse();

    string text;
    int srcChoice;

    cout << "Джерело тексту:\n";
    cout << "1 - Введення з клавіатури\n";
    cout << "2 - Зчитати з файлу (task5.txt)\n";
    cout << "Вибір: ";
    cin >> srcChoice;
    cin.ignore();

    if (srcChoice == 2) {
        string filename = "task6.txt";
        cout << "Читання з файлу: " << filename << "\n\n";
        text = readFromFile(filename);

        if (text.empty()) {
            cout << "Помилка: файл порожній або не вдалося прочитати!\n";
            cout << "Створіть файл " << filename << " з текстом для шифрування.\n";
            return 1;
        }

        cout << "--- Вміст файлу " << filename << " ---\n";
        cout << text;
        cout << "--- Кінець файлу ---\n";
    } else {
        cout << "Введіть текст українською мовою: ";
        getline(cin, text);
    }

    if (text.empty()) {
        cout << "Помилка: текст порожній!\n";
        return 1;
    }

    cout << "\nДія:\n";
    cout << "1 - Шифрування (текст -> Морзе)\n";
    cout << "2 - Дешифрування (Морзе -> текст)\n";
    cout << "3 - Показати таблицю Морзе\n";
    cout << "Вибір: ";

    int action;
    cin >> action;
    cin.ignore();

    if (action == 3) {
        printMorseTable();
        return 0;
    }

    string result;

    cout << "\n" << string(50, '=') << "\n";

    if (action == 1) {
        cout << "ВИХІДНИЙ ТЕКСТ:\n";
        cout << text << "\n";

        result = textToMorse(text);

        cout << "\nКОД МОРЗЕ:\n";
        cout << result << "\n";

        cout << "\nВідтворити звуковий супровід? (1 - так, 0 - ні): ";
        int playSound;
        cin >> playSound;
        cin.ignore();

        if (playSound == 1) {
            cout << "\nВідтворення азбуки Морзе:\n";
            cout << ". = короткий сигнал (●)\n";
            cout << "- = довгий сигнал (■)\n\n";
            playMorseSound(result);
            cout << "\n\n";
        }

        cout << "\nЗберегти результат у файл? (1 - так, 0 - ні): ";
        int saveChoice;
        cin >> saveChoice;
        cin.ignore();

        if (saveChoice == 1) {
            string outFile = "task6.txt";
            if (saveToFile(outFile, result)) {
                cout << "Код Морзе збережено у файл: " << outFile << "\n";
            } else {
                cout << "Помилка збереження файлу!\n";
            }
        }
    }
    else if (action == 2) {
        cout << "ВВЕДІТЬ КОД МОРЗЕ (використовуйте . та -, пробіл між літерами, / для слів):\n";
        cout << "Приклад: -- .- .-. .. .- / .-.. ..- -... .. - -...\n";
        cout << "Ваш код: ";
        getline(cin, result);

        string decoded = morseToText(result);

        cout << "\nДЕШИФРОВАНИЙ ТЕКСТ:\n";
        cout << decoded << "\n";

        cout << "\nЗберегти результат у файл? (1 - так, 0 - ні): ";
        int saveChoice;
        cin >> saveChoice;
        cin.ignore();

        if (saveChoice == 1) {
            string outFile = "task6.txt";
            if (saveToFile(outFile, decoded)) {
                cout << "Дешифрований текст збережено у файл: " << outFile << "\n";
            } else {
                cout << "Помилка збереження файлу!\n";
            }
        }
    }
    else {
        cout << "Невірний вибір!\n";
        return 1;
    }

    cout << string(50, '=') << "\n";

    return 0;
}