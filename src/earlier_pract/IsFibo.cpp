#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
determines if a number is a part of fibonacci sequence or not.
*/


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
    //read number of tests to be performed
    getline(cin,ReadLine);

    //convert to int
    int NumTests=stoull(ReadLine,NULL);
    
    unsigned long long Num; 

    //perform the tests
    for (int i=0; i<NumTests ; ++i){

    getline(cin,ReadLine);

    //the number to be tested for being a fibo number.
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

