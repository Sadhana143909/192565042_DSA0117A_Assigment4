
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
class Staff {
protected:
    string name;
    int id;
public:
    Staff(string n, int i) : name(n), id(i) {}
    virtual double pay() const = 0;
    virtual void display() const {
        cout << name << " " << id << " " << pay() << endl;
    }
    virtual ~Staff() {}
};
 
class Professor : public Staff {
    double basic, research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}
    double pay() const override {
        const double DA_RATE = 0.42;
        return basic + basic * DA_RATE + research;
    }
};
 
class LabAssistant : public Staff {
    double basic;
public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i), basic(b) {}
    double pay() const override {
        const double DA_RATE = 0.42;
        return basic + basic * DA_RATE;
    }
};
 
class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i), hours(h), rate(r) {}
    double pay() const override {
        return hours * rate;
    }
};
 
int main() {
    vector<Staff*> staff;
    staff.push_back(new Professor("Anu", 101, 50000, 5000));
    staff.push_back(new LabAssistant("Bala", 102, 25000));
    staff.push_back(new GuestFaculty("Devi", 103, 20, 800));
 
    for (Staff* s : staff)
        s->display();
 
    for (Staff* s : staff)
        delete s;
    return 0;
}
