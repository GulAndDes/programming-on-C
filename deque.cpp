#include <iostream>
using namespace std;

template<typename T>
struct Node {
    int data;
    Node<T>* prev;
    Node<T>* next;

    Node(T data = T(), Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : data(data), prev(prev), next(next) {}
};

template<typename T>
class Deque {
private:
    Node<T>* front = -1;
    Node<T>* end;
    int size;

public:

    Deque() : front(nullptr), end(nullptr), size(0) {}

    ~Deque() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }
    bool isEmpty(){
        return size == 0; 
    }
    void addFront(T value) {
        Node<T>* newNode = new Node<T>(value, nullptr, front);
        if (front != nullptr) {
            front->prev = newNode;
        }
        front = newNode;
        if (end == nullptr) {
            end = front;
        }
        size++;
    }

    void addend(T value) {
        Node<T>* newNode = new Node<T>(value, end, nullptr);
        if (end != nullptr) {
            end->next = newNode;
        }
        end = newNode;
        if (front == nullptr) {
            front = end;
        }
        size++;
    }

    T removeFront() {
        if (front == nullptr) {
            throw runtime_error("Deque is empty");
        }
        T value = front->data;
        Node<T>* temp = front;
        front = front->next;
        if (front != nullptr) {
            front->prev = nullptr;
        } else {
            end = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    T removeend() {
        if (end == nullptr) {
            throw runtime_error("Deque is empty");
        }
        T value = end->data;
        Node<T>* temp = end;
        end = end->prev;
        if (end != nullptr) {
            end->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
        size--;
        return value;
    }
    
    T getMax() {
        if (size == 0) {
            throw runtime_error("Deque is empty");
        }
        T maxVal = front->data;
        Node<T>* current = front;
        while (current != nullptr) {
            if (current->data > maxVal) {
                maxVal = current->data;
            }
            current = current->next;
        }
        return maxVal;
    }

    void removeMax() {
        T maxVal = getMax();
        if (front->data == maxVal) {
            removeFront();
        } else if (end->data == maxVal) {
            removeend();
        } else {
            Node<T>* current = front->next;
            while (current != nullptr && current->data != maxVal) {
                current = current->next;
            }
            current->prev->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            delete current;
            size--;
        }
    }
    void print() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
        }

        Node<T>* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Deque<int> deque;
    deque.addFront(5);
    deque.addend(10);
    deque.addFront(3);
    deque.addend(15);
    cout << "Max element: " << deque.getMax() << endl;
    cout<<"Deque: ";
    deque.print();
    deque.removeMax();
    cout << "Deque after removing max: ";
    deque.print();

    return 0;
}