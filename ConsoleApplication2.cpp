#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
int hui4;
using namespace std;
struct NumberInfo // структура для хранения информации о найденных числах
{
    int lineNumber;
    int number;

    NumberInfo(int line, int num) : lineNumber(line), number(num) {}
};
int main(int argc, char* argv[])
{
    setlocale(0, "");
    string in, out;
    if (argc < 2) {
        cout << "Недостаточно аргументов в командной строке.\nВходной файл: ";
        cin >> in;
        cout << "Выходной файл: ";
        cin >> out;
    }
    if (argc < 3 && argc > 1) {
        if (string(argv[1]) == "-I") {
            in = string(argv[2]);
            string a = "TITLE in: " + in;
            system(a.c_str());
            a.clear();
            cout << "Введите имя файла для выхода: ";
            cin >> out;
        }
        else if (string(argv[1]) == "-O") {
            out = string(argv[2]);
            string a = "TITLE in: " + out;
            system(a.c_str());
            a.clear();
            cout << "Введите имя файла для входа: ";
            cin >> in;
        }
    }
    if (argc < 6 && argc > 2) {
        if (string(argv[1]) == "-I") {
            in = string(argv[2]);
        }
        if (string(argv[1]) == "-O") {
            out = string(argv[2]);
        }
        if (argc == 4) {
            if (in == "") {
                cout << "Чего-то не хватает, введи имя для входного файла: ";
                cin >> in;
            }
            else {
                cout << "Чего-то не хватает, введи имя для выходного файла: ";
                cin >> out;
            }
        }
        if (argc == 5) {
            if (string(argv[1]) == "-I") {
                in = string(argv[2]);
                cout << in;
            }
            if (string(argv[1]) == "-O") {
                out = string(argv[2]);
            }
            if (string(argv[3]) == "-I") {
                in = string(argv[4]);
            }
            if (string(argv[3]) == "-O") {
                out = string(argv[4]);
            }
        }
    }


    if (in == "") {
        cout << "in пуст, введите его: ";
        cin >> in;
    }
    if (out == "") {
        cout << "in: " << in << endl;
        cout << "out пуст, введите его: 228 ";
        cin >> out;
    }
    ifstream in_;
    in_.open(in, ios::in);
    string line;
    map<int, vector<int>> table;
    int lineNumber = 0;
    ofstream out_;
    out_.open(out, ios::out);
    int found;
    bool numFound = false;  // флаг, что число найдено
    string inp = "TITLE in: " + in + " out: " + out;
    system(inp.c_str());
    char b = '\'';
    char c = '"';
    int m = 1;

    bool kav = false;
    while (getline(in_, line)) // читаем файл построчно
    {
        ++lineNumber;
        cout << m << " ";
        cout << line;
        cout << "   ";
        m = m + 1;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '"' && !kav) {
                kav = true;
                continue;
            }
            if (line[i] == '"' && kav) {
                kav = false;
            }
            if (isdigit(line[i]) && !kav) {  // если символ является цифрой
                if (!numFound) {  // если это начало нового числа
                    numFound = true;  // устанавливаем флаг
                    found = line[i] - 48;  // первую цифру записываем в переменную
                }
                else {  // если это следующая цифра числа
                    found = found * 10 + (line[i] - 48);  // увеличиваем число
                }
            }
            else {  // если это не цифра
                if (numFound) {  // если перед этим было найдено число
                    cout << found << "\t";  // выводим число
                    table[found].push_back(lineNumber);
                    numFound = false;  // сбрасываем флаг
                }
            }
        }
        cout << endl;
    }

    in_.close(); // закрываем файл
    // Выводим таблицу на экран
    cout << "\n№ Число\tСтроки" << endl;
    out_ << "\n№ Число\tСтроки" << endl;
    int k = 1;

    for (auto& row : table) {
        cout << k << " " << row.first << "\t";
        out_ << k << " " << row.first << "\t";
        k++;

        for (auto& lineNumber : row.second) {
            cout << lineNumber << " ";
            out_ << lineNumber << " ";
        }
        cout << endl;
        out_ << endl;
    }

    out_.close();
    return 0;
}
