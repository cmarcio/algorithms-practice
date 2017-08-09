#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

void bubblesort(int vector[], int size){
    int tmp;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - (i+1); j++){
            if(vector[j] > vector[j+1]){
                tmp = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = tmp;                    
            }
        }
    }
}

int main(){
    int n, mult;
    int courses[5];
    string key;
    //ostringstream convert;

    while(scanf("%d", &n) != EOF && n != 0){
        map<string, int> match;    
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 5; j++){
                cin >> courses[j];
            }
            bubblesort(courses, 5);
            key = "";
            for(int j = 0; j < 5; j++){
                string str = static_cast<ostringstream*>( &(ostringstream() << courses[j]) )->str();
                //convert << courses[j];
                key += str;
            }
            if(match.find(key) == match.end()){
                match[key] = 1;
            }else {
                match[key] = match[key] + 1;
            }
        }
        int max = 1;
        int count = 1;
        for(map<string, int>::iterator p = match.begin(); p != match.end(); p++){
            if( (p->second) > max){
                max = p->second;
                count = 1;
            }
            else if((p->second) == max && max != 1){
                count++;
            }
        }
        if(max == 1){
            cout << n << "\n";
        }else{
            cout << max * count << "\n";
        }
    }

    return 0;
}