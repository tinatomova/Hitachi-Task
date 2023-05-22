#include "Data.h"
using namespace std;

int main() {
    
    cout << "Welcome!\n\n";  

    string choice = "0";
    string input = "";

    while(choice != "3"){ 
        bool isValidFile = false;

        while (!isValidFile) {
            cout << "Enter CSV filename: ";
            cin >> input;
            if(input == "Q"){
                break;
            }
            system("cls");
            ifstream file(input);
            if (!file) {
                cout << "Error: Failed to open the file!\n" << endl;
            } 
            else {
                isValidFile = true;
                file.close();
            }
        }
        if(input == "Q"){
            break;
        }
        system("cls");

        Data d(input);
        if(!d.getValidFile()){
            cout << "Invalid file format\n";
            continue;
        }
        d.findBestDay();

        cout << "The information is imported!\n\n";
        cout << "Please choose an option: \n";
        cout << "\t1. Import data from file\n";
        cout << "\t2. Export report\n";
        cout << "\t3. Quit\n\n";
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        if(choice == "1"){
            continue;
        }
        
        else if(choice == "2"){           
            if(d.exportData("WeatherReport.csv")){
                cout << "The report was exported successfully!\n";
                cout << "Do you want to send the report? ('Y' or 'N'): ";
                char decision;
                cin >> decision;
                system("cls");

                while(decision == 'Y'){
                    string sender, password, receiver;
                    cout << "Your email: ";
                    cin >> sender;
                    cout << "Password: ";
                    cin >> password;
                    cout << "To: ";
                    cin >> receiver;
                    system("cls");

                    while(!d.sendData(sender, password, receiver)){
                        cout << "Your email: ";
                        cin >> sender;
                        cout << "Password: ";
                        cin >> password;
                        cout << "To: ";
                        cin >> receiver;
                        system("cls");
                    }

                    cout << "Report sent successfully!\n\n";
                    cout << "Do you want to send the report again? ('Y' or 'N'): ";
                    cin >> decision;
                    system("cls");
                } 
            }     

        }

        else if(choice == "3"){
            break;
        }
        
        else{
            cout << "Invalid choice. Please try again.\n\n";
            choice = "1";
        }

        cout <<"Please choose an option:\n";
        cout << "\t1. Import data from CSV file\n";
        cout << "\t3. Quit\n\n";
        cout << "Answer: ";
        cin >> choice;
        system("cls");
    }           
}