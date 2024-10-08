#include <iostream>
#include "tree.hpp"


int main(int argc, char* argv[]) {
    // считываем строку
    std::string expr;
    std::cin >> expr;
    // создаем дерево по строке
    AriphmTree tree(expr);
    // печатаем исходное
    tree.print(0);
    // трансформируем
    tree.applyTransformation();
    // печатаем вновь
    tree.print(0);
    return 0;
}