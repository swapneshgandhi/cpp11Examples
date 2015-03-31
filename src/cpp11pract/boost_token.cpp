// simple_example_2.cpp
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   string s;
   std::cin>>s;
   tokenizer<escaped_list_separator<char> > tok(s, escaped_list_separator<char>("\\", " ", "\""));
   for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
}

 
