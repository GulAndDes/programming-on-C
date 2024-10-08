#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int TABLE_SIZE = 10;

// Структура элемента таблицы
struct TableElement {
    int key;
    int data;
};

// Функция для сортировки таблицы методом шейкерной сортировки
void shakerSort(TableElement arr[], int n) {
    bool swapped;
    int start = 0;
    int end = n - 1;

    do {
        swapped = false;
        // Проход справа налево
        for (int i = end - 1; i >= start; i--) {
            if (arr[i].data > arr[i + 1].data) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Если ничего не поменялось, массив уже отсортирован

        swapped = false;
        // Проход слева направо
        for (int i = start + 1; i <= end; i++) {
            if (arr[i].data < arr[i - 1].data) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        end--; // Уменьшаем область поиска на каждом проходе

    } while (start < end);
}

TableElement binarySearch(TableElement arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].key == key) {
            return arr[mid];
        } else if (arr[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return TableElement{-1, -1}; // Элемент не найден
}

int main() {
    int table_size;
    cout<<"Enter table size:"<<endl;
    cin>>table_size;
    TableElement arr[table_size];
    cout << "Enter key and elements:" << endl;
    for (int i = 0; i < table_size; ++i) {
        cin >> arr[i].key >> arr[i].data;
    }

    cout << "source table:" << endl;
    cout<<endl;
    cout<<"Key - Elem:"<<endl;
    for (int i = 0; i < table_size; ++i) {
        cout << arr[i].key << " - " << arr[i].data << endl;
    }
    // сортировка
    shakerSort(arr, table_size);
    cout << "sorted table:" << endl;
    cout<<endl;
    cout<<"Key - Elem:"<<endl;
    for (int i = 0; i < table_size; ++i) {
        cout << arr[i].key << " - " << arr[i].data << endl;
    }

    //двоичный поиска
    int searchKey;
    cout << "Enter key: ";
    cin >> searchKey;
    TableElement result = binarySearch(arr, table_size, searchKey);
    if (result.key != -1) {
        cout << "Elem find: " << result.data << endl;
    } else {
        cout << "Elem not found." << endl;
    }

    return 0;
}