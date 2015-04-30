#include <cstring>
#include <cstdlib>
#include <iostream>

int factorial(int n){
	int c,fact=1;

	for (c = 1; c <= n; c++)
		fact = fact * c;

	return fact;
}


char* insertCharAt(int pos, char c, char *str){
	int i=0;
	while (i<pos){
		str++;
	}

	char temp;

	while (*str!='\0'){
		temp=*str;
		*str=c;
		c=temp;
		str++;
	}

}

char** permute(char *str){


	char **permute_array = new char*[100];
	for (int i=0;i<100;i++){
		permute_array[i]=new char[strlen(str)+2];
	}

	if(str==NULL){
		return NULL;
	}

	else if (strlen(str)==0){
		strcpy(permute_array[0],"");
		return permute_array;
	}


	char first=*str;
	char rem[strlen(str)-1];

	strncpy(rem,(str+1),strlen(str)-1);

	char **old_permute=permute(rem);

	int j=0;

	while(strlen(old_permute[j])>0){
		int k;
		for (k=0; k<strlen(old_permute[j]);k++){
			strcpy(permute_array[j],insertCharAt(k,first,old_permute[j]));

		}
	}
	return permute_array;

}

int main ()
{
	char str[]="abcd";
	char** ans=permute(str);

	for (int i=0;strlen(ans[i])>0;i++){
	std::cout << "myvector stores " << ans[i] << " \n";
	}
	return 0;
}

