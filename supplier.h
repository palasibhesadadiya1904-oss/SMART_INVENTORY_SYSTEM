#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
using namespace std;

class Supplier {
private:
    int supplierID;
    string name;
    string contact;

public:
    Supplier();
    Supplier(int id, string name, string contact);

    int getID() const;
    string getName() const;
    string getContact() const;

    void display() const;
};

#endif