// problem link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2899

#include <iostream>

using namespace std;

int main(){
    int T, N, c, max_speed;

    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> N;
        cin >> max_speed;
        for(int j = 1; j < N; j++){
            cin >> c;
            if(c > max_speed)
                max_speed = c;
        }
        cout << "Case " << (i+1) << ": " << max_speed << "\n";
    }

    return 0;
}