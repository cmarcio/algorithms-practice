#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

long long sieve_size;
bitset<20000010> bs;
vector<long long> primes;
vector<long long> twins;

void checktwins() {
    int last = primes.size() -1;
    if ( primes.size() > 1 && primes[last] == primes[last - 1] + 2 ) {
        twins.push_back(primes[last-1]);
    }
}

void sieve(long long upperbound) {
    int count = 0;
    sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for ( long long i = 2; i <= sieve_size; i++ )
        if ( bs[i] ) {
            for ( long long j = i * i; j <= sieve_size; j += i )
                bs[j] = 0;
            primes.push_back( (int) i );
            checktwins();
        }
}

int main() {
    int s;
    long long twin = 0;

    sieve(20000000);
    while ( cin >> s ) {
        cout << "(" << twins[s-1] << ", " << twins[s-1] + 2 << ")\n";
    }

    return 0;
}