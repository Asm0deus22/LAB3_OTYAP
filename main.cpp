////////////////////
// FILE: main.cpp //
////////////////////
#include <fstream>
#include <iostream>
#include <List.h>
#include <Utils.h>
#include <LexicalAnalyser.h>

using namespace std;
using namespace CustomList;
using namespace Lexemes;

int main() { // я не хочу это в main, это же ведь тест
    ifstream reading("input.txt"); // готовим чтение
    
    reading.seekg(0, ios::end); // узнаем размер файла
    int size = (int) reading.tellg();
    reading.seekg(0, ios::beg);
    
    char *str = new char[size + 1]; // готовим строку для сохранения
    reading.read(str, size); // читаем
    str[size] = 0; // зануляем конец
    reading.close(); // закрываем чтение
    // инициализируем списки лексем
    List<Lexeme*> *lexemes = new List<Lexeme*>();
    List<Lexeme*> *ids = new List<Lexeme*>();
    List<Lexeme*> *constants = new List<Lexeme*>();
    
    LexicalAnalyser::analyze(*lexemes, str, size + 1); // запускаем лексический анализатор
    
    /////////////////// ВЫВОДИМ ИНФУ /////////////////////
    ofstream writing("output.txt"); // готовим запись
    char *out;
    bool isFirst = true;
    Lexeme *current;
    int i;
    for (i = 0; i < lexemes->getSize(); i++) { // Выводим все лексемы
        current = lexemes->operator[](i);
        out = getLexemeCString(*current);
        
        switch (current->type) { // если нужно - готовим список ИДшек и констант на вывод
            case id: {
                ids->pushBack(current);
                break;
            }
            case vl: {
                constants->pushBack(current);
                break;
            }
        }
        
        if (isFirst) isFirst = !isFirst;
        else {
            cout << ' ';
            writing << ' ';
        }
        cout << out;
        writing << out;
        
        delete[] out; // очищаем временную строку
    }
    cout << endl;
    writing << endl;
    isFirst = true;
    for (i = 0; i < ids->getSize(); i++) { // выводим ИДшки
        current = ids->operator[](i);
        
        if (isFirst) isFirst = !isFirst;
        else {
            cout << ' ';
            writing << ' ';
        }
        cout << current->lexComponent;
        writing << current->lexComponent;
    }
    cout << endl;
    writing << endl;
    isFirst = true;
    for (i = 0; i < constants->getSize(); i++) { // выводим константы
        current = constants->operator[](i);
        
        if (isFirst) isFirst = !isFirst;
        else {
            cout << ' ';
            writing << ' ';
        }
        cout << current->lexComponent;
        writing << current->lexComponent;
    }
    /////////////////// КОНЕЦ ИНФЫ /////////////////////
    
    // все нафиг сносим и закрываем адекватно
    writing.close();
    while (lexemes->getSize()) delete lexemes->popBack(); // достаточно удалять только из этого списка, т.к. в ids, constants хранятся именно что копии указателей
    delete ids;
    delete constants;
    delete lexemes;
    delete[] str;

    return 0;
}
///////////////////////////
// END OF FILE: main.cpp //
///////////////////////////