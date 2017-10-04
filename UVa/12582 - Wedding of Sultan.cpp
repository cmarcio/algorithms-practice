#include <iostream>
#include <string>
#include <map>

using namespace std;

void erase(string &s, int a, int b) {
    string new_s;
    for(int i = 0; i < s.length(); i++) {
        if (i != a && i != b)
            new_s.push_back(s[i]);
    }
    s = new_s;
}

map<char,int> countPaths(string s) {
    map<char,int> spk_count;
    int origin = 0;
    int destin = 1;

    while (s.length() > 0) {
        /*cout << s << "\n";        
        cout << "origin " << origin << " -> " << s[origin] << "\n";
        cout << "destin " << destin << " -> " << s[destin] << "\n";
        cout << "\n";*/
        if(s[origin] == s[destin]) {
            erase(s, origin, destin);
            origin--;
            destin--;
        }
        else {
            spk_count[s[origin]] += 1;
            spk_count[s[destin]] += 1;
            origin++;
            destin++;
        }
    }
    return spk_count;
}

int main() {
    int t;
    string sequence;

    cin >> t;
    getline(cin, sequence);
    
    for (int i = 0; i < t; i++) {
        getline(cin, sequence);
        map<char,int> paths = countPaths(sequence);
        cout << "Case " << i + 1 << "\n";
        for (map<char,int>::iterator p = paths.begin(); p != paths.end(); p++) {
            cout << p->first << " = " << p->second << "\n";
        }
        //cout << sequence << "\n";
    }

    return 0;
}