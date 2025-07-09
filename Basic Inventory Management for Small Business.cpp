// Basic Inventory Management for Small Business.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Product {
    string name;
    int quantity;
    float price;
};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    for (char ch : s) {
        if (ch == delimiter) {
            tokens.push_back(token);
            token.clear();
        }
        else {
            token += ch;
        }
    }
    tokens.push_back(token);
    return tokens;
}

void addProduct() {
    Product p;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter quantity: ";
    cin >> p.quantity;
    cout << "Enter price: ";
    cin >> p.price;

    ofstream file("inventory.txt", ios::app);
    file << p.name << "|" << p.quantity << "|" << p.price << "\n";
    file.close();

    cout << "Product added successfully!\n";
}

vector<Product> loadProducts() {
    vector<Product> products;
    ifstream file("inventory.txt");
    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, '|');
        if (parts.size() == 3) {
            Product p;
            p.name = parts[0];
            p.quantity = stoi(parts[1]);
            p.price = stof(parts[2]);
            products.push_back(p);
        }
    }
    file.close();
    return products;
}

void displayProducts() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }
    cout << "\nInventory List:\n";
    for (const auto& p : products) {
        cout << "Name: " << p.name << ", Quantity: " << p.quantity << ", Price: $" << p.price << "\n";
    }
}

void searchProduct() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }
    cin.ignore();
    cout << "Enter product name to search: ";
    string searchName;
    getline(cin, searchName);

    bool found = false;
    for (const auto& p : products) {
        if (p.name == searchName) {
            cout << "Found product - Name: " << p.name << ", Quantity: " << p.quantity << ", Price: $" << p.price << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Product not found.\n";
}

void updateQuantity() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }
    cin.ignore();
    cout << "Enter product name to update quantity: ";
    string name;
    getline(cin, name);

    bool updated = false;
    for (auto& p : products) {
        if (p.name == name) {
            cout << "Current quantity: " << p.quantity << "\n";
            cout << "Enter new quantity: ";
            int newQty;
            cin >> newQty;
            p.quantity = newQty;
            updated = true;
            break;
        }
    }

    if (!updated) {
        cout << "Product not found.\n";
        return;
    }

    ofstream file("inventory.txt");
    for (const auto& p : products) {
        file << p.name << "|" << p.quantity << "|" << p.price << "\n";
    }
    file.close();

    cout << "Quantity updated successfully.\n";
}

void deleteProduct() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }
    cin.ignore();
    cout << "Enter product name to delete: ";
    string name;
    getline(cin, name);

    bool deleted = false;
    vector<Product> newProducts;
    for (const auto& p : products) {
        if (p.name == name) {
            deleted = true;
        }
        else {
            newProducts.push_back(p);
        }
    }

    if (!deleted) {
        cout << "Product not found.\n";
        return;
    }

    ofstream file("inventory.txt");
    for (const auto& p : newProducts) {
        file << p.name << "|" << p.quantity << "|" << p.price << "\n";
    }
    file.close();

    cout << "Product deleted successfully.\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Inventory Management System ---\n";
        cout << "1. Add Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product Quantity\n";
        cout << "5. Delete Product\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addProduct(); break;
        case 2: displayProducts(); break;
        case 3: searchProduct(); break;
        case 4: updateQuantity(); break;
        case 5: deleteProduct(); break;
        case 0: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
