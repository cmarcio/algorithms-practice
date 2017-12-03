#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

#define VALUE_SIZE 20

int M[VALUE_SIZE][201];
//int value[VALUE_SIZE];
int weight[VALUE_SIZE];

void clearM() {
    for(int i = 0; i < VALUE_SIZE; i++){
        for(int j = 0; j < 201; j++){
            M[i][j] = -1;
        }
    }
}

int p(int j, int t) {
    for(int i = j; i >= 0; i--) {
        if(t - weight[i] >= 0)
            return i;
    }
    return -1;
}

int computeOpt(int n, int l) {
    if(n == -1) return 0;
    if(M[n][l] != -1){
        return M[n][l];
    }

    int l2 = l - weight[n];

    if (l2 >= 0) {
        M[n][l] = max(weight[n] + computeOpt(n-1, l2), computeOpt(n-1, l));
    }
    else {
        M[n][l] = computeOpt(n-1, l);
    }
    //cout << "[" << n << "][" << l << "] = " << M[n][l] <<"\n";
    
    return M[n][l];
}

void getLuggage(string s, int &n, int &w){
    //cout << "IN\n";
    w = 0, n = 0;
    char * pch;
    char str[1000];
    strcpy(str, s.c_str());
    pch = strtok (str," ");
    while (pch != NULL){
        weight[n++] = atoi(pch);
        pch = strtok (NULL, " ");
        w += weight[n-1];
    }
    //cout << "OUT\n";
}

int main(){
    int m, n, w;
    string s;

    cin >> m;
    getline(cin, s);
    while(m--) {
        clearM();        
        getline(cin, s);
        getLuggage(s, n, w);
        if (w % 2 == 0 && (computeOpt(n-1, w/2) == w/2))
            cout << "YES\n";
        else cout << "NO\n";
        //cout << w << "  " << computeOpt(n-1, w/2) << "\n";
    }

    return 0;
}