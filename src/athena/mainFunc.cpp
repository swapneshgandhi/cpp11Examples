#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

class AccountPositions {
public:
	std::string AccountNumber;
	std::string Symbol;
	int Quantity;
	float Price;

	std::string getAccountNumber() const {
		return AccountNumber;
	}

	void setAccountNumber(std::string accountNumber) {
		AccountNumber = accountNumber;
	}

	float getPrice() const {
		return Price;
	}

	void setPrice(float price) {
		Price = price;
	}

	int getQuantity() const {
		return Quantity;
	}

	void setQuantity(int quantity) {
		Quantity = quantity;
	}

	std::string getSymbol() const {
		return Symbol;
	}

	void setSymbol(std::string symbol) {
		Symbol = symbol;
	}

};

int ParseQuantity(string Quantity){

	std::size_t found=Quantity.find_first_of(')', 0);

	if (found==std::string::npos){
		return atoi(Quantity.c_str());
	}

	else{
		string Number=Quantity.substr( Quantity.find_first_of('(', 0)+1, ( Quantity.find_first_of(')', 0)) );
		return -1*atoi(Number.c_str());
	}
}


int main(int argc, char* argv[]){

	int c;
	char *FileName;

	while ((c = getopt (argc, argv, "f:")) != -1)
		switch (c)
		{
		case 'f':
			if(!optarg){
				fprintf(stderr,"Usage server -f [FileName] ");
				exit(1);
			}
			FileName = optarg;
			break;

		case '?':
			fprintf(stderr,"Usage server -f [FileName] ");
			return 1;
		default:
			fprintf(stderr,"Usage server -f [FileName] ");
			exit(1);
		}

	if(argc!=3){
		fprintf(stderr,"Usage server -f [FileName] ");
		exit(1);
	}


	ifstream inf(FileName);

	// If we couldn't open the output file stream for writing
	if (!inf)
	{
		// Print an error and exit
		cerr << "Uh oh, Sample.dat could not be opened for writing!" << endl;
		exit(1);
	}
	string eachLine;
	vector<string> strs;

	vector<string>::iterator it;
	AccountPositions newRecord;

	boost::unordered_map<string,vector<AccountPositions> > AccountMap;

	getline(inf,eachLine);

	while (getline(inf,eachLine)){
		vector<AccountPositions> Records;

		boost::split(strs, eachLine	, boost::is_any_of(","));
		it=strs.begin();
		newRecord.setAccountNumber(*it);
		newRecord.setSymbol(*(++it));

		int Quantity=ParseQuantity(*(++it));
		newRecord.setQuantity(Quantity);

		newRecord.setPrice(atof((*(++it)).c_str()));

		if (AccountMap.find(newRecord.getAccountNumber())!= AccountMap.end()){
			boost::unordered_map<string,vector<AccountPositions> >::const_iterator got = AccountMap.find(newRecord.getAccountNumber());
			Records=got->second;
		}
		Records.push_back(newRecord);
		AccountMap[newRecord.getAccountNumber()]=Records;
	}

	ofstream outf("Output.data");

	// If we couldn't open the output file stream for writing
	if (!outf)
	{
		// Print an error and exit
		cerr << "Uh oh, Sample.dat could not be opened for writing!" << endl;
		exit(1);
	}

	outf<<"Account \tLong\tShort\tNet\t"<<endl;

	typedef boost::unordered_map<string,vector<AccountPositions> >  Hash;

		for (boost::unordered_map<string,vector<AccountPositions> >::const_iterator it = AccountMap.begin(); it!=AccountMap.end(); ++it){
		vector<AccountPositions> Records;

		boost::unordered_map<string,vector<AccountPositions> >::const_iterator got = AccountMap.find(it->first);
		Records=it->second;

		int dv=0;
		int netLong=0;
		int netShort=0;
		for (vector<AccountPositions>::iterator RecordIt=Records.begin();
				RecordIt!=Records.end();RecordIt++){

			dv=(*RecordIt).getPrice() * (*RecordIt).getQuantity();

			if (dv>0){
				netLong+=dv;
			}
			else{
				netShort+=dv;
			}

		}
		// We'll write two lines into this file
		int total=(netLong+netShort);
		string output;
		outf <<  it->first << "\t" << netLong << "\t" << netShort << "\t" << total << endl;

	}

}
