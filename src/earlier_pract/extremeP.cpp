#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<stdio.h>
#include<map>
#include<ext/hash_map>
#include<ext/hash_set>
#include<set>
#include<string>
#include<assert.h>
#include<vector>
#include<time.h>
#include<queue>
#include<deque>
#include<sstream>
#include<stack>
#include<sstream>
#define MA(a,b) ((a)>(b)?(a):(b))
#define MI(a,b) ((a)<(b)?(a):(b))
#define AB(a) (-(a)<(a)?(a):-(a))
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define pob pop_back
#define ep 0.0000000001
#define pi 3.1415926535897932384626433832795

using namespace std;
using namespace __gnu_cxx;
const long long P=1000000000+7;
const int N=5001;

int n,m,i,j,kk,k,l,r;
int a[N];
long long d[N],dd[N];
int main()
{
    cin>>n>>k>>l;
    for (i=1;i<=k;i++)
    {
        cin>>j;
        a[j]|=1;
        a[j+1]|=2;
    }
    for (i=1;i<=l;i++)
    {
        cin>>j;
        a[j]|=2;
        a[j+1]|=1;
    }
    for (i=2;i<=n;i++)
    if (a[i]==3) {cout<<0<<endl; return 0;}
    d[1]=1;
    for (i=2;i<=n;i++)
    {
        for (j=1;j<=n;j++)
            d[j]=(d[j]+d[j-1])%P;
        if (a[i]==2)
        {
            for (j=1;j<=i;j++)
            dd[j]=d[j-1];
        } else
        if (a[i]==1)
        {
            for (j=1;j<=i;j++)
            dd[j]=(d[n]-d[j-1]+P)%P;
        }else
            for (j=1;j<=i;j++)
            dd[j]=d[n];

        for (j=1;j<=n;j++) d[j]=0;
      for (j=1;j<=i;j++)
    d[j]=dd[j];
    // for (j=1;j<=i;j++)
   //  cout<<d[j]<<" ";cout<<endl;
    }
    long long ans=0;
    for (i=1;i<=n;i++) ans=(ans+d[i])%P;
    cout<<ans<<endl;
    return 0;
}

