#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

/**
   Turn string s into a vector of types T
*/

using namespace boost;

template<class T>
void tokenizeV(const std::string &s,
               std::vector<T> &o)
{
  tokenizer<escaped_list_separator<char> > tok(s, escaped_list_separator<char>("\\", " ", "\""));
  for(tokenizer<escaped_list_separator<char> >::iterator j (tok.begin());
      j != tok.end();
      ++j)
  {

    o.push_back(boost::lexical_cast<T>(*j));
  }
}

int main(void)
{
  std::string buffer="23 23 12 121";
  //std::cin>>buffer;
  std::getline(std::cin,buffer);

  std::vector<std::string>v;
  tokenizeV(buffer,v);

  BOOST_FOREACH(const std::string &x, v)
    std::cout<<x<<",";
  std::cout<<std::endl;
}
