#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;




void isFibo(unsigned long long Num){
    
 unsigned long long prev=1,curr=1;   
 unsigned long long temp=0;
    
 while (curr < Num){
     
     temp=prev;
     prev=curr;
     curr+=temp;
     
     if (curr == Num || Num == 1){
         cout << "IsFibo" << endl;
         return;
     }
     
 }
    cout << "IsNotFibo"<< endl;
    
}

int main() {
  
    const int MaxNum = 10 << 10;
    
    string ReadLine;
    getline(cin,ReadLine);
    
    int NumTests=stoull(ReadLine,NULL);
    
    unsigned long long Num; 
    
    for (int i=0; i<NumTests ; ++i){
    
    getline(cin,ReadLine);
        
    Num=stoull(ReadLine,NULL);    
    
    if (!MaxNum >= Num){
        cout << "IsNotFibo"<< endl;
    }
    else{
    isFibo(Num);
    }                

    }
    
    return 0;
}

