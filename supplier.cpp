#include "supplier.h"
#include <iostream>
using namespace std;

Supplier::Supplier() {
    supplierID = 0;
    name = "";
    contact = "";
}

Supplier::Supplier(int id, string n, string c) {
    supplierID = id;
    name = n;
    contact = c;
}

int Supplier::getID() const {
    return supplierID;
}

string Supplier::getName() const {
    return name;
}

string Supplier::getContact() const {
    return contact;
}

void Supplier::display() const {
    cout << "Supplier ID: " << supplierID << endl;
    cout << "Name: " << name << endl;
    cout << "Contact: " << contact << endl;
}