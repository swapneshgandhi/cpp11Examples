#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <string>

/*
// Read file in
// Stock, TimeInterval, Volume Traded, High, Low.
VOD.L 1 100 183.7 184.0
BT.L 1 14 448.2 449.4
VOD.L 2 434 182.4 184.1
BT.L 2 234 449.5 449.8
..

// Find the total volume traded for each stock
// Find the high and low for each stock.

// Write file a to stdout
// Per stock per interval output the %volume traded in that interval as a percentage of the whole day
// Stock, Interval, %Vol for day.
VOD.L,1,2.0
BT.L,1,1.1
VOD.L,2,8.2
BT.L,2,19.0

// Write file b to stdout
// Stock, day high, day low
VOD.L,186.7,182.4
BT.L,445.3,450.9
 */

using namespace std;
typedef basic_string<char> string;

class    CHighLow
{
public:
	CHighLow() : nCurLow(0), nCurHigh(0) {};

	void    add(int nHigh, int nLow)
	{
		if (nHigh > nCurHigh)
			nCurHigh = nHigh;

		if (nLow < nCurLow)
			nCurLow = nLow;
	}

	int        nCurLow;
	int        nCurHigh;
};

int main(int argc, char* argv[])
{
	//should check if there are as many arguments as you expect.
	if (!strcmp("version", argv[1]))
	{
		cerr << "Using version 1.0 VWAPer" << endl;
		return 0;
	}

	//check if file was opened correctly or check if it's a null pointer
	FILE*    file = fopen(argv[2], "r");


	//this should go to stdout not stderr
	cerr << "Reading file" << argv[2] << endl;

	//space should be dynamically allocated if it depends on input size.
	//this should be in an class.

	/*I think it's a good idea to use c++ string here
	 *as it has richer interface for common string operations and manages memory for you.
	 */

	/*
	 * class TradingData{
	 *
	 * string StockName;
	 * int Interval;
	 * float High;
	 * float Low;
	 * }
	 *
	 *
	 */

	char    line[256];
	char    Stocks[1000][10];
	int        Intervals[1000];
	int        Volumes[1000];
	float    Highs[1000];
	float    Lows[1000];

	int        i = 0;
	int        sum = 0;

	while (fgets(line, 256, file))
	{
		//if using sscanf one should be specifying width of the string or
		//use alternatives like stringstream or split a string on a delimiter.
		sscanf(line, "%s %d %d %f %f",
				Stocks[i], &Intervals[i],
				&Volumes[i], &Highs[i], &Lows[i++]);

		cerr << Stocks[i] << endl;
		cerr << Intervals[i] << endl;
		cerr << Volumes[i] << endl;
		cerr << Highs[i] << endl;
		cerr << Lows[i] << endl;
	}

	cerr << "Calculating total volumes" << endl;

	map<std::string, int>        TotalVolumes;

	/*this loop takes O(n^2) time, may be we should use multimap to store all the trading data
    for the same stock.
    or use map with vector of objects as the value for the map
    and then for each stockname traverse through all the volumes to find total volumes for the stock.
    then we can do it in O(n) only. */

	for (int s = 0; s <= i; ++s)
	{
		std::string    stockname = Stocks[s];

		for (int j =0; j <= i; ++j)
		{
			//why not use string::compare() function, no need to convert to char *
			if (!strcmp(Stocks[j], stockname.c_str()))
			{
				TotalVolumes[stockname] += Volumes[j];
			}
		}
	}

	cerr << "Calculating high lows" << endl;

	map<std::string, CHighLow>    HighLows;

	for (int s = 0; s <= i; ++s)
	{
		HighLows[Stocks[s]].add(Highs[s], Lows[s]);
	}

	cerr << "Writing files" << endl;

	// write file a
	for (int s = 0; s <= i; ++s)
	{
		/* percentage volume should be  (volume for an interval)/ (total volume for the stock) *100
		 */

		cout << Stocks[s] << "," << Intervals[s] << "," <<
				TotalVolumes[Stocks[s]] / Volumes[s] * 100 << endl;
	}

	// write file b
	map<std::string, CHighLow>::iterator itr = HighLows.begin();
	while (itr != HighLows.end())
	{
		cout << (*itr).first << "," << (*itr).second.nCurLow << "," <<
				(*itr).second.nCurHigh << endl;

		++itr;
	}

	//if executed correctly should return 0 not 1.
	return 1;
}




