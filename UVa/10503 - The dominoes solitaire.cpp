#include <iostream>
#include <vector>

using namespace std;

int dominos[7][7];

bool exist_domino(int a, int b) {
    if (a >= 0 && a <= 6 && b >= 0 && b <= 6 && dominos[a][b] > 0){
        return true;
    }
    else { return false; }
}

void add_domino(int a, int b) {
    if (a >= 0 && a <= 6 && b >= 0 && b <= 6) {
        dominos[a][b] += 1;
        dominos[b][a] += 1;
    }
    else {
        cout << "1 - invalide piece!\n";
    }
}

void remove_domino(int a, int b) {
    if (a >= 0 && a <= 6 && b >= 0 && b <= 6 && exist_domino(a,b)) {
        dominos[a][b] -= 1;
        dominos[b][a] -= 1;
    }
    else {
        cout << "2 - invalide piece!\n";
    }
}

bool place_domino( pair<int,int> l, pair<int,int> r, int n) {
    //cout << n << ": " << l.first << " " << l.second << "\n";
    if (n == 0) {
        return ((l.second == r.first)); //|| (l.second == r.second));
        
    }
    
    for (int i = 0; i <= 6; i++) {
        if (exist_domino(l.second,i)) {
            remove_domino(l.second, i);
            if ( place_domino( make_pair(l.second, i), r, n-1 ) ){
                //cout << l.second << " " << i << "| ";
                return true;
            }
            else {
                add_domino(l.second, i);
            }
        }
    }
    return false;
}

void erase_dominos() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            dominos[i][j] = 0;
        }
    }
}



int main() {
    int n, m, x, y;
    pair <int,int> left, right;

    while ((cin >> n >> m) && (m != 0)) {
        cin >> x >> y;
        left = make_pair(x,y);
        cin >> x >> y;        
        right = make_pair(x,y);
        erase_dominos();
        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            add_domino(x,y);
        }
        if (place_domino(left, right, n)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}