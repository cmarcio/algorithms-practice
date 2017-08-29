#include <iostream>

using namespace std;

int length_array[1000000];

int cycle_length(int n) {
    if ( n == 1 ) {
        return 1;        
    }
    if ( n < 1000000 && length_array[n] != 0 ){
        return length_array[n];
    }
    
    if ( n % 2 == 0 ) {
        n = n/2;
    }
    else {
        n = (n * 3) + 1;
    }
    return 1 + cycle_length(n);
}

int max(int i, int j) {
    return (i > j) ? i : j;
}

void swap(int &a, int &b) {
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int max_cycle_length(int a, int b) {
    if ( a > b ) {
        swap(a, b);
    }
    int max_l = cycle_length(a);
    for ( int i = a+1; i <= b; i++ ) {
        int new_l = cycle_length(i);
        length_array[i] = new_l;
        max_l = max(max_l, new_l);
    }
    return max_l;
}

int initialize_length_array() {
    for ( int i = 0; i < 1000000; i++ ) {
        length_array[i] = 0;
    }
}

int main() {
    int i, j, length;

    initialize_length_array();
    while ( cin >> i >> j ) {
        length = max_cycle_length(i, j);
        cout << i << " " << j << " " << length << "\n"; 
    }

    return 0;
}