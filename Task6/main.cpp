#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
 
class Vehicle {
protected:
    string regNo;
    double dailyRate;
    bool rented;
public:
    Vehicle(string r, double rate)
        : regNo(r), dailyRate(rate), rented(false) {}
 
    virtual double charge(int days) const = 0;
 
    virtual void display() const {
        cout << regNo << " " << dailyRate
             << " " << (rented ? "Rented" : "Available")
             << " Charge: " << charge(1) << endl;
    }
 
    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }
 
    double returnVehicle(int lateDays) {
        rented = false;
        if (lateDays < 0) lateDays = 0;
        return lateDays * 200.0;
    }
 
    virtual ~Vehicle() {}
};
 
class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate) : Vehicle(r, rate) {}
    double charge(int days) const override {
        return dailyRate * days;
    }
};
 
class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    string serviceDueDate;
public:
    MotorVehicle(string r, double rate, double fuel, string date)
        : Vehicle(r, rate), fuelLevel(fuel), serviceDueDate(date) {}
};
 
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r, double rate, double fuel, string date)
        : MotorVehicle(r, rate, fuel, date) {}
    double charge(int days) const override {
        return dailyRate * days;
    }
};
 
class Car : public MotorVehicle {
protected:
    int seats;
public:
    Car(string r, double rate, double fuel, string date, int s)
        : MotorVehicle(r, rate, fuel, date), seats(s) {}
    double charge(int days) const override {
        return dailyRate * days;
    }
};
 
class ElectricCar : public Car {
    double batteryCapacity;
    double kwhUsed;
    double costPerKwh;
public:
    ElectricCar(string r, double rate, double fuel, string date,
                int s, double capacity, double used, double cost)
        : Car(r, rate, fuel, date, s),
          batteryCapacity(capacity), kwhUsed(used),
          costPerKwh(cost) {}
 
    double charge(int days) const override {
        return dailyRate * days + kwhUsed * costPerKwh;
    }
};
 
class ElectricBus : public MotorVehicle {
    int seats;
    double kwhUsed;
    double costPerKwh;
public:
    ElectricBus(string r, double rate, double fuel, string date,
                int s, double used, double cost)
        : MotorVehicle(r, rate, fuel, date),
          seats(s), kwhUsed(used), costPerKwh(cost) {}
 
    double charge(int days) const override {
        return dailyRate * days + kwhUsed * costPerKwh;
    }
};
 
int main() {
    vector<unique_ptr<Vehicle>> fleet;
 
    fleet.push_back(make_unique<Bicycle>("BIKE101", 100));
    fleet.push_back(make_unique<TwoWheeler>("TW202", 300, 80, "2026-12-10"));
    fleet.push_back(make_unique<Car>("CAR303", 1500, 60, "2026-12-15", 5));
    fleet.push_back(make_unique<ElectricCar>(
        "EV404", 1800, 90, "2026-12-20", 5, 60, 20, 8));
    fleet.push_back(make_unique<ElectricBus>(
        "BUS505", 3000, 85, "2026-12-25", 30, 50, 8));
 
    for (const auto& v : fleet)
        v->display();
 
    if (fleet[0]->rent())
        cout << "Bicycle rented" << endl;
 
    cout << "Late charge: "
         << fleet[0]->returnVehicle(2) << endl;
 
    return 0;
}
