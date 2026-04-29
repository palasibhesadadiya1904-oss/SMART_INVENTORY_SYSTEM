#ifndef SUPPLY_MANAGER_H
#define SUPPLY_MANAGER_H

#include <vector>
#include "supplier.h"
#include "supply_order.h"

using namespace std;

class SupplyManager {
private:
    vector<Supplier> suppliers;
    vector<SupplyOrder> orders;

public:
    void addSupplier(int id, string name, string contact);
    void viewSuppliers() const;

    void placeSupplyOrder(int orderID, int productID, int quantity);
    void viewSupplyOrders() const;

    void updateOrderStatus(int orderID, string status);

    int receiveStock(int orderID); 
    // returns quantity to add to inventory when delivered
};

#endif