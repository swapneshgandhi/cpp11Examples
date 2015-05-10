#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

/*
// Write file b to stdout
// Stock, day high, day low
VOD.L,186.7,182.4
BT.L,445.3,450.9
 */



class TradeData{
public:
int vol;
float high;
float low;

TradeData(int vol, float low, float high){
this->vol=vol;
this->high=high;
this->low=low;
}

};

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

using namespace std;

//this class is not a nice object oriented practice, in terms of itâs member functions or fields.

int main(int argc, char* argv[])
{

        string stock;
        int     interval;
        int vol;
        int high;
        int low;

    int         i = 0;
    int         sum = 0;

    map<string, map <int, vector< shared_ptr<TradeData> > > >  TradeDataMap;
        map <int, vector<shared_ptr<TradeData> > > innerMap;
        vector< shared_ptr<TradeData> > VecP;
        string line;
        vector<string> strs;
        const char* fileName="data.dat";
        ifstream inf(fileName);

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
*/

    cout << "here";
        while (getline(inf,line)){
                strs.clear();
                split( line, ' ', strs);
        auto it=strs.begin();
        stock=*it;
        it++;
        interval=stoi(*it);
        int vol=stoi(*(++it));
        float low =stof(*(++it));
        float high=stof(*(++it));
        shared_ptr<TradeData> t = shared_ptr<TradeData>( new TradeData(vol,low,high));

        innerMap=TradeDataMap[stock];

        if (!(innerMap.empty())){
        VecP=innerMap[interval];
        }
        else{VecP.clear();}

        VecP.push_back(move(t));

        innerMap[interval]=VecP;
        TradeDataMap[stock]=innerMap;

    }

        cout << "here2";

        for (auto outer : TradeDataMap){
                int totalVol=0;
                float HighD=0;
                float LowD=9999999;
                for (auto inner : outer.second){

                vector< shared_ptr<TradeData> > VecP2=inner.second;

                        for (auto const &vectData: VecP2){
                        totalVol+=vectData->vol;
                        HighD= vectData->high > HighD ? vectData->high : HighD;
                        LowD= vectData->low < LowD ? vectData->low : LowD;
                        }

                }

        //write to file


                for (auto inner : outer.second){

                        vector< shared_ptr<TradeData> > VecP2=inner.second;

                        int PerVol=0;
                        for (auto const &vectData: VecP2){
                                PerVol+=vectData->vol;
                                }
                cout << outer.first << ", " << inner.first << ", " << ((float)PerVol/totalVol)*100 << endl;

                }

        cout << outer.first << ", " << HighD << ", " << LowD << endl;

        }
        cout << "here3";
    return 0;
}

