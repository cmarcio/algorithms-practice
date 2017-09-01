#include <iostream>

using namespace std;

int main() {
    int k, mod, N;

    while ( cin >> N ) {
        k = 0;
        mod = 1 % N;
        while ( mod ) {
            k++;
            mod = (mod * 10 + 1) % N;
        }
        cout << k+1 << "\n";
    }

    return 0;
}