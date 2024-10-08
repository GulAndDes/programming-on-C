#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// Структура узла дерева
struct Node {
    char value;
    Node* left;
    Node* right;
};
// Функция для проверки, имеет ли оператор1 больший приоритет, чем оператор2
bool hasHigherPrecedence(char op1, char op2) {
    if ((op1 == '*' || op1 == '/' || op1 == '^') && (op2 == '+' || op2 == '-'))
        return true;
    else
        return false;
}

// Создание нового узла
Node* createNode(char value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Функция для построения дерева выражений из постфиксной записи
Node* buildTree(string postfix) {
    stack<Node*> st;
    for (char c : postfix) {
        if (isdigit(c)) {
            Node* newNode = createNode(c - '0'); // Преобразуем цифру из строки в число
            st.push(newNode);
        } else {
            Node* right = st.top();
            st.pop();
            Node* left = st.top();
            st.pop();
            Node* newNode = createNode(c);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }
    return st.top();
}

// Функция для вычисления значения выражения, представленного деревом
int evaluateTree(Node* root) {
    if (root->left == nullptr && root->right == nullptr)
        return root->value; // Лист - это число

    int leftVal = evaluateTree(root->left);
    int rightVal = evaluateTree(root->right);

    switch (root->value) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            return leftVal / rightVal;
        case '^':
            return pow(leftVal, rightVal);
        default:
            throw invalid_argument("Invalid operator");
    }
}

// Функция для преобразования инфиксного выражения в постфиксное
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    for (char c : infix) {
        if (isdigit(c))
            postfix += c; // Если символ - цифра, добавляем его в постфикс
        else if (c == '(')
            st.push('(');
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // Удаляем '(' из стека
        } else {
            while (!st.empty() && hasHigherPrecedence(c, st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}


int main() {
    string infixExpression;
    cout << "Enter infix expression: ";
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    Node* root = buildTree(postfixExpression);
    int result = evaluateTree(root);
    cout << "Result: " << result << endl;

    return 0;
}