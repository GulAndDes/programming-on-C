#include <iostream>

using namespace std;

struct stack{
    int length;
    int *data; 
    int top; 
};


bool isEmpty (stack s);
void newStack(stack &s, int l);
stack newStack(int l);
void deleteStack(stack &s);
void pushStack(stack &s, int l);
int topStack(stack s);
void resizeStack(stack &s);
int pullStack(stack &s);
stack copyStack(stack s);
void copyStack(stack sd, stack ss);


int main() {
    stack first_stack = newStack(0);

    pushStack(first_stack, 3);
    pushStack(first_stack, 4);
    pushStack(first_stack, 5);
    pushStack(first_stack, 0);
    pushStack(first_stack, 7);;


    stack new_stack = newStack(0);
    cout << "First Stack\n";
    new_stack = copyStack(first_stack);

    while (not(isEmpty(first_stack))){
        cout << pullStack(first_stack) << " ";
    }

    cout << "\nCopy First Stack\n";
    while (not(isEmpty(new_stack))){
        cout << pullStack(new_stack) << " ";
    }
    cout << "\n";
    
    return 0;
}

bool isEmpty (stack s)
{
    if (s.top<0) return true;
    else return false;
}

void newStack(stack &s, int l){
    if (l > 0){
        s.data = new int [l];
        s.length = l;
        s.top = -1;
}
    else{
        s.data = NULL;
        s.length = 0;
        s.top = -1;
}
}
stack newStack(int l){
    stack res;
    res.top = -1;
    l<0?l = 0: 
    res.length = l;
    if (l) res.data = new int[l];
    else res.data = NULL;
    return res;
}

void deleteStack(stack &s){
    if ( s.length > 0) { delete [] s.data;}
    s.data = NULL;
    s.length = 0;
    s.top = -1;
}

void pushStack(stack &s, int l){
    if (s.length != 0){
	    if (s.top == s.length - 1) resizeStack(s); 
	    s.top ++;
	    s.data[s.top] = l;
}
    else{
        resizeStack(s);
        s.top ++;
        s.data[s.top] = l;
}
}


int topStack(stack s){
    if (isEmpty(s)) throw -1;
    return s.data[s.top]; 
}



void resizeStack(stack &s){
    stack res = newStack(s.length + 10);
    copyStack(res, s);
    deleteStack(s);
    s = res;
}

int pullStack(stack &s){
    if (isEmpty(s)) throw -1;
    s.top--;
    return s.data[s.top + 1];
}

stack copyStack(stack s){ //реализация s2 = copyStack(s1)
    stack res;
    res.length = s.length;
    res.top = s.top;
    if (s.data != NULL) res.data = new int[res.length];
    else res.data = NULL;
    for (int i = 0; i <= res.top; i++)
        res.data[i] = s.data[i];
    return res;
}
void copyStack(stack sd, stack ss){
    if (ss.top < sd.length) {
        for(int i =0; i<ss.top;i++)
	        sd.data[i] = ss.data[i];
        sd.top = ss.top;
}
    else{ 
        deleteStack(sd);
        sd = copyStack(ss);
}
}