#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

map<string,int> patterns;
int b[300];
char sequenceA[300], sequenceB[300];

// algoritmo disponibilizado pelo professor
void kmpPreProcess(int *b, char *pat, int tam_pat) {
    int i = 0;
    int j = -1;
    b[0] = -1;
    while (i < tam_pat) {
        while (j >= 0 && pat[i] != pat[j])
            j = b[j];
        i++; j++;
        b[i] = j;
    }
}

// algoritmo disponibilizado pelo professor
void kmpSearch(int *b, char *pat, char *text, int tam_pat, int tam_txt) {
    int i = 0;
    int j = 0;
    while (i < tam_txt) {
        while (j >= 0 && text[i] != pat[j]) 
            j = b[j];
        i++; j++;
        if (j == tam_pat) {
            //cout << "a substring foi encontrada na posição = " << i - j << endl;
            //j = b[j];
            string s(pat, tam_pat);
            patterns[s] += 1;
            return;
        }
    }
}

int min(int a, int b) {
    return a > b ? b : a;
}

void findRepetition(int size1, int size2, int k) {
    //strcpy(sequenceB, s2.c_str());
    if (size1 > size2) {
        for (int i = 0; i <= size1 - k; i++) {
            //strcpy(sequenceA, s1.substr(i, k).c_str());
            kmpPreProcess(b, &sequenceA[i], k);
            kmpSearch(b, &sequenceA[i], sequenceB, k, size2);
        }
    }
    else {
        for (int i = 0; i <= size2 - k; i++) {
            //strcpy(sequenceA, s1.substr(i, k).c_str());
            kmpPreProcess(b, &sequenceB[i], k);
            kmpSearch(b, &sequenceB[i], sequenceA, k, size1);
        }
    }
    
}

int main() {
    string s1, s2;
    int k;

    while (getline(cin, s1)) {
        getline(cin, s2);
        strcpy(sequenceA, s1.c_str());
        strcpy(sequenceB, s2.c_str());
        k = min(s1.length(), s2.length());
        while (k--) {
            patterns.clear();
            findRepetition(s1.length(), s2.length(), k+1);
            if (patterns.begin() != patterns.end()) {
                for (map<string,int>::iterator p = patterns.begin(); p != patterns.end(); p++ ) {
                    cout << p->first << "\n";
                }
                break;
            }
        }
        if (patterns.begin() == patterns.end()) cout << "No common sequence.\n";
        if (getline(cin, s1)) cout << "\n";
    }


    return 0;
}