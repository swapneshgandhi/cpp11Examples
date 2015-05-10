#include <iostream>
#include <fstream>
#include <string>	
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <cstdio>

class Record{
public:
std::string type;
double start_time;
double end_time;

	bool operator < (const Record& Rec) const {
        return (start_time < Rec.start_time);
    }
    
};

using namespace std;
void createSortedVectors(const vector <Record> Records, vector <vector<Record>> &Schedules){

vector<Record>::const_iterator RecordIt=Records.begin();
vector<vector<Record>>::iterator ScheduleIt;

bool Inserted=false;

	while (RecordIt!=Records.end()){
	
	for (ScheduleIt=Schedules.begin();ScheduleIt!=Schedules.end();ScheduleIt++){
		
		if ( (*ScheduleIt).empty() || (*ScheduleIt).back().end_time < RecordIt->end_time){
			(*ScheduleIt).push_back(*RecordIt);
			Inserted=true;
		}
		
	}
	
	if(Inserted==false){
	vector<Record> newVector;
	Schedules.push_back(newVector);
	}

	else{
	RecordIt++;
	}

	}

}


int main ()
{
  //std::unordered_map<std::string,double> myrecipe;

  ifstream inf("Sample.dat");
 
    // If we couldn't open the output file stream for writing
    if (!inf)
    {
        // Print an error and exit
        cerr << "Uh oh, Sample.dat could not be opened for writing!" << endl;
        exit(1);
    }
	string eachLine;  
  	vector<string> strs;
	vector <Record> Records;
  	vector<string>::iterator it;
	Record newRecord;
  	
  	while (getline(inf,eachLine)){
  		
  		boost::split(strs, eachLine	, boost::is_any_of("\t "));
		it=strs.begin();
		newRecord.type=*it;
		newRecord.start_time=stod(*(++it),NULL);
		newRecord.end_time=stod(*(++it),NULL);
  		Records.push_back(newRecord); 
  	}
  	
  	sort(Records.begin(),Records.end());
  	
  	vector<vector<Record>> Schedules;
  	
  	createSortedVectors(Records,Schedules);
  	
    return 0;
}
