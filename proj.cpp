#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Store {
    int storeId;
    string location;
};

struct Customer {
    int customerId;
    string firstName;
    string lastName;
    string phone;
    string transactionLocation;
};

struct Employee {
    int employeeId;
    string firstName;
    string middleName;
    string lastName;
    string role;
    string phone;
};

struct Product {
    int productId;
    string catalogue;
    double cost;
    double price;
    int quantityStock;
    string name;
    string description;
};

void displayInformation(const vector<Store>& stores, const vector<Customer>& customers, const vector<Employee>& employees, const vector<Product>& products) {
    cout << left << setw(15) << "Store ID" << setw(30) << "Location" << '\n';
    cout << string(45, '-') << '\n';
    for (const auto& store : stores) {
        cout << setw(15) << store.storeId << setw(30) << store.location << '\n';
    }

    cout << "\nCustomer Information:\n";
    cout << left << setw(15) << "Customer ID" << setw(20) << "First Name" << setw(20) << "Last Name" << setw(20) << "Phone" << setw(30) << "Transaction Location" << '\n';
    cout << string(105, '-') << '\n';
    for (const auto& customer : customers) {
        cout << setw(15) << customer.customerId << setw(20) << customer.firstName << setw(20) << customer.lastName << setw(20) << customer.phone << setw(30) << customer.transactionLocation << '\n';
    }

    cout << "\nEmployee Information:\n";
    cout << left << setw(15) << "Employee ID" << setw(20) << "First Name" << setw(20) << "Middle Name" << setw(20) << "Last Name" << setw(20) << "Role" << setw(20) << "Phone" << '\n';
    cout << string(115, '-') << '\n';
    for (const auto& employee : employees) {
        cout << setw(15) << employee.employeeId << setw(20) << employee.firstName << setw(20) << employee.middleName << setw(20) << employee.lastName << setw(20) << employee.role << setw(20) << employee.phone << '\n';
    }

    cout << "\nProduct Information:\n";
    cout << left << setw(15) << "Product ID" << setw(20) << "Catalogue" << setw(10) << "Cost" << setw(10) << "Price" << setw(15) << "Quantity Stock" << setw(20) << "Name" << setw(30) << "Description" << '\n';
    cout << string(120, '-') << '\n';
    for (const auto& product : products) {
        cout << setw(15) << product.productId << setw(20) << product.catalogue << setw(10) << product.cost << setw(10) << product.price << setw(15) << product.quantityStock << setw(20) << product.name << setw(30) << product.description << '\n';
    }
}

int main() {
    // Sample data
    vector<Store> stores = {{1, "123 Main St"}, {2, "456 Maple Ave"}};
    vector<Customer> customers = {{1, "Abel", "Doe", "555-1234", "123 Main St"}, {2, "Anna", "Samuel", "555-5678", "456 Maple Ave"}};
    vector<Employee> employees = {{1, "Betty", "Yohannes", "Bekele", "Manager", "555-8765"}, {2, "Bob", "C", "Michael", "Clerk", "555-4321"}};
    vector<Product> products = {{1, "Footwear", 100.0, 150.0, 10, "Sandals", "Comfortable summer sandals"}, {2, "Footwear", 50.0, 75.0, 20, "Sneakers", "Stylish and comfortable sneakers"}};

    // Display the information
    displayInformation(stores, customers, employees, products);

    return 0;
}
