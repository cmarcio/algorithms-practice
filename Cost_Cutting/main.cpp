#include <iostream>

using namespace std;

void bubbleSort(int vector[], int size){
    int tmp;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < (size-(i+1)); j++){
            if(vector[j] > vector[j+1]){
                tmp = vector[j+1];
                vector[j+1] = vector[j];
                vector[j] = tmp;    
            }
        }
    }
}

int main(){
    int T, x[3];

    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> x[0] >> x[1] >> x[2];
        bubbleSort(x, 3);
        cout << "Case " << (i+1) << ": " <<  x[1] << "\n";
    }

    return 0;
}