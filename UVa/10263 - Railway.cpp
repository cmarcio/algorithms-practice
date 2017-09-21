#include <iostream>

using namespace std;

struct point {
    float x, y;
};

void newPoint(point &p, float x, float y) {
    p.x = x;
    p.y = y;    
}

v

int main() {
    float x, y;
    int n;
    point m, p;

    while(cin >> x >> y) {
        newPoint(m, x, y);
        cin >> n;
        for(int i = 0; i <= n; i++) {
            cin >> x >> y;
            newPoint(p, x, y);
            float dist = dist
        }
    }

    return 0;
}