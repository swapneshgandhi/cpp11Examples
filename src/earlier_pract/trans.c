#include <stdio.h>
#include <iostream>
const static int maxn = 1010;
const static long long modulo = 1000000007;

int n, k;
char alice_string[maxn];

void read_data(){
	std::cin >> n >> k;
	scanf("%s", alice_string);		
}

void solve(){
	long long result;
	long long C[maxn][maxn];

	for (int i = 0; i <= n; ++i){
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i-1][j]+C[i-1][j-1])%modulo;
	}

//	total trans
	result = 0;
	for (int i = 0; i <= k; i++)
		result = (result + C[n][i])%modulo;
//	std::cout<<"total:"<<result<<std::endl;	
	

//	invalid
	long long total_uniq[maxn];
	for (int repeat = 1; repeat <= n/2; ++repeat){
		if (n % repeat != 0) continue;
		
		long long total[maxn];
		for (int i = 0; i <= k; ++i)
			total[i] = 1;

		for (int i = 0; i < repeat; ++i){
			int t0 = 0, t1 = 0;
			int pos = i;
			while (pos<n){
				if (alice_string[pos] == '0') 
					t0 ++;	
				else
					t1 ++;
				pos += repeat;
			}
			for (int change = k; change >=0; --change){
				long long tmp = 0;
				if (change - t0 >= 0) tmp += total[change-t0];
				if (change - t1 >= 0) tmp += total[change-t1];
				total[change] = tmp%modulo;
			}
			
		}
		total_uniq[repeat] = total[k];
		for (int i = 1; i <= repeat/2; ++i)
			if (repeat % i == 0)
				total_uniq[repeat] = (total_uniq[repeat] - total_uniq[i] + modulo) % modulo;

		result = (result + modulo - total_uniq[repeat]) % modulo;	
	}
	std::cout<<result<<std::endl;
}

int main(){
	int T;
	std::cin >> T;
	while (T>0){
		read_data();
		solve();
		T--;
	}	
	return 0;
}

