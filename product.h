#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;
    float price;

    void input();
    void display();
};

#endif