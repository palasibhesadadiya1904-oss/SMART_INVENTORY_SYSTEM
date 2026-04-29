#ifndef ORDER_H
#define ORDER_H

#include <iostream>
using namespace std;

class Order {
public:
    string customerName;
    int productId;
    int quantity;

    void input();
    void display();
};

#endif