#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int,int> P;

struct compare_first { // comparison function for priority queue
    constexpr bool operator()(pair< int, P > const & a, 
        pair< int, P > const & b) const noexcept
    { return a.first > b.first; }
};

int config[10000]; // all the possible configurations for the game
priority_queue< pair< int,P >, vector< pair< int,P > >, compare_first > pq; // priority queue for configurations

int digToInt(int v[]) {
    return (1000 * v[0]) + (100 * v[1]) + (10 * v[2]) + (v[3]); 
}

void intToDig(int n, int v[]) {
    for ( int i = 0; i < 4; i++ ) {
        v[i] = n / pow(10, 3-i);
        n -= v[i] * pow(10, 3-i);
    }
}

void clearConfig() {
    for ( int i = 0; i < 10000; i++ ) {
        config[i] = false;
    }
}

void readConfig(int v[]) {
    for ( int i = 0; i < 4; i++ ) {
        cin >> v[i];
    }
}

void setVisited(int i) {
    config[i] = true;
}

bool isVisited(int n) {
    return config[n];
}

void copyValue(int s[], int t[]) {
    for ( int i = 0; i < 4; i++ ) {
        t[i] = s[i];
    }
}

void getChildren(int parent, int children[8]) {
    int value[4], base[4];

    intToDig(parent, base);
    for ( int i = 0; i < 4; i++ ) {
        copyValue(base, value);
        value[i] = ( base[i] != 0 ) ? base[i] - 1 : 9;    // press left button for digit i
        children[2*i] = digToInt(value);
        value[i] = ( base[i] != 9 ) ? base[i] + 1 : 0;    // press right button for digit i
        children[2*i+1] = digToInt(value);        
    }
}

int hcost(int x, int y) {
    int s[4], t[4]; 
    intToDig(x, s);
    intToDig(y, t);

    int cost = 0;
    for ( int i = 0; i < 4; i++ ) {
        int d = abs( s[i] - t[i] );
        cost += min(d, 9 - d);
    }
    return cost;
}

void addToQueue(int children[8], int depth, int t) {
    for ( int i = 0; i < 8; i++ ) {         // validate possible next children
        if ( !isVisited(children[i]) ) {
            setVisited(children[i]);
            int cost = depth + hcost(children[i], t);// + heuristic(children[i], t);
            pq.push( make_pair(cost, make_pair(children[i], depth+1) ));
        }
    }
}

int A_Star(int s[], int t[]) {
    pq = priority_queue< pair< int,P >, vector< pair< int,P > >, compare_first > ();
    int children[8];    
    int current = digToInt(s);
    int last = digToInt(t);

    if ( !isVisited(current) ) {
        setVisited(current);
        pq.push( make_pair(0, make_pair(current, 0) ));
        while ( !pq.empty() ) {
            current = pq.top().second.first;
            int depth = pq.top().second.second;
            int cost = pq.top().first;
            pq.pop();
            if ( current == last ) return depth;
            getChildren(current, children);
            addToQueue(children, depth, last);
        }
    }
    return -1;
}

int main() {
    int t, n;
    int source[4], target[4], forbidden[4];   // source and targe configurations

    cin >> t;
    for ( int i = 0; i < t; i++ ) {
        readConfig(source);
        readConfig(target);
        clearConfig();  // initialize the config matrix
        cin >> n;
        for ( int j = 0; j < n; j++ ) {
            readConfig(forbidden);
            setVisited(digToInt(forbidden));
        }
        int x = A_Star(source, target);
        cout << x << "\n";
    }

    return 0;
}