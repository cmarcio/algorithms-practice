#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define VALUE_SIZE 30

int M[VALUE_SIZE][1001];
int value[VALUE_SIZE];
int cost[VALUE_SIZE];
int w;

void clearM() {
    for(int i = 0; i < VALUE_SIZE; i++){
        for(int j = 0; j < 1001; j++){
            M[i][j] = -1;
        }
    }
}

vector<int> getTrasures(int n, int l, int gold) {
    vector<int> t;
    for(int i = n-1; i >= 0; i--){
        //cout << i << "[" << i << "][" << l << "] = " << gold << "\n";
        if((i == 0 || M[i][l] != M[i-1][l]) && M[i][l] == gold){
            t.push_back(i);
            gold -= value[i];
            l -= cost[i]*3*w;
        }
    }
    return t;
}

int p(int j, int t) {
    for(int i = j; i >= 0; i--) {
        if(t - (cost[i] * w * 3) >= 0)
            return i;
    }
    return -1;
}

int computeOpt(int n, int l) {
    if(n == -1) return 0;

    if(M[n][l] != -1){
        return M[n][l];
    }

    int l2 = l - (3 * w * cost[n]);

    if (l2 >= 0) {
        M[n][l] = max(value[n] + computeOpt(p(n-1, l2), l2), computeOpt(n-1, l));
    }
    else {
        M[n][l] = computeOpt(n-1, l);
    }
    return M[n][l];
}

int main() {
    int t, n, d, v, gold;
    vector<int> treasures;
    bool first = true;

    while(cin >> t >> w) {
        if (first) first = false;
        else cout << "\n";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d >> v;
            cost[i] = d;
            value[i] = v;
        }
        clearM();
        gold = computeOpt(n-1, t);
        cout << gold << "\n";
        treasures = getTrasures(n, t, gold);
        cout << treasures.size() << "\n";
        for (int i = treasures.size()-1; i >= 0; i--){
            int j = treasures[i];
            cout << cost[j] << " " << value[j] << "\n";
        }
    }
    
    return 0;
}