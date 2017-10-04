#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

int b[1000];
char sequence[1000];
map<string,int> patters_count;
map<string,bool> patters_seen;


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
            j = b[j];
            string s(pat, tam_pat);
            patters_count[s] = patters_count[s] + 1;
            patters_seen[s] = true;
        }
    }
}

bool findMostRepeated() {
    int max_count = 0;
    string biggest;
    for (map<string,int>::iterator p = patters_count.begin(); p != patters_count.end(); p++) {
        //cout << p->first << " " << p->second << "\n";
        if (p->second >= max_count) {
            biggest = p->first;
            max_count = p->second;
            //cout << p->second << "\n";
        }
    }
    if (max_count > 1) {
        cout << biggest << " " << max_count << "\n";
        return true;
    } else
        return false;
}

bool findBiggestSubstring(string s){
    strcpy(sequence, s.c_str());
    int k = s.length();
    while (--k) {
        patters_count.clear();
        patters_seen.clear();
        for(int i = 0; i <= (s.length() - k); i++) {
            //cout << i << " " << k << "\n";
            //cout << s.substr(i, k) << "\n";
            if ( !patters_seen[ s.substr(i, k) ]) {
                kmpPreProcess(b, &sequence[i], k);
                kmpSearch(b, &sequence[i], sequence, k, s.length());
            }
        }
        if (findMostRepeated())
            return true;
        //cout << "aqui " << k << "\n";
    }
    return false;
}

int main() {
    int t;
    string s;

    cin >> t;
    getline(cin, s);
    while (t--) {
        getline(cin, s);
        if (!findBiggestSubstring(s))
            cout << "No repetitions found!\n";
    }

    return 0;
}