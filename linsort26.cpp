#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<typename T>
class Deque {
private:
    vector<int> data;
public:
    void pushFront(const int& value) {
        data.insert(data.begin(), value);
    }

    void pushBack(const int& value) {
        data.push_back(value);
    }

    bool empty() const {
        return data.empty();
    }

    void popFront() {
        if (!empty()) {
            data.erase(data.begin());
        }
    }

    void popBack() {
        if (!empty()) {
            data.pop_back();
        }
    }

    int front() const {
        if (!empty()) {
            return data.front();
        }
        throw -1;
    }

    int back() const {
        if (!empty()) {
            return data.back();
        }
        throw -1;
    }

    int findMax() const {
        if (empty()) {
            throw -1;
        }
        T maxElement = data[0];
        for (const auto& element : data) {
            if (element > maxElement) {
                maxElement = element;
            }
        }
        return maxElement;
    }

    void removeMax() {
        if (empty()) {
            throw -1;
        }
        T maxElement = findMax();
        data.erase(remove(data.begin(), data.end(), maxElement), data.end());
    }

    void print() const {
        for (const auto& element : data) {
            cout << element << " ";
        }
        cout << endl;
    }
};

int main() {
    Deque<int> deque;
    deque.pushFront(5);
    deque.pushBack(10);
    deque.pushFront(3);
    deque.pushBack(7);

    cout << "Deque: ";
    deque.print();

    cout << "Max element: " << deque.findMax() << endl;
    deque.removeMax();
    cout << "Deque after removing max: ";
    deque.print();

    return 0;
}