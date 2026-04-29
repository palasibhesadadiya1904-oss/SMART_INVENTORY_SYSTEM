#include "supply_manager.h"
#include <iostream>
using namespace std;

// Supplier Functions
void SupplyManager::addSupplier(int id, string name, string contact) {
    suppliers.push_back(Supplier(id, name, contact));
}

void SupplyManager::viewSuppliers() const {
    for (const auto &s : suppliers) {
        s.display();
        cout << "------------------------\n";
    }
}

// Supply Order Functions
void SupplyManager::placeSupplyOrder(int orderID, int productID, int quantity) {
    orders.push_back(SupplyOrder(orderID, productID, quantity));
    cout << "Supply order placed successfully.\n";
}

void SupplyManager::viewSupplyOrders() const {
    if (orders.empty()) {
        cout << "No supply orders available.\n";
        return;
    }

    for (const auto &o : orders) {
        o.display();
    }
}

void SupplyManager::updateOrderStatus(int orderID, string status) {
    for (auto &o : orders) {
        if (o.getOrderID() == orderID) {
            o.setStatus(status);
            cout << "Order status updated.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

// When Delivered → return quantity to add to inventory
int SupplyManager::receiveStock(int orderID) {
    for (auto &o : orders) {
        if (o.getOrderID() == orderID && o.getStatus() == "Delivered") {
            return o.getQuantity();
        }
    }
    return 0;
}