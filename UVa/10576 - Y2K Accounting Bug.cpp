#include <iostream>

using namespace std;

int sum(int v[]) {
    int d = 0;
    for ( int i = 0; i < 12; i++ ) {
        d += v[i];
    }
    return d;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

bool valid(int months[], int position ) {
    int k = 5;
    for( int i = 0; i <= position-4; i++ ) {
        int subsum = 0;
        for ( int j = 0; j < 5; j++ ) {
            subsum += months[i + j];
        }
        if (subsum >= 0) return false;
    }
    return true;
}

int assign(int months[], int position, int value, int s, int d) {
    if ( position == 12 ) { // fim
        return sum(months);
    }

    months[position] = value;

    if ( !valid(months, position) ){
        return -1;
    }

    int a = assign(months, position+1, s, s, d );
    int b = assign(months, position+1, -d, s, d );
    return max(a, b);
}

int backtracking( int s, int d) {
    int months[12];

    int a  = assign(months, 0, s, s, d);
    int b = assign(months, 0, -d, s, d);
    int best = max(a, b);
    return ( best >= 0 ) ? best : -1;
}

int main() {
    int s, d;
    int months[12];

    while ( cin >> s >> d ) {
        int best = backtracking(s, d);
        if ( best == -1 ) {
            cout << "Deficit\n";
        }
        else {
            cout << best << "\n";            
        }
    }

    return 0;
}