#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct point {
    int x, y;
    bool operator<(const point& p) const {
        return x < p.x;// sort by x
    }
};

void newPoint(point &p, int x, int y) {
    p.x = x;
    p.y = y;
}

double distance(point p1, double x, double y) {
    double dx, dy;
    dx = x - p1.x;
    dy = y - p1.y;
    return sqrt( pow( dx, 2 ) + pow( dy, 2 ) );
}

double sunnyDistance(point p1, point p2, int h) {
    double m = ((p2.y - p1.y) * 1.0) / (p2.x - p1.x);
    double x = (((h - p1.y) * 1.0 ) / m) + p1.x;
    return distance(p1, x, h);
}

int main() {
    int c, n;
    int x, y, height;
    double dist;
    point points[100];

    cin >> c;
    for (int i = 0; i < c; i++) {
        cin >> n;
        height = 0;
        dist = 0;
        for (int j = 0; j < n; j++) {
            cin >> x >> y;
            newPoint(points[j], x, y);
        }
        sort(points, points + n);
        for (int j = n-1; j >= 0; j--) {
            //cout << points[j].x << " ";
            if (points[j].y > height) {
                dist += sunnyDistance(points[j], points[j+1], height);
                height = points[j].y;                
            }
        }
        //cout << dist << "\n";
        printf("%.2f\n", dist);        
    }
    return 0;
}