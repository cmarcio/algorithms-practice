#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

int main() {
    int n;
    string tree;
    
    cin >> n;
    getline(cin, tree);
    getline(cin, tree);
    for (int i = 0; i < n; i++) {
        map<string,int> forest;
        int total = 0;
        while (getline(cin, tree) && !tree.empty()) {
            forest[tree] += 1;
            total++;
        }
        double total_perc = 0;
        for (map<string,int>::iterator p = forest.begin(); p != forest.end(); p++) {
            double perc = ((p->second * 1.0) / (total * 1.0)) * 100.0;
            total_perc += perc;
            cout << p->first << " ";
            cout << fixed << setprecision(4) << perc << "\n";
        }
        if (i != n-1) cout << "\n";
    }

    return 0;
}