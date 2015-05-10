#include <iostream>
#include <string>

using namespace std;
int main() {

	string inString;

	getline(cin,inString);
	int Testcase= stoi(inString);

	for (int i=0;i<Testcase;i++){
	getline(cin,inString);

	int end=inString.find(" ");

	int NRows=stoi(inString.substr(0, end - 0));

	int MCols=stoi(inString.substr(end+1, inString.length()));
	char FirstChar='\0';
	char prevLine='\0';

	for (int n=0;n<NRows;n++)   {
		getline(cin,inString);
		char FirstChar=inString[0];
		for (int m=0;m<MCols;m++){

			if (!(FirstChar==inString[m])) {
				cout<<"NO"<<endl;
			}
		}

		if (prevLine==FirstChar){
			cout<<"NO"<<endl;
		}
		prevLine=inString[0];
	}

	cout<<"YES"<<endl;

	}
	return 0;
}
