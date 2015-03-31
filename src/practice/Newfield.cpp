#include <stack>
#include <iostream>
#include <string>

using namespace std;

bool isOpeningBracket(char bracket){

	if ( bracket == '{' || bracket == '(' || bracket == '['){
		return true;
	}

	else{
		return false;
	}

}

bool isBracketClosed(char Opening, char Closing){

	switch (Opening) {
	case '(':
		return (')'==Closing);

	case '{':
		return ('}'==Closing);

	case '[':
		return (']'==Closing);

	default:
		return false;
	}
}

/*
 * Complete the function below.
 */
string braces(string value) {
	stack<char>helperStack;

	int i=0;

	while (i<value.length()){

		if (isOpeningBracket(value[i])){
			helperStack.push(value[i]);
		}

		else {
			char TopChar=helperStack.top();
			if (!isBracketClosed(TopChar,value[i])){
				return "NO";
			}
			helperStack.pop();
		}
		i++;
	}

	if(helperStack.empty()){
		return "YES";
	}
	return "NO";
}

int main(){
	string s="asas";
	cout<<braces(s);
}


