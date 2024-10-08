#include<iostream>
#include<string>
using namespace std;

struct NodeBst{
    string key;
    NodeBst* data[10];
    int top;
    NodeBst(string k) { 
        key=k; data[10]={}; top=0;
        }
};


NodeBst* add(NodeBst* p, string kbst){
    if(!p){ 
        return new NodeBst(kbst);
        }

    p->data[p->top] = new NodeBst(kbst);
    p->top++;
    return p;
}


void print(NodeBst* node){
    int ans = atoi((node->key).c_str());
    for (int i = 1;i<atoi((node->data[0]->key).c_str()); i++){
        ans *= atoi((node->key).c_str());
    }
    cout << ans << endl;
}


void clear(char k[]){
    for (int i = 0; i < 5; i++){
        k[i] = 0;
    }
}


void create(string current, NodeBst* node){

    bool f = true;
    bool s = true;
    string var;

    for (int i = 0; i < current.length(); i++){

        if (current[i] == '^') {
            f = true;
            if (s){
                node = add(node, var);
                var.clear();
                s = false;
            }
        }

        else if (f){
            var += current[i];
            }
    }
    node = add(node, var);
    print(node);
}



int main() {
    NodeBst* root=nullptr;
    string a;
    cin >> a;

    create(a, root);
}