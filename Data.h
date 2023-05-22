#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>
//#include <curl/curl.h>
#include "Day.h"

using namespace std;
class Data
{
private:
    vector<Day> data;
    int bestDay;
    bool validFile;
    
public:
    Data(const string& filename);
    void print()const;
    void findBestDay();
    bool getValidFile()const;

    bool exportData(const std::string& filename)const;
    double findAverage(int (Day::*getter)() const)const;
    int findMax(int (Day::*getter)() const)const;
    int findMin(int (Day::*getter)() const)const;
    double findMedian(int (Day::*getter)() const)const;
    bool sendData(const std::string& senderEmail, const std::string& password, const std::string& receiverEmail)const;
};