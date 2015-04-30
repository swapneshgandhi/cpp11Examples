#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
 
    int T;
    cin >> T;
    
    while (T--){
        string input;
        cin >> input;
        int i;
        for (i=input.length()-2;i>=0;--i){
            
            if (input[i]<input[i+1]) break;
            
        }
        
    
        if (i==-1){
            cout << "no answer" << endl;
            continue;
        }
        
        int second;
        for (int j=i ; j < input.length() ; j++){
            second=i+1;
            if (input[i]<input[j] && input[j] < input[second]){
                second=j;
            }     
        }
            char c=input[i];
            input[i]=input[second];
            input[second]=c;
            sort(input.begin()+i+1,input.end());
       
      
        cout << input << endl;
    }
    
    return 0;
}

