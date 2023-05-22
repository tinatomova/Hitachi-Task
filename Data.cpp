#include "Data.h"

Data::Data(const string& filename){
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file\n";
        this->validFile = 0;
        return;
    }

    this->validFile = 1;
    string line;
    getline(file, line); 
    vector<vector<string>> tempContainer;

    for(int i = 0; i < 6; i++){
        (getline(file, line));
        istringstream iss(line);       
        vector<string> tempVector;
        string temp;
        getline(iss, temp, ','); 
        
        while(getline(iss, temp, ',')){
            if(i < 4){
                try{
                stoi(temp);
                }
                catch(const invalid_argument& e){
                    this->validFile = false;
                    return;
                }
            }
            tempVector.push_back(temp);
        }
        tempContainer.push_back(tempVector);
    }

    file.close();

    if (tempContainer.size() != 6) {
        this->validFile = false;
        return;
    }

    for(int i = 0; i < tempContainer[0].size(); i++){       
        Day oneDay(stoi(tempContainer[0][i]), stoi(tempContainer[1][i]), stoi(tempContainer[2][i]), stoi(tempContainer[3][i]), !(tempContainer[4][i] == "No"), tempContainer[5][i]);  
        this->data.push_back(oneDay);   
    }
    bestDay = -1;
}

bool Data::getValidFile()const{
    return this->validFile;
}

void Data::findBestDay(){   
    Day minDay;
    for(int i = 0; i < this->data.size(); i++){
        if(minDay > this->data[i]){
            minDay = this->data[i];
            this->bestDay = i;
        }
    }
}

bool Data::exportData(const string& filename)const{
    ofstream file(filename);
    if (!file) {
        cout << "Error creating file!\n";
        return false;
    }

    file << "Parameter,Average value,Max value,Min value,Median value,Most appropriate day: " << bestDay + 1 << "\n";

    auto writeDataRow = [&](const string& parameter, int (Day::*getValue)() const) {
        file << parameter << ",";
        
        file << findAverage(getValue) << ","
            << findMax(getValue) << ","
            << findMin(getValue) << ","
            << findMedian(getValue) << ",";

        if(bestDay != -1){
            file << (data[bestDay].*getValue)() << "\n";
        }
        else{
            file << "-\n";
        }      
    };

    writeDataRow("Temperature (C)", &Day::getTemperature);
    writeDataRow("Wind (m/s)", &Day::getWind);
    writeDataRow("Humidity (%)", &Day::getHumidity);
    writeDataRow("Precipitation (%)", &Day::getPrecipitation);
    if(bestDay != -1){
        file << "Lightning,-,-,-,-," << data[bestDay].getLightning() << "\n";
        file << "Clouds,-,-,-,-," <<data[bestDay].getClouds() << "\n";
    }
    else{
        file << "Lightning,-,-,-,-,-\n";
        file << "Clouds,-,-,-,-,-\n";
    }

    file.close();
    return true;
}

bool Data::sendData(const string& senderEmail, const string& password, const string& receiverEmail)const{
    string filePath = "WeatherReport.csv";
    /*
    CURL* curl = curl_easy_init();
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://your-smtp-server.com");
        curl_easy_setopt(curl, CURLOPT_USERNAME, senderEmail);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password); 
        struct curl_slist* recipients = nullptr;
        recipients = curl_slist_append(recipients, receiverEmail.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_mime* mime = curl_mime_init(curl);
        curl_mimepart* part = curl_mime_addpart(mime);
        curl_mime_data(part, "Weather Report", CURL_ZERO_TERMINATED);

        std::string emailText = "The most appropriate day is: " + to_string(bestDay + 1);
        emailText += "\n";
        emailText += "Temperature: " + to_string(data[bestDay].getTemperature()) + " C\n";
        emailText += "Wind: " + to_string(data[bestDay].getWind()) + " m/s\n";
        emailText += "Humidity: " + to_string(data[bestDay].getHumidity()) + " %\n";
        emailText += "Precipitation: " + to_string(data[bestDay].getPrecipitation()) + " %\n";
        emailText += "Lightning: " + data[bestDay].getLightning() + "\n";
        emailText += "Clouds: " + data[bestDay].getClouds() + "\n";
        part = curl_mime_addpart(mime);
        curl_mime_data(part, emailText.c_str(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "WeatherReport.csv");
        curl_mime_filedata(part, filePath);

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cout << "Failed to send email\n";
            return false;
        }
        curl_mime_free(mime);
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    */
    return false;
}



double Data::findAverage(int (Day::*getter)() const)const{  
    int sum = 0;
    for(int i = 0; i < this->data.size(); i++){
        sum += (this->data[i].*getter)();
    }
    return static_cast<double>(sum) / this->data.size();
}

int Data::findMax(int (Day::*getter)() const)const{
    int max = INT_MIN;
    for(int i = 0; i < this->data.size(); i++){
        if(max < (this->data[i].*getter)()){
            max = (this->data[i].*getter)();
        }
    }
    return max;
}

int Data::findMin(int (Day::*getter)() const)const{
    int min = INT_MAX;
    for(int i = 0; i < this->data.size(); i++){
        if(min > (this->data[i].*getter)()){
            min = (this->data[i].*getter)();
        }
    }
    return min;
}

double Data::findMedian(int (Day::*getter)() const)const{
    vector<int> values;
    for(int i = 0; i < this->data.size(); i++){
        values.push_back((this->data[i].*getter)());
    }
    if(this->data.size() % 2 == 1){
        auto middle = values.begin() + values.size() / 2;
        nth_element(values.begin(), middle, values.end());
        return double(*middle);
    }
    else{
        auto before = values.begin() + (values.size() - 1) / 2;
        auto after = values.begin() + (values.size() + 1) / 2;
        nth_element(values.begin(), before, values.end());
        nth_element(values.begin(), after, values.end());
        return double(*before + *after) / 2.0; 
    }
}

void Data::print()const{
    for(int i = 0; i < this->data.size(); i++){
        cout << i + 1 << ": ";
        this->data[i].print();
    }
    cout << "Best day: " << bestDay + 1 << "    ";
    if(bestDay != -1){
        data[bestDay].print();
    }
}
