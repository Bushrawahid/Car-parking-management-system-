#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct Car {
    string regNumber;
    string ownerName;
    time_t entryTime;
};

vector<Car> parkingLot;
const int TOTAL_SLOTS = 10;
double feePerHour = 2.5;  

void saveToFile() {
    ofstream file("parking_data.txt");
    for (const auto& car : parkingLot) {
        file << car.regNumber << " " << car.ownerName << " " << car.entryTime << endl;
    }
    file.close();
}

void loadFromFile() {
    ifstream file("parking_data.txt");
    Car car;
    while (file >> car.regNumber >> car.ownerName >> car.entryTime) {
        parkingLot.push_back(car);
    }
    file.close();
}

void addCar() {
    if (parkingLot.size() >= TOTAL_SLOTS) {
        cout << "Parking full!" << endl;
        return;
    }
    Car car;
    cout << "Enter car registration number: ";
    cin >> car.regNumber;
    cout << "Enter owner name: ";
    cin >> car.ownerName;
    car.entryTime = time(0);
    parkingLot.push_back(car);
    saveToFile();
    cout << "Car added successfully!" << endl;
}

void removeCar() {
    string regNumber;
    cout << "Enter car registration number to remove: ";
    cin >> regNumber;
    for (auto it = parkingLot.begin(); it != parkingLot.end(); ++it) {
        if (it->regNumber == regNumber) {
            time_t exitTime = time(0);
            double hours = difftime(exitTime, it->entryTime) / 3600.0;
            double fee = hours * feePerHour;
            parkingLot.erase(it);
            saveToFile();
            cout << "Car removed. Parking fee: $" << fee << endl;
            return;
        }
    }
    cout << "Car not found!" << endl;
}

void displaySlots() {
    cout << "Available slots: " << TOTAL_SLOTS - parkingLot.size() << " out of " << TOTAL_SLOTS << endl;
}

void searchCar() {
    string regNumber;
    cout << "Enter car registration number to search: ";
    cin >> regNumber;
    for (const auto& car : parkingLot) {
        if (car.regNumber == regNumber) {
            cout << "Car found: " << car.regNumber << " | Owner: " << car.ownerName << endl;
            return;
        }
    }
    cout << "Car not found!" << endl;
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\nCar Parking Management System\n";
        cout << "1. Add Car\n2. Remove Car\n3. Display Slots\n4. Search Car\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: addCar(); break;
        case 2: removeCar(); break;
        case 3: displaySlots(); break;
        case 4: searchCar(); break;
        case 5: cout << "Exiting..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
    return 0;
}