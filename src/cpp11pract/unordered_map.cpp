#include <map>
#include <iostream>

using namespace std;

class demo
{

public:
	int a, b,;

friend ostream &operator<<( ostream &output, 
                                       const demo &D )
{ 
         output << "a : " << D.a << " b : " << D.b;
         return output;            
}

};

int main(){
// here is how declare my map:

demo ptr;

std::map<int, demo> my_map;

ptr.a=12;
ptr.b=23;

my_map.insert(std::make_pair(12, ptr));

 std::cout << "mymap contains:\n";
  for (std::map<int, demo>::iterator it = my_map.begin(); it!=my_map.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}
