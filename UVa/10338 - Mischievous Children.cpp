#include <iostream>
#include <map>
#include <string>

using namespace std;

unsigned long long factorial(int n) {
    return ( n == 1 ) ? 1 : n * factorial(n-1);
}

int main() {
    int n;
    char c;
    string word;
    map<char, int> letters;
    unsigned long long result;

    cin >> n;
    getline(cin, word);
    for ( int i = 0; i < n; i++ ) {
        getline(cin, word);        
        letters.clear();
        for ( int j = 0; j < word.length(); j++ ) {
            c = word[j];
            if ( letters.find(c) == letters.end() )
                letters[c] = 1;
            else
                letters[c] = letters[c] + 1;
        }
        result = factorial(word.length());
        for ( map<char,int>::iterator p = letters.begin(); p != letters.end(); p++ ) {
            if ( p->second > 1 ) {
                result /= factorial(p->second);
            }
        }
        cout << "Data set " << i+1 << ": " << result << "\n";
    }

    return 0;
}