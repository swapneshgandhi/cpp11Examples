#include<iostream>
#include<cstring>
#include<cstdlib>

using namespace std;

int main(){
int n;
cout<<"Enter the number: ";
cin>>n;
int rem;
char op[32];
int i=0;
while (n){
rem=n%2;
n/=2;
sprintf(op[i++],"%d",rem);

cout<<rem;

}
cout<<endl;
while (i>0){
cout<<op[--i];
}

return 0;
}

