#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Ashish_Donation{
    int lastIndex;
    unsigned long long* SquaredNum;
};

typedef struct Ashish_Donation Ashish_Donation;

void calcSquares(unsigned long long num, Ashish_Donation *donation){

    while (donation->lastIndex < num){

        donation->SquaredNum[++(donation->lastIndex)] = donation->SquaredNum[(donation->lastIndex)-1] + 
                                                        (donation->lastIndex) * (donation->lastIndex);

    }
}


int binarySearch(unsigned long long num, Ashish_Donation donation, int st , int end){

    int mid = st + (end-st)/2;
    int ind;

    if (donation.SquaredNum[mid] <= num && donation.SquaredNum[mid+1] > num ){
        ind=mid;
    }

    else if (donation.SquaredNum[mid] > num){
        ind=binarySearch(num,donation, st , mid-1);
    }

    else if (donation.SquaredNum[mid] < num){
        ind=binarySearch(num,donation, mid+1 , end);
    }
    return ind;
}

int main() {

    int TestCases;
    cin >> TestCases;

    int i;
    
    Ashish_Donation donation;

    unsigned long long size = pow (10,7);
    
    donation.SquaredNum = new unsigned long long[320000];
    
    if (donation.SquaredNum==0){
        cout << "No Memory" << endl;
    }
    
    memset(donation.SquaredNum,0,sizeof(donation.SquaredNum));

    donation.lastIndex=0;
    calcSquares(size, &donation);
    while (i++ < TestCases){
        unsigned long long num;
        cin  >> num;

       cout << binarySearch(num, donation, 0 , donation.lastIndex) << endl;

    }
    return 0;
}


