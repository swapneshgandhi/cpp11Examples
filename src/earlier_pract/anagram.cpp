#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int countA[26]; 
int countB[26];

int findDiff(){
    int count=0;
    for (int i=0;i<26;i++){
        
        count+=abs(countA[i]-countB[i]);
        
    }
    return count;
    
}
   

int main() {
   string a;
   string b;
   int t;
    
    cin >> t;
    
    while (t--){
   
     memset(countA,0,sizeof(countA));
     memset(countB,0,sizeof(countB));
        
     string complstr;   
     cin >> complstr;
        
     if (complstr.length() %2!=0){
         cout << "-1" << endl;
         continue;
     }
        
     int i=0;
     a.clear();
     b.clear();
     while (i<complstr.length()){
         
         if (i<complstr.length()/2){
         countA[complstr[i]-97]+=1;
         }
         else{
         countB[complstr[i]-97]+=1;
         }
         i++;
     }
    
        cout << findDiff() <<endl;
        
    }
    
    return 0;
}

