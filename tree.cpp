#include <iostream>
#include <string>
#include <stack>
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

bool AriphmTree::is_operator() {  
    return (symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*' || symbol == '^');
}

int AriphmTree::priority(char c) { // приоритет оператора
    if (c == '*' || c == '/') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else if (c == '^') {
        return 3;
    } else {
        return -1;
    }
}

bool AriphmTree::is_char_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int AriphmTree::op_assoc(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        return 0;
    else // право ассоциативный оператор (^)
        return 1;
}

AriphmTree::AriphmTree(char c) {
    symbol = c; // присваиваем значения символа в вершину
    left = nullptr;
    right = nullptr;
}

AriphmTree::AriphmTree(const std::string& expression) {
    AriphmTree* created_tree = create(expression); // создаем дерево по выражению
    // присваивание под-дерева
    this->symbol = created_tree->symbol;
    this->left = created_tree->left;
    this->right = created_tree->right;
    // очистка вспомогательного дерева 
    created_tree->left = nullptr;
    created_tree->right = nullptr;
    delete created_tree; 
}

AriphmTree::AriphmTree(const AriphmTree& other) {
    // копирование символа
    this->symbol = other.symbol;

    // рекурсивное копирование под-деревьев слева
    if (other.left != nullptr) {
        this->left = new AriphmTree(*other.left);
    } else {
        this->left = nullptr;
    }

    // рекурсивное копирование под-деревьев справа
    if (other.right != nullptr) {
        this->right = new AriphmTree(*other.right);
    } else {
        this->right = nullptr;
    }
}


AriphmTree* AriphmTree::create(std::string expression) { 
    std::string pol_expression = ""; // создаем строку символово в обратной польской записи
    int size_str = expression.size();
    std::stack <char> st; // создаем стек
    //АЛГОРИТМ СОРТИРОВОЧНОЙ СТАНЦИИ ДЕЙКСТРЫ
    for (int i = 0; i < size_str; i++) {
        char c = expression[i];
        if (isspace(c)) continue;

        if (is_char_operator(c)) {
            for (;;) {
                if (st.empty()) {
                    break;
                }
                char _top = st.top();

                if (!is_char_operator(_top)) break;

                if (op_assoc(c) == 0 && (priority(c <= priority(_top))) || (op_assoc(c) == 1 && (priority(c) < priority(_top)))) {
                    pol_expression.push_back(_top);
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(c);
        } else if (isalpha(c) || isdigit(c)) {
            pol_expression.push_back(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                char _add = st.top();
                st.pop();
                pol_expression.push_back(_add);

            }

            if (st.empty()) {
                throw std::logic_error("missed left bracket\n");
            }
            st.pop();
        } else if (c == '(') {
            st.push(c);
        } else if (c == '\0') {
            break;
        } else {
            throw std::logic_error("invalid char\n");
        }

    }
    // если остались символы в стеке
    while(!st.empty()) {
        if (st.top() == '(') {
            throw std::logic_error("missed right bracket\n");
        }
        char tmp = st.top();
        pol_expression.push_back(tmp);
        st.pop();
    }

    size_str = pol_expression.size();
    std::stack<AriphmTree*> st_tree;
    //создаем дерево по обратной польской
    for (int i = 0; i < size_str; i++) {
        char c = pol_expression[i];

        if (!is_char_operator(c)) {
            // если не оператор, то просто кладем в стек
            AriphmTree* tmp = new AriphmTree(c);
            st_tree.push(tmp);
        } else {
            // если вытянули оператор, то подсоединяем под-деревья
            AriphmTree* _right = st_tree.top();
            st_tree.pop();
            AriphmTree* _left = st_tree.top();
            st_tree.pop();
            AriphmTree* op = new AriphmTree(c);
            op->left = _left;
            op->right = _right;
            st_tree.push(op);
        }

    }
    // возвращаем итоговое дерево с верхушки стека
    AriphmTree* res = st_tree.top();
    return res;
}


// печать дерева как в обычном бинарном дереве
void AriphmTree::print(int lvl) {
    if (this->is_operator()) {
        right->print(lvl + 1);
    }
    for (int i = 0; i < lvl; i++) {
        std::cout << "\t";
    }
    std::cout << symbol << std::endl;
    if (this->is_operator()) {
        left->print(lvl + 1);
    }
}

// деструктор дерева
AriphmTree::~AriphmTree() {
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }

}

//глубокое копирование дерева
AriphmTree* AriphmTree::tree_copy(AriphmTree* tree) {
    if (tree == nullptr) {
        return nullptr;
    }

    AriphmTree* tmp = new AriphmTree(tree->symbol);
    // копируем левую часть
    if (tree->left != nullptr) {
        tmp->left = tree_copy(tree->left);
    } else {
        tmp->left = nullptr;
    }
    // копируем правую часть
    if (tree->right != nullptr) {
        tmp->right = tree_copy(tree->right);
    } else {
        tmp->right = nullptr;
    }

    return tmp;
}


void AriphmTree::transform(AriphmTree* tree) {
    if (tree == nullptr) return;
    // если вершина символ возведения степени
    if (tree->is_operator() && tree->symbol == '^') {
        // берем левое под-дерево правого под-дерева
        AriphmTree* right_l;
        if (tree->right->left != nullptr) {
            right_l = tree->tree_copy(tree->right->left);
        } else {
            return;
        }
        // берем правое под-дерево правого под-дерева
        AriphmTree* right_r;
        if (tree->right->right != nullptr) {
            right_r = tree->tree_copy(tree->right->right);
        } else {
            return;
        }
        // копируем исходное дерево, но без под-деревьев правой части
        AriphmTree* tmp = tree->tree_copy(tree);
        tmp->right->left = nullptr;
        tmp->right->right = nullptr;
        // копируем исходное дерево еще раз, но без под-деревьев правой части
        AriphmTree* tmp2 = tree->tree_copy(tree);
        tmp2->right->left = nullptr;
        tmp2->right->right = nullptr;
        // очищаем правые части этих под-деревьев
        tmp->right = nullptr;
        tmp2->right = nullptr;
        // назначаем наши right_l, right_r вершины
        tmp->right = right_l;
        tmp2->right = right_r;
        // главному дереву меняем знак на *
        tree->symbol = '*';
        // перевязываем новые вершины к дереву
        tree->left = tmp;
        tree->right = tmp2;
        // вызываем рекусрию от левого и правого под-деревьев
        transform(tree->left);
        transform(tree->right);
    }
}

// вызов трансформации через метод без аргументов
void AriphmTree::applyTransformation() {
    transform(this);
}

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