#pragma once
#include <string>
#include <iostream>
using namespace std;
class Day
{
private:
    int temperature;
    int wind;
    int humidity;
    int precipitation;   
    bool lightning;
    string clouds;

    double index;
    bool valid;
public:
    
    Day();
    Day(int temperature, int wind, int humidity, int precipitation, bool lightning, string clouds);
    bool isValid();

    int getTemperature()const;
    int getWind()const;
    int getHumidity()const;
    int getPrecipitation()const;
    string getLightning()const;
    string getClouds()const;

    Day& operator=(const Day& rhs);
    bool operator<(const Day& rhs)const;
    bool operator>(const Day& rhs)const;
    bool operator==(const Day& rhs)const;

    void print()const;
    
};