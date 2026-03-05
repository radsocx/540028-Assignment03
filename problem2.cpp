// compilation command:
// g++ problem2.cpp -o problem2
// run:
// ./problem2
// memory leak check:
// g++ -g -fsanitize=address problem2.cpp -o problem2

#include <iostream>
using namespace std;

struct DynArray {
    int *data;
    int size;
    int capacity;
};

void initArray(DynArray& a) {
    a.capacity = 2;
    a.size = 0;
    a.data = new int[a.capacity];
}

void freeArray(DynArray& a) {
    delete[] a.data;
    a.data = nullptr;
    a.size = 0;
    a.capacity = 0;
}

void resize(DynArray& a, int newCapacity) {
    int* newData = new int[newCapacity];
    for (int i = 0; i < a.size; i++) {
        newData[i] = a.data[i];
    }
    delete[] a.data;
    a.data = newData;
    a.capacity = newCapacity;
}

void pushBack(DynArray& a, int value) {
    if (a.size == a.capacity) {
        resize(a, a.capacity * 2);
    }
    a.data[a.size] = value;
    a.size++;
}

void insertAt(DynArray& a, int index, int value) {
    if (a.size == a.capacity) {
        resize(a, a.capacity * 2);
    }
    for (int i = a.size; i > index; i--) {
        a.data[i] = a.data[i - 1];
    }
    a.data[index] = value;
    a.size++;
}

void removeAt(DynArray& a, int index) {
    for (int i = index; i < a.size - 1; i++) {
        a.data[i] = a.data[i + 1];
    }
    a.size--;
}

int getAt(const DynArray& a, int index) {
    return a.data[index];
}

void setAt(DynArray& a, int index, int value) {
    a.data[index] = value;
}

void printDynArr(const DynArray& a) {
    cout << "[";
    for (int i = 0; i < a.size; i++) {
        cout << a.data[i];
        if (i < a.size - 1) cout << ", ";
    }
    cout << "] (size=" << a.size << ", cap=" << a.capacity << ")" << endl;
}

int main() {
    DynArray arr;
    initArray(arr);

    for (int i = 1; i <= 5; i++) pushBack(arr, i * 10);
    printDynArr(arr);

    insertAt(arr, 2, 25);
    printDynArr(arr);

    removeAt(arr, 0);
    printDynArr(arr);

    cout << "Element at index 2: " << getAt(arr, 2) << "\n";
    setAt(arr, 2, 99);
    printDynArr(arr);

    freeArray(arr);
}