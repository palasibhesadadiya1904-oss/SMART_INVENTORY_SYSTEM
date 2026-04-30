#include <iostream>
#include <vector>
#include <fstream>
#include "product.h"
#include "supply_manager.h"
#include <iomanip>

using namespace std;

//  FILE HANDLING 

void loadProducts(vector<Product> &products)
{
    ifstream file("products.txt");
    if (!file)
        return;

    Product p;
    while (file >> p.id >> p.name >> p.quantity >> p.price)
    {
        products.push_back(p);
    }
    file.close();
}

void saveProducts(vector<Product> &products)
{
    ofstream file("products.txt");
    for (auto &p : products)
    {
        file << p.id << " "
             << p.name << " "
             << p.quantity << " "
             << p.price << endl;
    }
    file.close();
}

//  COMMON FUNCTIONS 

void viewProducts(vector<Product> &products)
{
    cout << "\nID\tName\tQty\tPrice\n";
    for (auto &p : products)
    {
        if (p.quantity > 0) // show only available
            p.display();
    }
}

void searchProduct(vector<Product> &products)
{
    string name;
    cout << "Enter product name: ";
    cin >> name;

    bool found = false;

    for (auto &p : products)
    {
        if (p.name == name && p.quantity > 0)
        {
            p.display();
            found = true;
        }
    }

    if (!found)
        cout << "Product not found.\n";
}

//  ORDER 

