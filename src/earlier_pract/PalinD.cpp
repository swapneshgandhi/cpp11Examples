#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int isPalindrome (char *str , int len){
    
    int i=0;
    while (str[i++]){
        if (str[i] != str [len-1-i]){
            return i;
        }
    }
    return -1;
}

int main() {
 
    int T;
    cin >> T;
    char a[1005];
    char b[1005];
    
    
    while (T--){
    memset(&a,'\0',sizeof(a));
    memset(&b,'\0',sizeof(b));      
        cin >> a;
        cout << a;
        int l= strlen(a);
        int x=isPalindrome(a,l);
        
        if (x==-1){
            cout << x << endl;
        }
        else{
        int j=0;
        for (int i=0;a[i];i++){
            if (i!=x){b[j++]=a[i];}
        }
        
        if (isPalindrome(b,l-1)==-1){
            cout << x<< endl; 
        }
        else{
             cout << l-1-x << endl;
        }    
        }
    }    
    return 0;
}









