#include <iostream>
#include <bitset>
#include <vector>
#include <map>
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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * ( b / gcd(a, b));
}

int main() {
    int t, a, b, c;

    sieve(10000000);

    cin >> t;
    for ( int i = 0; i < t; i++ ) {
        cin >> a >> c;
        b = 1;
        if ( c % a == 0 ) {
            map<int,int> a_fac = primeFactors(a);
            map<int,int> c_fac = primeFactors(c);
            for ( map<int,int>::iterator p = c_fac.begin(); p != c_fac.end(); p++) {
                int factor = p->first;
                int exponent = p->second;
                if ( exponent > a_fac[factor] ) {
                    b *= pow(factor, exponent);
                }
            }
            cout << b << "\n";
        }
        else 
            cout << "NO SOLUTION\n";
    }


    return 0;
}