#include"Day.h"

using namespace std;

Day::Day(){
    this->temperature = 0;
    this->wind = 0;
    this->humidity = 0;
    this->precipitation = 0;
    this->lightning = 0;
    this->clouds = "";

    this->index = 1;
    this->valid = 0;
}

Day::Day(int temperature, int wind, int humidity, int precipitation, bool lightning, string clouds){
    this->temperature = temperature;
    this->wind = wind;
    this->humidity = humidity;
    this->precipitation = precipitation;
    this->lightning = lightning;
    this->clouds = clouds;
    this->index = (double(wind) / 10.0) * (double(humidity) / 100.0);

    if((temperature > 2 && temperature < 31) && 
    (wind <= 10) && 
    (humidity < 60) && 
    (!precipitation) && 
    (!lightning) &&
    (clouds != "Cumulus" && clouds != "Nimbus")){
        this->valid = true;
    }
    else{
        this->valid = false;
    }
}
bool Day::isValid(){
    return this->valid;
}

int Day::getTemperature()const{
    return this->temperature;
}

int Day::getWind()const{
    return this->wind;
}

int Day::getHumidity()const{
    return this->humidity;
}

int Day::getPrecipitation()const{
    return this->precipitation;
}

string Day::getLightning()const{
    return this->lightning ? "Yes" : "No";
}
string Day::getClouds()const{
    return this->clouds;
}

Day& Day::operator=(const Day& rhs){
    if(this != &rhs){
        this->temperature = rhs.temperature;
        this->wind = rhs.wind;
        this->humidity = rhs.humidity;
        this->precipitation = rhs.precipitation;
        this->lightning = rhs.lightning;
        this->clouds = rhs.clouds;

        this->index = rhs.index;
        this->valid = rhs.valid;
    }   
    return *this;
}

bool Day::operator<(const Day& rhs)const{
    if(this->valid == true && rhs.valid == false) return true;
    if(this->valid == false && rhs.valid == true) return false;
    if(this->index == rhs.index){
        return this->wind < rhs.wind;
    }
    return (this->index < rhs.index);
}

bool Day::operator>(const Day& rhs)const{
    if(this->valid == true && rhs.valid == false) return false;
    if(this->valid == false && rhs.valid == true) return true;
    if(this->index == rhs.index){
        return this->wind > rhs.wind;
    }
    return (this->index > rhs.index);
}

bool Day::operator==(const Day& rhs)const{
    return (this->valid == rhs.valid) && (this->index == rhs.index) && (this->wind == rhs.wind);
}

void Day::print()const{
    cout << "Temperature: " << this->temperature << "   Wind: " << this->wind << "  Humidity: " << this->humidity << "  Precipitation: " << this->precipitation << "    Lightning: " << this->lightning << "    Clouds: " << this->clouds << endl;
}

