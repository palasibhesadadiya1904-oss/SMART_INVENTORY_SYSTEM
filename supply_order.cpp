#include "supply_order.h"
#include <iostream>
using namespace std;

SupplyOrder::SupplyOrder() {
    orderID = 0;
    productID = 0;
    quantity = 0;
    status = "Ordered";
}

SupplyOrder::SupplyOrder(int oid, int pid, int qty) {
    orderID = oid;
    productID = pid;
    quantity = qty;
    status = "Ordered";
}

int SupplyOrder::getOrderID() const {
    return orderID;
}

int SupplyOrder::getProductID() const {
    return productID;
}

int SupplyOrder::getQuantity() const {
    return quantity;
}

string SupplyOrder::getStatus() const {
    return status;
}

void SupplyOrder::setStatus(string newStatus) {
    status = newStatus;
}

void SupplyOrder::display() const {
    cout << "Order ID: " << orderID << endl;
    cout << "Product ID: " << productID << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Status: " << status << endl;
    cout << "------------------------\n";
}