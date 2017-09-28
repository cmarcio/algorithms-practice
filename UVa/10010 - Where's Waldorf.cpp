#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

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
            cout << "a substring foi encontrada na posição = " << i - j << endl;
            j = b[j];
        }
    }
}

void printline(char s[], int size) {
    for (int i = 0; i < size; i++) {
        cout << s[i];
    }
    cout << "\n";
}

void readText(char text[][50], int m, int n) {
    char c;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c;
            text[i][j] = tolower(c);
            //cout << text[i][j];
        }
        //cout << "\n";
    }
}

void toLowercase(char s[], int size) {
    for (int i = 0; i < size; i++) {
        s[i] = tolower(s[i]);
        //cout << s[i];
    }
}

void readPattern(char pattern[100], int &p_size) {
    string s;
    getline(cin, s);
    strcpy(pattern, s.c_str());
    p_size = s.length();
    toLowercase(pattern, p_size);
    
    //cout << "\n";    
}

void getColumn(char text[][50], char column[], int m, int col) {
    for (int i = 0; i < m; i++) {
        column[i] = text[i][col];
    }
}

void findPattern(char text[][50], char pattern[], int m, int n, int p) {
    int b[100];
    char column[50];
    // search on the lines
    for (int i = 0; i < m; i++) {
        cout << "* Searching pattern "; printline(pattern, p);
        cout << "* On line "; printline(text[i], n);
        kmpPreProcess(b, pattern, p);
        kmpSearch(b, pattern, text[i], p, n);
        cout << "\n";
    }
    for (int i = 0; i < n; i++) {
        getColumn(text, column, m, i);
        cout << "* Searching pattern "; printline(pattern, p);
        cout << "* On Column "; printline(column, m);
        kmpPreProcess(b, pattern, p);
        kmpSearch(b, pattern, column, p, m);
        cout << "\n";
        
    }
}

int main() {
    int c, m, n, k, p;
    char letter, linebreak;
    char text[50][50];
    char pattern[100];

    cin >> c;
    //cout << c << "\n";
    for (int i = 0; i < c; i++) {
        //cin >> linebreak;
        cin >> m >> n;
        //cout << m << " " << n << "\n";
        readText(text, m, n);
        cin >> k;
        readPattern(pattern, p); // read the linebreak
        //cin >> linebreak;
        //cout << linebreak <<"\n";
        //cout << k;
        for (int j = 0; j < k; j++) {
            readPattern(pattern, p);
            printline(pattern, p);
            cout << "\n";
            findPattern(text, pattern, m, n, p);
        }

    }
    return 0;
}