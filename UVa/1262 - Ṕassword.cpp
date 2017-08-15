#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void read_grid(char grid[6][5]) {
    for ( int i = 0; i < 6; i++ ) {
        for ( int j = 0; j < 5; j++ ) {
            cin >> grid[i][j];
        }
    }
}

vector< vector<char> > grid_intersection(char lgrid[6][5], char rgrid[6][5]) {
    vector< map<char, int> > count(5);
    for ( int j = 0; j < 5; j++ ) {
        for ( int i = 0; i < 6; i++ ) {
            char c = lgrid[i][j];
            count[j][c] = 0;
        }
    }
    // merge the two grids in a map
    for ( int j = 0; j < 5; j++ ) {
        for ( int i = 0; i < 6; i++ ) {
            char c = rgrid[i][j];
            if( count[j].find(c) != count[j].end() ) {
                count[j][c] = 1;
            }
        }
    }
    // put the common elements of a column in an array (ascending order)
    vector< vector<char> > result;
    for ( int j = 0; j < 5; j++ ) {
        vector<char> column;
        for ( map<char,int>::iterator p = count[j].begin(); p != count[j].end(); p++ ) {
            if( p->second == 1 ){
                column.push_back(p->first);
            }
        }
        result.push_back(column);
    }
    return result;
}

string kth_password( vector< vector<char> > &grid, int kth ) {
    int count = 0;
    char s[5];
    for ( int i = 0; i < grid[0].size(); i++ ) {
        for ( int j = 0; j < grid[1].size(); j++ ) {
            for ( int k = 0; k < grid[2].size(); k++ ) {
                for ( int l = 0; l < grid[3].size(); l++ ) {
                    for ( int m = 0; m < grid[4].size(); m++ ) {
                        if ( ++count == kth ) {
                            s[0] = grid[0][i];
                            s[1] = grid[1][j];
                            s[2] = grid[2][k];
                            s[3] = grid[3][l];
                            s[4] = grid[4][m];
                            return s;
                        }
                    }
                }
            }
        }
    }
    return "NO";
}

int main() {
    int t, k;
    char grid_a[6][5], grid_b[6][5];
    vector< vector<char> > grid;

    cin >> t;
    for ( int i = 0; i < t; i++ ) {
        cin >> k;
        read_grid(grid_a);
        read_grid(grid_b);
        grid = grid_intersection(grid_a, grid_b);
        cout << kth_password(grid, k) << "\n";
        grid.clear();
    }

    return 0;
}