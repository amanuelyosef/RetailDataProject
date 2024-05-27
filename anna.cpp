
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Product {
    int productid;
    string name;
    string catalogue;
    int cost;
    int price;
    int quantity;
    string description;
};

void processProducts(const string& filename,const double taxRate) {
    vector<Product> products;
   
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Product product;
        size_t pos = 0;

        // Extract productid
        pos = line.find('\t');
        product.productid = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Extract name
        pos = line.find('\t');
        product.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract catalogue
        pos = line.find('\t');
        product.catalogue = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract cost
        pos = line.find('\t');
        product.cost = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Extract price
        pos = line.find('\t');
        product.price = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Extract quantity
        pos = line.find('\t');
        product.quantity = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Extract description
        product.description = line;

        products.push_back(product);
    }
    file.close();

    
    cout << "Product Data:" << endl;
    ifstream displayFile(filename);
    if (!displayFile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    while (getline(displayFile, line)) {
        cout << line << endl;
    }
    displayFile.close();

    
    double totalProfit = 0, totalTax = 0, totalSales = 0;
    for (const auto& product : products) {
        double profit = (product.price - product.cost) * product.quantity;
        double tax = product.price * product.quantity * taxRate;
        double sales = product.price * product.quantity;
        totalProfit += profit;
        totalTax += tax;
        totalSales += sales;
    }

    cout << "Total Sales: $" << totalSales << endl;
    cout << "Total Profit: $" << totalProfit << endl;
    cout << "Total Tax: $" << totalTax << endl;
}

int main() {
    const string filename = "product.txt";
    const double taxRate = 0.15; // Assuming 15% tax rate

    processProducts(filename, taxRate);

    return 0;
}
