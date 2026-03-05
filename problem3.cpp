// compilation command:
// g++ problem3.cpp -o problem3
// run:
// ./problem3
// memory leak check:
// g++ -g -fsanitize=address problem3.cpp -o problem3

#include <iostream>

using namespace std;

int linearSearch(int* arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int* arr, int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int* generateSortedArray(int n) {
    if (n <= 0) return nullptr;
    
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }
    return arr;
}

void runTest(int n) {
    int* arr = generateSortedArray(n);
    
    int midIdx = n / 2;
    int targetExists = arr[midIdx];
    int targetMissing = -5; 

    int linRes1 = linearSearch(arr, n, targetExists);
    int binRes1 = binarySearch(arr, n, targetExists);
    
    int linRes2 = linearSearch(arr, n, targetMissing);
    int binRes2 = binarySearch(arr, n, targetMissing);

    cout << "n = " << n << endl;
    cout << "Target " << targetExists << ": Lin=" << linRes1 << " Bin=" << binRes1 << endl;
    cout << "Target " << targetMissing << ": Lin=" << linRes2 << " Bin=" << binRes2 << endl;
    cout << "Match: " << (linRes1 == binRes1 && linRes2 == binRes2 ? "Yes" : "No") << "\n" << endl;

    delete[] arr;
}

int main() {
    int sizes[] = {10, 100, 1000};
    
    for (int n : sizes) {
        runTest(n);
    }

    return 0;
}