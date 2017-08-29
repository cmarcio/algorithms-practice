#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n, number, d;
    int seq[1000];
    int dif[1000];

    while ( cin >> number && number != 0 ) { // for each line of input
        seq[n++] = number;
        while ( cin >> number && number != 0 ) { // read each element of the line
            seq[n++] = number;
        }

        sort(seq, seq+n);   // sort the sequence of numbers

        for ( int i = 0; i < n-1; i++ ) {   // calc the difference between each pair of numbers
            dif[i] = seq[i+1] - seq[i];
        }

        d = 0;
        for ( int i = 0; i < n-1; i++ ) { // calc gcd of each pair
            d = gcd(d, dif[i]);
        }

        cout << d << "\n";
        n = 0;
    }
    return 0;
}