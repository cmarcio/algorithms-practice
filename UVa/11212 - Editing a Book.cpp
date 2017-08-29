#include <iostream>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

struct cutpaste {
    char config[10];        // vector with this state configuration
    int depth;              // depth in the backtracking tree
};

typedef struct cutpaste Op;

struct compare_cost { // comparison function for priority queue
    constexpr bool operator()
    (pair< int, Op > const & a, pair< int, Op > const & b) const noexcept
        { return a.first > b.first; }
};

priority_queue< pair<int,Op>, vector< pair<int,Op> >, compare_cost > pqueue;

unsigned long digToUlong(char v[], int n) {
    unsigned long number = 0;
    for ( int i = 1; i <= n; i++ ) {
        number += pow(10, n-i) * (int) v[i];
    }
    return number;
}

void ulongToDig(unsigned long number, char v[], int n) {
    for ( int i = 1; i <= n; i++ ) {
        v[i] = number/pow(10, n-i);
        number = number % (int) pow(10, n-i);
    }
}

bool isOrdered(char v[], int size) {
    for ( int i = 1; i <= size; i++ ) {
        if ( (int) v[i] != i ) return false;
    }
    return true;
}

void copyDig(char source[], char target[], int n) {
    for (int i = 1; i <= n; i++ ) {
        target[i] = source[i];
    }
}

void printDig(char v[], int n) {
    for ( int i = 1; i <= n; i++ ) {
        cout << (int) v[i];
    }
    cout << "\n";
}

int hcost(char permutation[], int n) {
    int d = 0;
    /*for ( int i = 1; i <= n; i++ ) {
        d += abs((int ) permutation[i] - i);
    }*/
    for ( int i = 0; i < n; i++ ) {
        if ( permutation[i] + 1 != permutation[i + 1] )
            d++;
    }
    //d = digToUlong(permutation,n) - 123456789;
    return d;
}

void permutLeft(char source[], char permutation[], int set_size, int origin, int destin) {
    copyDig(source, permutation, 9);
    for ( int i = 0; i < set_size; i++ ) {
        permutation[destin+i] = source[origin+i];
    }
    for ( int i = 0; i < origin-destin; i++ ) {
        permutation[destin+set_size+i] = source[destin+i];        
    }
    /*cout << "k:" << set_size << " origin:" << origin << " destin:" << destin << "\n";
    cout << "permutation: ";
    printDig(permutation, 9);*/   
}

void permutRight(char source[], char permutation[], int set_size, int origin, int destin) {
    copyDig(source, permutation, 9);
    for ( int i = 0; i < set_size; i++ ) {
        permutation[destin+i] = source[origin+i];
    }
    for ( int i = 0; i < destin-origin; i++ ) {
        permutation[origin+i] = source[origin+set_size+i];        
    }    

    /*cout << "k:" << set_size << " origin:" << origin << " destin:" << destin << "\n";
    cout << "permutation: ";
    printDig(permutation, 9);*/
}

int getPermutations(char permutations[][10], char current[], int n) {
    int count = 0;
    for ( int k = 1; k <= n-1; k++ ) {      // set size
        for ( int i = 1; i <= n+1-k; i++ ) {  // subset to move [i, .. , i+k]
            for ( int j = i-1; j > 0; j --) { // move to left
                permutLeft(current, permutations[count++], k, i, j);                
            }
            for ( int j = i+k; j <= n-k+1; j++ ) {   // move to right
                permutRight(current, permutations[count++], k, i, j);
            }
        }
    }
    return count;
}

int A_Star( char v[], int n) {
    Op first, current, newop;
    int psize, cost;
    char permutations[1000][10];

    // esvazia fila
    pqueue = priority_queue< pair<int,Op>, vector< pair<int,Op> >, compare_cost > ();
    // cria estrutura de nós visitados
    map<unsigned long, bool> visited;

    // coloca primeiro na fila
    first.depth = 0;
    copyDig(v, first.config, n);
    pqueue.push( make_pair(0, first) );
    // enquanto a fila não estiver vazia
    while ( !pqueue.empty() ) {
        // tira da fila
        current = pqueue.top().second; pqueue.pop();
        //printDig(current.config, n);
        // marca como visitado
        visited[digToUlong(current.config, n)] = true;
        // se chegou no estado final retorna
        if ( isOrdered(current.config, n) ) return current.depth;
        // pega possíveis filhos
        psize = getPermutations(permutations, current.config, n);
        // coloca filhos na fila    
        for ( int i = 0; i < psize; i++ ) {
            // se não foi visitado
            if ( visited.find( digToUlong(permutations[i], n) ) == visited.end() ) {
                // marca como visitado
                visited[digToUlong(permutations[i], n)] = true;
                // calcula o custo
                newop.depth = current.depth + 1;                
                cost = newop.depth + hcost(permutations[i], n);
                copyDig(permutations[i], newop.config, n);
                //cout << "permutation: ";
                //printDig(newop.config, n);
                //cout << "cost: " << cost << "\n";
                
                // coloca na fila
                pqueue.push( make_pair(cost, newop) );
            }
        }
        //cout << "---------------------------------------\n";
    }
    return -1;
}

int main() {
    int n, number;
    char v[10];
    v[0] = 0;
    int j = 1;
    while ( cin >> n && n != 0 ) {
        for ( int i = 1; i <= n; i++ ) {
            cin >> number;
            v[i] = number;
        }
        int depth = A_Star(v, n);
        cout << "Case " << j++ << ": ";
        cout << depth << "\n";
    }
    
    return 0;
}