void placeOrder(vector<Product> &products, string customerName)
{
    vector<pair<int, int>> cart; // (productID, quantity)

    int choice;

    do
    {
        int id, qty;

        cout << "\nEnter Product ID: ";
        cin >> id;

        cout << "Enter Quantity: ";
        cin >> qty;

        bool found = false;

        for (auto &p : products)
        {
            if (p.id == id)
            {

                if (p.quantity >= qty)
                {
                    cart.push_back({id, qty});
                    cout << "Added to cart!\n";
                }
                else
                {
                    cout << "Not enough stock!\n";
                }

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Product not found!\n";
        }

        cout << "Add more items? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);

    //  SHOW FINAL CART 
    cout << "\n*************************************************\n";
    cout << "*               CUSTOMER BILL                    *\n";
    cout << "*************************************************\n";

    cout << "Customer Name : " << customerName << "\n\n";

    cout << "-------------------------------------------------\n";
    cout << "ID\tName\tQty\tPrice\tTotal\n";
    cout << "-------------------------------------------------\n";

    float totalAmount = 0;

    for (auto &item : cart)
    {
        for (auto &p : products)
        {
            if (p.id == item.first)
            {
                float itemTotal = item.second * p.price;

                cout << left << setw(6) << p.id
                     << setw(12) << p.name
                     << setw(6) << item.second
                     << setw(8) << p.price
                     << setw(8) << itemTotal << endl;

                totalAmount += itemTotal;
            }
        }
    }

    cout << "-------------------------------------------------\n";
    cout << "Total Amount : " << totalAmount << endl;
    cout << "*************************************************\n";

    //  CONFIRM 
    int confirm;
    cout << "Confirm order? (1 = Yes, 0 = No): ";
    cin >> confirm;

    if (confirm == 1)
    {

        ofstream file("orders.txt", ios::app);

        for (auto &item : cart)
        {
            file << customerName << " "
                 << item.first << " "
                 << item.second << endl;

            // reduce stock
            for (auto &p : products)
            {
                if (p.id == item.first)
                {
                    p.quantity -= item.second;
                }
            }
        }

        file << "---\n"; // mark end of order
        file.close();

        cout << " Order placed successfully!\n";
    }
    else
    {
        cout << " Order cancelled.\n";
    }
}
//  ADMIN FUNCTIONS 

void addProduct(vector<Product> &products)
{
    Product p;
    p.input();
    products.push_back(p);
    saveProducts(products);
}

void updateProduct(vector<Product> &products)
{
    int id;
    cout << "Enter product ID: ";
    cin >> id;

    for (auto &p : products)
    {
        if (p.id == id)
        {
            cout << "Enter new name: ";
            cin >> p.name;
            cout << "Enter new quantity: ";
            cin >> p.quantity;
            cout << "Enter new price: ";
            cin >> p.price;

            saveProducts(products);
            cout << "Updated successfully!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}

void deleteProduct(vector<Product> &products)
{
    int id;
    cout << "Enter product ID: ";
    cin >> id;

    for (auto it = products.begin(); it != products.end(); ++it)
    {
        if (it->id == id)
        {
            products.erase(it);
            saveProducts(products);
            cout << "Deleted successfully!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}

void viewOrders()
{
    ifstream file("orders.txt");

    cout << "\nCustomer\tProductID\tQty\n";

    string name;
    int id, qty;

    while (file >> name >> id >> qty)
    {
        cout << name << "\t\t" << id << "\t\t" << qty << endl;
    }

    file.close();
}

void checkLowStock(vector<Product> &products)
{
    cout << "\n Low Stock Products (Qty <= 5):\n";
    cout << "ID\tName\tQty\tPrice\n";

    bool found = false;

    for (auto &p : products)
    {
        if (p.quantity <= 5)
        {
            p.display();
            found = true;
        }
    }

    if (!found)
    {
        cout << "No low stock items.\n";
    }
}

void generateReport(vector<Product> &products)
{
    int totalProducts = products.size();
    int totalStock = 0;
    int lowStockCount = 0;

    for (auto &p : products)
    {
        totalStock += p.quantity;
        if (p.quantity <= 5)
            lowStockCount++;
    }

    // Count orders
    ifstream file("orders.txt");
    int orderCount = 0;
    string name;
    int id, qty;

    while (file >> name >> id >> qty)
    {
        orderCount++;
    }
    file.close();

    cout << "\n===== REPORT =====\n";
    cout << "Total Products: " << totalProducts << endl;
    cout << "Total Stock: " << totalStock << endl;
    cout << "Low Stock Items: " << lowStockCount << endl;
    cout << "Total Orders: " << orderCount << endl;
}

//  MENUS 

void shopkeeperMenu(vector<Product> &products, SupplyManager &sm)
{
    checkLowStock(products);
    int choice;

    do
    {
        cout << "\n=== SHOPKEEPER MENU ===\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. View Orders\n";
        cout << "6. Low Stock Alert\n";
        cout << "7. Generate Report\n";
        cout << "8. Add Supplier\n";
        cout << "9. View Suppliers\n";
        cout << "10. Place Supply Order\n";
        cout << "11. View Supply Orders\n";
        cout << "12. Update Supply Status\n";
        cout << "13. Receive Stock (Update Inventory)\n";
        cout << "14. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            addProduct(products);
        else if (choice == 2)
            viewProducts(products);
        else if (choice == 3)
            updateProduct(products);
        else if (choice == 4)
            deleteProduct(products);
        else if (choice == 5)
            viewOrders();
        else if (choice == 6)
            checkLowStock(products);
        else if (choice == 7)
            generateReport(products);
        else if (choice == 8)
        {
            int id;
            string name, contact;
            cout << "Enter Supplier ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Contact: ";
            cin >> contact;

            sm.addSupplier(id, name, contact);
        }

        else if (choice == 9)
        {
            sm.viewSuppliers();
        }

        else if (choice == 10)
        {
            int oid, pid, qty;
            cout << "Enter Order ID: ";
            cin >> oid;
            cout << "Enter Product ID: ";
            cin >> pid;
            cout << "Enter Quantity: ";
            cin >> qty;

            sm.placeSupplyOrder(oid, pid, qty);
        }

        else if (choice == 11)
        {
            sm.viewSupplyOrders();
        }

        else if (choice == 12)
        {
            int oid;
            string status;
            cout << "Enter Order ID: ";
            cin >> oid;
            cout << "Enter Status (Ordered/Shipped/Delivered): ";
            cin >> status;

            sm.updateOrderStatus(oid, status);
        }

        else if (choice == 13)
        {
            int oid;
            cout << "Enter Order ID to receive stock: ";
            cin >> oid;

            int qty = sm.receiveStock(oid);

            if (qty == 0)
            {
                cout << "Order not delivered or invalid!\n";
            }
            else
            {
                int pid;
                cout << "Enter Product ID to update inventory: ";
                cin >> pid;

                for (auto &p : products)
                {
                    if (p.id == pid)
                    {
                        p.quantity += qty;
                        cout << "Inventory updated!\n";
                        saveProducts(products);
                        break;
                    }
                }
            }
        }
    } while (choice != 14);
    if (choice == 14)
    {
        return;
    }
}

void customerMenu(vector<Product> &products, string name)
{
    int choice;

    do
    {
        cout << "\n=== CUSTOMER MENU ===\n";
        cout << "1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Place Order\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            viewProducts(products);
        else if (choice == 2)
            searchProduct(products);
        else if (choice == 3)
        {
            placeOrder(products, name);
            saveProducts(products);
        }

    } while (choice != 4);
    if (choice == 4)
    {
        return;
    }
}

void loginSystem(vector<Product> &products, SupplyManager &sm)
{
    int role;

    cout << "\n===== LOGIN SYSTEM =====\n";
    cout << "1. Shopkeeper Login\n";
    cout << "2. Customer\n";
    cout << "3. Exit Program\n";
    cout << "Enter choice: ";
    cin >> role;

    if (role == 1)
    {
        string user, pass;

        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        if (user == "admin" && pass == "1234")
        {
            shopkeeperMenu(products, sm);
     
            loginSystem(products, sm);
        }
        else
        {
            cout << " Invalid credentials!\n";
            loginSystem(products, sm);
        }
    }

    else if (role == 2)
    {
        string name;
        cout << "Enter your name: ";
        cin >> name;

        customerMenu(products, name);

        loginSystem(products, sm);
    }

    else if (role == 3)
    {
        cout << "Exiting system...\n";
        return; 
    }

    else
    {
        cout << "Invalid choice!\n";
        loginSystem(products, sm);
    }
}


int main()
{
    vector<Product> products;
    SupplyManager sm;

    loadProducts(products);

    loginSystem(products, sm);

    return 0;
}