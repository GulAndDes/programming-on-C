#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data = T(), Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node = nullptr) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    void push_back(T data) {
        if (head == nullptr) {
            head = new Node(data);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(data);
        }
        ++size;
    }

    void pop_front() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
            --size;
        }
    }

    int length() const {
        return size;
    }
    
    void printList()  {
        for (auto it = begin(); it != end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    void remove_kth(int k) {
        if (k < 1 || k > size) return;

        Node* prev = nullptr;
        Node* current = head;
        int index = 1;
        while (current != nullptr && index < k) {
            prev = current;
            current = current->next;
            ++index;
        }

        if (current == nullptr) return;

        if (prev == nullptr) {
            head = current->next;
        } 
        else {
            prev->next = current->next;
        }

        delete current;
        --size;
    }
    void remove_every(LinkedList<T>& list, int k){
        for (int i = k; i <= list.length(); i+=k){
            list.remove_kth(i);
            i -= 1;
        }
    }
    
};


int main() {
    LinkedList<char> list;
    int k;
    list.push_back('A');
    list.push_back('B');
    list.push_back('C');
    list.push_back('D');
    list.push_back('E');
    list.push_back('M');
    
    cin>>k;
    cout<<endl;
    cout << "List: ";
    list.printList();
    cout << endl;

    list.remove_every(list, k);
    cout << "After removing every k element: ";
    list.printList();
    cout << endl;

    cout << "List length: " << list.length() << endl<<endl;

    list.remove_kth(1);
    cout << "List after removing element: ";
    list.printList();

    return 0;
}