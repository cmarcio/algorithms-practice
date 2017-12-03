#include <iostream>

using namespace std;

#define BOB 0
#define ALICE 1
#define EMPTY -111111

int n;
int slice[51];
int v[51][2];

void clearV(){
    for(int i = 0; i < 51; i++){
        v[i][BOB] = EMPTY;
        v[i][ALICE] = EMPTY;
    }
}

void printV(int person){
    for(int i = 0; i <= n; i++){
        cout << v[i][person] << " ";
    }
    cout << "\n";
}

int opt(int pos, int person){
    int next = person == BOB ? ALICE : BOB;
    cout << "PERSON: " << person << "\n";
    printV(person);

    if(pos < 0) return 0;

    if(v[pos][person] != EMPTY) return v[pos][person];

    //v[pos][person] = max(slice[pos] + (0 * opt(pos-1, next, 0)), opt(pos-1, person, 0));
    v[pos][person] = max(slice[pos] - opt(pos-1, next), opt(pos-1, person) - slice[pos]);

    return v[pos][person];
}
/*
int opt2() {
    for(int i = n; i >= 0; i++){

    }
}*/

int main(){
    int sum = 0;
    
    cin >> n;

    for(int i = n-1; i >= 0; i--){
        cin >> slice[i];
        sum += slice[i];
    }

    clearV();
    opt(n, BOB);

    printV(BOB);
    printV(ALICE);

    return 0;
}