#include "order.h"

void Order::input() {
    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter product ID: ";
    cin >> productId;
    cout << "Enter quantity: ";
    cin >> quantity;
}

void Order::display() {
    cout << customerName << "\t" << productId << "\t" << quantity << endl;
}