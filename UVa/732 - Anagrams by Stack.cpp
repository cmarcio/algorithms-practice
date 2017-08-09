#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

// global variables
string source, target;
vector<string> sequences;

void verify(char op, int s, int t, stack<char> mystack, string commands){
    //cout << op << " " << s << " " << t << "\n";
    //cout << commands << "\n";

    // pop operator
    if(op == 'o' && !mystack.empty()){        
        // pop is valid and target character matchs the stack top
        if(t < target.length() -1 && mystack.top() == target[t]){
            mystack.pop();
            verify('i', s, t+1, mystack, commands + "o ");
            verify('o', s, t+1, mystack, commands + "o ");
        }
        // pop is valid, is the last and matches the stack top
        else if (t == target.length() -1 && mystack.top() == target[t]){
            mystack.pop();
            sequences.push_back(commands + 'o');
        }
    }
    // push operator
    else if (op == 'i') {
        // current character on source is valid
        if(s < source.length()){
            mystack.push(source[s]); // put character on stack
            verify('i', s+1, t, mystack, commands + "i ");
            verify('o', s+1, t, mystack, commands + "i ");
        }
    }
}

void dfs(){
    stack<char> mystack;
    sequences.clear();
    verify('i', 0, 0, mystack, "");
    verify('o', 0, 0, mystack, "");
}

int main(){
    
    while(getline(cin, source)){
        getline(cin, target);
        dfs();
        cout << "[\n";
        for(int i = 0; i < sequences.size(); i++){
            cout << sequences[i] << "\n";
        }
        cout << "]\n";        
    }

    return 0;
}