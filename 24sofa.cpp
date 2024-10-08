#include <iostream>
#include <string>
using namespace std;

struct NodeBst {
    string key;
    NodeBst* data[100];
    int top;
    NodeBst(string k) {
        key = k;
        for (int i = 0; i < 100; i++) data[i] = nullptr;
        top = 0;
    }
};

NodeBst* add(NodeBst* p, string kbst) {
    if (!p) {
        return new NodeBst(kbst);
    }
    p->data[p->top] = new NodeBst(kbst);
    p->top++;
    return p;
}

bool isNegatedExpression(const string& expr) {
    return expr.size() > 1 && expr.front() == '(' && expr[1] == '-' && expr.back() == ')';
}

void print(NodeBst* node) {
    if (node == nullptr) return;
    cout << node->key;
    for (int i = 0; i < node->top; i++) {
        if (node->data[i]->key == "-") {
            if (i + 2 < node->top && (node->data[i + 2]->key == "*" || node->data[i + 2]->key == "/")) {
                if (i >= 2 && node->data[i - 1]->key == "(" && node->data[i - 2]->key == "+") {
                    cout << "-" << node->data[i + 1]->key << " " << node->data[i + 2]->key << " " << node->data[i + 3]->key;
                    i += 3;
                } else {
                    cout << " + (-(" << node->data[i + 1]->key << " " << node->data[i + 2]->key << " " << node->data[i + 3]->key << "))";
                    i += 3;
                }
            } else {
                if (isNegatedExpression(node->data[i + 1]->key)) {
                    cout << " " << node->data[i + 1]->key;
                } else {
                    if (i >= 2 && node->data[i - 1]->key == "(" && node->data[i - 2]->key == "+") {
                        cout << "-" << node->data[i + 1]->key;
                    } else {
                        cout << " + (-" << node->data[i + 1]->key << ")";
                    }
                }
                i++;
            }
        } else if (node->data[i]->key == "+" || node->data[i]->key == "*" || node->data[i]->key == "/") {
            cout << " " << node->data[i]->key << " " << node->data[i + 1]->key;
            i++;
        }
    }

    cout << endl;
}

void create(string current, NodeBst* &node) {
    string var;
    bool firstMinus = false;

    for (int i = 0; i < current.length(); i++) {
        char c = current[i];

        if (c == '-' || c == '+' || c == '*' || c == '/') {
            if (!var.empty()) {
                node = add(node, var);
                var.clear();
            }

            if (i == 0 && c == '-') {
                firstMinus = true;
            } else {
                node = add(node, string(1, c));
            }
        } else {
            var += c;
        }
    }

    if (!var.empty()) {
        node = add(node, var);
    }

    if (firstMinus && node != nullptr && node->top > 0) {
        cout<<'-';
        NodeBst* minusNode = new NodeBst("-");
        minusNode->data[0] = node->data[0];
        minusNode->top = 1;
        node->data[0] = minusNode;
    }

    print(node);  
}

int main() {
    NodeBst* root = nullptr;
    string input;
    cout << "Enter: ";
    getline(cin, input);
    create(input, root);  
}
