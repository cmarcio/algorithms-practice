#include <iostream>
#include <bitset>
#include <map>
#include <vector>
#include <cmath>

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

map<int,int> primeFactors(long long N) {
    map<int,int> factors;
    long long PF_idx = 0;
    long long PF = primes[PF_idx];
    while ( N != 1 && (PF * PF <= N) ) {
        while ( N % PF == 0 ) {
            N /= PF;
            factors[PF]++;
        }
        PF = primes[++PF_idx];
    }
    if ( N != 1 ) factors[N]++;
    return factors;
}

bool isdivisible(int n, int m) {
    int a, b;
    map<int,int> mfac = primeFactors(m);
    for (map<int,int>::iterator p = mfac.begin(); p != mfac.end(); p++) {
        a = p->first;
        b = p->second;
        for (int i = a; i <= n; i += a) {
            map<int,int> ifac = primeFactors(i);
            b -= ifac[a];
            if (b <= 0) break;
        }
        if (b > 0) return false;
    }
    return true;
}

int main() {
    int n, m;
    sieve(1000000);
    while (cin >> n >> m) {
        if (m <= n || isdivisible(n, m))
            cout << m << " divides " << n << "!\n";
        else
            cout << m << " does not divide " << n << "!\n";    
    }

    return 0;
}