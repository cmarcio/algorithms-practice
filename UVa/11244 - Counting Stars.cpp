#include <iostream>

using namespace std;

char sky[100][100];

void printSky(int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cout << sky[i][j] << " ";
        cout << "\n";
    }
}

bool checkNeighbors(int i, int j, int r, int c) {
    r--; c--;
    if (i > 0 && j > 0 && sky[i-1][j-1] == '*')
        return false;
    if (i < r && j < c && sky[i+1][j+1] == '*')
        return false;
    if (i > 0 && sky[i-1][j] == '*')
        return false;
    if (j > 0 && sky[i][j-1] == '*')
        return false;
    if (i < r && sky[i+1][j] == '*')
        return false;
    if (j < c && sky[i][j+1] == '*')
        return false;
    if (i > 0 && j < c && sky[i-1][j+1] == '*')
        return false;
    if (i < r && j > 0 && sky[i+1][j-1] == '*')
        return false;
    return true;
}

int countStars(int r, int c) {
    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++ ) {
            if (sky[i][j] == '*' && checkNeighbors(i, j, r, c)) {
                count++;
            }
        }
    }
    return count;
}


int main() {
    int r, c, count;
    string s;

    while ((cin >> r >> c) && r != 0) {
        getline(cin, s); // read the linebreak after r and c
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> sky[i][j];

        //printSky(r, c);
        count = countStars(r, c);
        cout << count << "\n";

    }

    return 0;
}