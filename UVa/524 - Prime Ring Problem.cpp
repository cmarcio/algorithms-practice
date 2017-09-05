#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>

using namespace std;

long long sieve_size;
bitset<10000010> bs;
vector<int> primes;
int ring_size;

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

bool primesum(int a, int b) {
    return bs[a+b];
}

void printring(int ring[]) {
    int i;
    for (i = 0; i < ring_size-1; i++)
        cout << ring[i] << " ";
    cout << ring[i] << "\n";
}

void primeRings(int step, int current, int ring[], bool visited[]) {
    ring[step] = current;
    bool current_visited[17];
    memcpy(current_visited, visited, 17);

    current_visited[current] = true;
    if (step == ring_size -1) { // ultimo circulo
        if (primesum(current, 1)) 
            printring(ring);
        return;
    }
    for (int i = 2; i <= ring_size; i++) {
        if (!visited[i] && primesum(current, i))
            primeRings(step+1, i, ring, current_visited);
    }
}

void printspace(bool &first) {
    if (first)
        first = false;
    else cout << "\n";
}

int main() {
    int n, count = 1;
    int ring[16];
    bool visited[17], first = true;

    sieve(32);
    while (cin >> n) {
        printspace(first);
        ring_size = n;
        for(int i = 0; i < 17; i++) visited[i] = false;
        cout << "Case " << count++ << ":\n";
        primeRings(0, 1, ring, visited);

    }
    return 0;
}