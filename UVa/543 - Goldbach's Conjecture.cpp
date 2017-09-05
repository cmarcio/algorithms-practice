#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

long long sieve_size;
bitset<10000010> bs;
vector<int> primes;

void sieve(long long upperbound) {
    sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for ( long long i = 2; i <= sieve_size; i++ )
        if ( bs[i] ) {
            for ( long long j = i * i; j <= sieve_size; j += i )
                bs[j] = 0;
            primes.push_back( (int) i );
        }
}

int main() {
    int n, dif;

    sieve(1000000);

    while (cin >> n && n != 0) {
        for (int i = 0; primes[i] < n; i++) {
            dif = n - primes[i];
            if ( bs[dif] ) {
                cout << n << " = " << primes[i] << " + " << dif << "\n";
                break;
            }
        }
        if (!bs[dif]) {
            cout << "Goldbach's conjecture is wrong.\n";
        }
    }

    return 0;
}