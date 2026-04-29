#ifndef SUPPLY_ORDER_H
#define SUPPLY_ORDER_H

#include <string>
using namespace std;

class SupplyOrder {
private:
    int orderID;
    int productID;
    int quantity;
    string status; // Ordered, Shipped, Delivered

public:
    SupplyOrder();
    SupplyOrder(int oid, int pid, int qty);

    int getOrderID() const;
    int getProductID() const;
    int getQuantity() const;
    string getStatus() const;

    void setStatus(string newStatus);
    void display() const;
};

#endif