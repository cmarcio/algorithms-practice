#include <iostream>
#include <cmath>

using namespace std;

double min_dist;

struct point {
    double x, y;
};

struct line {
    double a, b, c;
};

void newPoint(point &p, double x, double y) {
    p.x = x;
    p.y = y;
}

void newLine(line &l, point p1, point p2) {
    if (p1.x == p2.x) { // vertical line is handled nicely here
        l.a = 1.0;
        l.b = 0.0;
        l.c = -p1.x;
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0; // fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - (l.b * p1.y);
    }
}

void closestPoint(point m, line l, point &cp) {
    //cout << "m = (" << m.x << ", " << m.y << ")\n";
    //cout << "l = " << l.a << "X + " << l.b << "Y + " << l.c << "\n";
    
    cp.x = (1.0 * l.b * (l.b * m.x - l.a * m.y) - (l.a * l.c)) / ( pow(l.a, 2) + pow(l.b, 2) );
    cp.y = (1.0 * l.a * ((-l.b) * m.x + l.a * m.y) - (l.b * l.c)) / ( pow(l.a, 2) + pow(l.b, 2) );
    //cout << "cp = (" << cp.x << ", " << cp.y << ")\n";
}

double dist(point p1, point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return pow(dx, 2) + pow(dy, 2);
}

bool isOnSeg(point p1, point p2, point c) {
    if ( c.x > p1.x && c.x > p2.x) return false;
    if ( c.x < p1.x && c.x < p2.x) return false;
    if ( c.y > p1.y && c.y > p2.y) return false;
    if ( c.y < p1.y && c.y < p2.y) return false;
    return true;
}

bool isClosest( point p1, point p2, line l, point m, point &result ) {
    point cp;
    double d, d1, d2;

    closestPoint(m, l, cp); // point in line l closest to the point m
    d = dist(m, cp);        // distance between the closest point of l and m
    if (d < min_dist) {     // if the distance is smaller than the minimun distance
        if ( isOnSeg(p1, p2, cp) ) {            // if the closest point is on the trail size
            min_dist = d;
            newPoint(result, cp.x, cp.y);
            return true;
        }
        d1 = dist(p1, m);
        d2 = dist(p2, m);
        if (d1 < d2 && d1 < min_dist) {
            min_dist = d1;
            newPoint(result, p1.x, p1.y);
            return true;
        }
        else if (d2 < d1 && d2 < min_dist) {
            min_dist = d2;
            newPoint(result, p2.x, p2.y);
            return true;
        }
    }
    return false;
}

int main() {
    double x, y;
    int n;
    point m, p1, p2, result;
    line l;

    while(cin >> x >> y) {
        min_dist = 4000000;
        newPoint(m, x, y);
        cin >> n;
        cin >> x >> y;
        newPoint(p1, x, y);
        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            newPoint(p2, x, y);
            newLine(l, p1, p2);
            isClosest(p1, p2, l, m, result);
            newPoint(p1, p2.x, p2.y);
        }
        //cout << result.x << "\n" << result.y << "\n";
        printf("%.4f\n%.4f\n", result.x, result.y);
    }
    return 0;
}