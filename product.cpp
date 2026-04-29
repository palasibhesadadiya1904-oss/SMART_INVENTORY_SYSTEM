#include "product.h"

void Product::input() {
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price: ";
    cin >> price;
}

void Product::display() {
    cout << id << "\t" << name << "\t" << quantity << "\t" << price << endl;
}