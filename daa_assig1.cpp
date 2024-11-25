#include <iostream>
#include <cmath>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

void printFibonacciIterative(int n) {
    int a = 0, b = 1, nextTerm;
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        nextTerm = a + b;
        a = b;
        b = nextTerm;
    }
    cout << "\nTime Complexity (Iterative): O(" << n << ") = " << n << " operations";
}

void printFibonacciRecursive(int n) {
    for (int i = 0; i < n; i++) {
        cout << fibonacciRecursive(i) << " ";
    }
    cout << "\nTime Complexity (Recursive): O(2^" << n << ") = " << pow(2, n) << " operations";
}

int main() {
    int n;
    cout << "Enter the number of terms: ";
    cin >> n;
    cout << "Fibonacci series (Recursive): ";
    printFibonacciRecursive(n);
    cout<<endl;
    cout << "Fibonacci series (Interative): ";
    printFibonacciIterative(n);
    return 0;
}
