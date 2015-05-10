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
returns YES if string provided to it is a valid brace.
pushes each charatcer to stack if it is an opening brace.
 and checks to see if an closing brace corresponds to brace
 at the top of the stack.
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
	string s="{()}[]()";
	cout<<braces(s);
}


