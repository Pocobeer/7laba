#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

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
        cout << "out пуст, введите его: ";
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
    const char* b = "'";
    const char c = '"';
    int m = 1;
    while (getline(in_, line)) // читаем файл построчно
    {
        ++lineNumber;
        cout << m << " ";
        cout << line;
        cout << "   ";
        m = m + 1;
        for (int i = 0; i < line.length(); i++) {  // проходим по символам строки
            if (isdigit(line[i])) {  // если символ является цифрой
                if (!numFound) {  // если это начало нового числа
                    numFound = true;  // устанавливаем флаг
                    found = line[i] - '0';  // первую цифру записываем в переменную
                    if (line[i-1] == '[' && line[i] == found) continue;
                }
                else {  // если это следующая цифра числа
                    found = found * 10 + (line[i] - '0');  // увеличиваем число
                }
            }
            else {  // если это не цифра
                if (numFound) {  // если перед этим было найдено число
                    cout << found << " ";  // выводим число
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