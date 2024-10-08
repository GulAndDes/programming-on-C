#pragma once
#include <iostream>
#include <sstream>
#include <climits>
#include <stack>
#include <string>

//класс вершины дерева выражений
class AriphmTree {
    char symbol; // символ
    AriphmTree* left; // указатель на левое под-дерево
    AriphmTree* right; // указатель на правое под-дерево

    bool is_operator(); // функция проверки вершины на оператор
    static bool is_char_operator(char c); // проверка символа на оператор
    static int priority(char c); // функция вычисл приоритет оператора
    static int op_assoc(char c); // функция вычисл ассоциативность оператора
    AriphmTree* create(std::string expression); //функция создающая дерево по строке выражения
    static void transform(AriphmTree* tree);// функция варианта
    
public:
    AriphmTree(char c); // конструктор вершины
    AriphmTree(const std::string& expression); // конструктор дерева по строке
    AriphmTree(const AriphmTree& other); // копи-конструктор(оказался не нужен)
    void print(int lvl);//функция вывода дерева в консоль
    AriphmTree* tree_copy(AriphmTree* tree); // функция копирования дерева
    ~AriphmTree();//деструктор(очистка дерева)
    void applyTransformation();//функция применения варианта трансформации

};
