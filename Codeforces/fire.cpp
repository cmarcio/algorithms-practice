#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_ITEMS 100
#define MAX_VALUE 21
#define MAX_TIME 2001
#define EMPTY -1

struct Item {
    int t, d, p, order;
};

int n;
int max_time;
Item item[MAX_ITEMS];
int m[MAX_ITEMS][MAX_TIME];
vector<int> saved;

void clearM(){
    for(int i =0; i < MAX_ITEMS; i++)
        for(int j = 0; j < MAX_TIME; j++)
            m[i][j] = EMPTY;
}

int next(int current_i, int time_left){
    //cout << "################" << "\nCurrent i = " << current_i << "\n";
    int j = current_i;
    int current_time = max_time - time_left;
    while(--j >= 0){
        //cout << "j = " << j << ", current time = " << current_time << ", time left = " << time_left << "\n";
        //cout << "time to save j = " << item[j].t << ", time after j will be burned = " << item[j].d <<"\n";
        if(item[j].t <= time_left && item[j].d > item[j].t + current_time)
            return j;
    }
    //cout << "burn\n";
    return -1;
}

int opt(int i, int T){
    //cout << "i = " << i << " tleft = " << T << "\n";
    if(i < 0) return 0;

    if(m[i][T] != EMPTY) return m[i][T];

    int time_left = T - item[i].t;
    m[i][T] = max( item[i].p + opt( next(i, time_left), time_left), opt(next(i, T), T) );
    return m[i][T];
}

void resultSet(int i, int T){
    while(i >= 0){
        int time_left = T - item[i].t;
        int next_a = next(i, time_left);
        int next_b = next(i, T);
        if(item[i].p + opt( next_a, time_left) >=  opt(next_b, T)) {
            //cout << "i = " << i << " t = " << T << "\n";
            saved.push_back(item[i].order);
            i = next_a;
            T = time_left;
        }
        else {
            i = next_b;
        }
    }
}

bool compare_d(const Item &a, const Item &b){
    return a.d > b.d;
}

bool compare_p(const Item &a, const Item &b){
    return a.p < b.p;
}

int main(){
    int max_value, m;

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> item[i].t >> item[i].d >> item[i].p;
        item[i].order = i+1;
    }
    
    clearM();
    
    sort(item, item+n, compare_d);
    //stable_sort(item, item+n, compare_d);
    
    max_time = item[0].d;
    //cout << max_time << "\n";
    max_value = opt(next(n, max_time), max_time);
    cout << max_value << "\n";

    resultSet(next(n, max_time), max_time);

    cout << saved.size() << "\n";
    for(int i = 0; i < saved.size(); i++)
        cout << saved[i] << " ";
    cout << "\n";

    return 0;
}