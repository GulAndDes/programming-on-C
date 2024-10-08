#include <iostream>

using namespace std;

struct Queue{
    int length;
    int *data;
    int start;
    int depth;
};

bool isEmptyQueue(const Queue &);
Queue newQueue(int);
void deleteQueue(Queue &);
void pushQueue(Queue &, int);
int topQueue(const Queue &);
void resizeQueue(Queue &, int);
int pullQueue(Queue &);
void copyQueue(Queue &,const Queue &); 

int main() {
    Queue first_queue = newQueue(0);
    pushQueue(first_queue, 1);
    pushQueue(first_queue, 2);
    pushQueue(first_queue, 3);
    pushQueue(first_queue, 4);
    pushQueue(first_queue, 5);

    Queue new_queue = newQueue(0);
    cout << "First Queue\n";
    while(not(isEmptyQueue(first_queue))){
        pushQueue(new_queue, topQueue(first_queue));
        cout << pullQueue(first_queue) << " ";
    }
    
    cout << "\nCopy First Queue\n";
     while(not(isEmptyQueue(new_queue))){
        cout << pullQueue(new_queue) << " ";
    }
    cout << "\n";

    return 0;
}


bool isEmptyQueue(const Queue &q){
    return q.depth == 0;
}


Queue newQueue(int l){
    if (l<0) throw -1;
    Queue q;
    q.length = l;
    q.data = NULL;
    if (l>0) q.data = new int [l];
    q.start = 0;
    q.depth = 0;
    return q;
}


void deleteQueue(Queue &q){
    if (q.length != 0) delete[]q.data;
    q.data = NULL;
    q.depth = 0;
    q.start = 0;
}


void pushQueue(Queue &q, int k){
    if (q.length == q.depth) 
        resizeQueue(q, 10);
    q.data[(q.start + q.depth) % q.length] = k;
    q.depth ++;
}


int topQueue (const Queue &q){
    if (q.depth == 0) throw -2;
    return q.data[q.start];
}


void resizeQueue(Queue &q, int dl = 10){
    Queue nq = newQueue(q.length + dl);
    copyQueue(nq, q);
    deleteQueue(q);
    q = nq;
}


int pullQueue(Queue &q){
    if (isEmptyQueue(q)) throw -3;
    int k = q.data[q.start];
    q.depth--;
    q.start = (q.start+1)%q.length;
    return k;
}


void copyQueue(Queue& q, const Queue& qs) {
    if (q.length < qs.depth)
        resizeQueue(q, qs.depth - q.length);
    for(int i = 0; i < qs.depth; i++)
        q.data[i] = qs.data[(qs.start + i) % qs.length];
    q.start = 0;
    q.depth = qs.depth;
}