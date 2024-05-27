#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
struct customer
{
    int customerId;
    string firstname;
    string lastname;
    string location;
    string phone;
};
struct product
{
    int productid;
    string name;
    string catalogue;
    int cost;
    int price;
    int quantity;
    string discription;
};
struct transaction
{
    int transactionid;
    int productid;
    int customerid;
    int amount;
    char location[25];
};
void transactionsss(string record, vector<transaction> &transact, vector<product> &products, const vector<customer> &user)
{
    cin.ignore(); // Ignore any remaining characters in the input buffer
    transaction trans;
    time_t current_time = time(0);
    struct tm *local_time = localtime(&current_time);

    int current_year = local_time->tm_year + 1900;
    int current_month = local_time->tm_mon + 1;
    int current_day = local_time->tm_mday;
    int index_pro, index_cus;
    string product_name, customer_firstname, customer_lastname;
    cout << "Which product do you want to purchase: ";
    getline(cin, product_name);

    bool found = false;
    int quantity;

    for (int i = 0; i < products.size(); ++i)
    {
        if (product_name == products[i].name)
        {
            index_pro = i + 1;
            found = true;
            cout << "Please enter first name: ";
            getline(cin, customer_firstname);
            cout << "Last name: ";
            getline(cin, customer_lastname);

            bool valid_customer = false;
            for (int j = 0; j < user.size(); ++j)
            {
                if (customer_firstname == user[j].firstname && customer_lastname == user[j].lastname)
                {
                    index_cus = j + 1;
                    valid_customer = true;
                    break;
                }
            }

            if (valid_customer)
            {
                do
                {
                    cout << "How many " << product_name << " do you want to purchase? (Available: " << products[i].quantity << ") ";
                    cin >> quantity;

                    if (quantity <= products[i].quantity)
                    {
                        trans.amount = quantity * products[i].price;
                        cout << "You are purchasing " << quantity << " " << product_name << "." << endl;
                        break;
                    }
                    else
                    {
                        cout << "The quantity of " << product_name << " is only " << products[i].quantity << "." << endl;
                        cout << "Do you want to purchase the available quantity (y/n)? ";
                        char ch;
                        cin >> ch;
                        if (ch == 'y')
                        {
                            quantity = products[i].quantity;
                            break;
                        }
                    }

                } while (true);
                ofstream myfile(record);
                if (myfile.is_open())
                {
                    cout << "The file is successfully open!" << endl;
                    myfile << "\t\t Transaction Information" << endl;
                    myfile << "------------------------------------------------------" << endl;
                    myfile << "Customer ID : " << user[index_cus].customerId << endl;
                    myfile << "Product ID : " << products[index_pro].productid << endl;
                    myfile << "Transaction ID : " << trans.transactionid << endl;
                    myfile << "Amount : " << trans.amount << endl;
                    myfile << "Date : " << current_day << "/" << current_month << "/" << current_year << endl;
                    myfile << "Location : " << user[index_cus].location << endl;
                    myfile << "------------------------------------------------------" << endl;

                    myfile.close();
                }
                else
                {
                    cout << "Error opening file." << endl;
                }
            }
            else
            {
                cout << "Customer not found." << endl;
            }

            break;
        }
    }

    if (!found)
    {
        cout << "Product not found." << endl;
    }
}

void customerAdder(string into, vector<customer> &user)
{
    customer add;
    customer c1 = {1, "John", "Smith", "Addis Ababa", "+251912345678"};
    customer c2 = {2, "Sarah", "Johnson", "Dire Dawa", "+251911234567"};
    customer c3 = {3, "Mohammed", "Ahmed", "Bahir Dar", "+251925984835"};
    customer c4 = {4, "Anna", "Wilson", "Gondar", "+251913256748"};
    customer c5 = {5, "Daniel", "Tesfaye", "Hawassa", "+251948689233"};
    customer c6 = {6, "Helen", "Jones", "Mekelle", "+251906982516"};
    customer c7 = {7, "Michael", "Brown", "Harar", "+251945352685"};
    customer c8 = {8, "Elizabeth", "Davis", "Jimma", "+251910652533"};
    customer c9 = {9, "David", "Garcia", "adama", "+251911251012"};
    customer c10 = {10, "Maria", "Rodriguez", "Axum", "+251978988899"};

    user.push_back(c1);
    user.push_back(c2);
    user.push_back(c3);
    user.push_back(c4);
    user.push_back(c5);
    user.push_back(c6);
    user.push_back(c7);
    user.push_back(c8);
    user.push_back(c9);
    user.push_back(c10);
    cout << "Customer Information added here " << endl;
    cout << "enter ID : ";
    cin >> add.customerId;
    cout << "Enter first name : ";
    cin >> add.firstname;
    cout << "Enter last name : ";
    cin >> add.lastname;
    cin.ignore();
    cout << "Enter location : ";
    getline(cin, add.location, '\n');
    cout << "Enter phone number : (+251-)";
    cin >> add.phone;
    add.phone = "+251" + add.phone;
    user.push_back(add);
    ofstream myfile;
    myfile.open(into);
    if (myfile.is_open())
    {
        cout << "the file is successfully open!" << endl;
        myfile << "\t\tcustomer Information" << endl;
        myfile << "------------------------------------------------------" << endl;
        for (int index = 0; index < user.size(); index++)
        {
            myfile << "Customer ID: " << user[index].customerId << endl;
            myfile << "First Name: " << user[index].firstname << endl;
            myfile << "Last Name: " << user[index].lastname << endl;
            myfile << "Location: " << user[index].location << endl;
            myfile << "Phone Number: " << user[index].phone << endl;
            myfile << "------------------------------------------------------" << endl;
        }
        myfile.close();
    }
    else
        cout << "Error opening file " << endl;
}

void produc(string &into, vector<product> &pro)
{

    int choice, index;
    bool cheak = false;
    product add;
    product p1{1, "Laptop", "Electronics", 600, 899, 50, "High-performance laptop with Intel i7 processor."};
    product p2{2, "Smartphone", "Electronics", 300, 499, 100, "Latest model with 5G connectivity and dual cameras."};
    product p3{3, "Running Shoes", "Fashion", 50, 99, 200, "Lightweight shoes designed for running enthusiasts."};
    product p4{4, "Yoga Mat", "Fitness", 20, 35, 1050, "Non-slip surface, eco-friendly material."};
    product p5{5, "Coffee Maker", "Home", 80, 129, 80, "Programmable machine for brewing coffee."};
    product p6{6, "Backpack", "Fashion", 40, 69, 120, "Durable backpack with multiple compartments."};
    product p7{7, "Smart Watch", "Electronics", 150, 249, 90, "Fitness tracking features and smartphone connectivity."};
    product p8{8, "Blender", "Home", 50, 89, 70, "High-speed blender for smoothies and shakes."};
    product p9{9, "Wireless", "Electronics", 100, 179, 110, "Noise-canceling headphones with Bluetooth connectivity."};
    product p10{10, "Leather Wallet Fashion", "Fashine", 30, 49, 180, "Genuine leather wallet with RFID protection."};
    pro.push_back(p1);
    pro.push_back(p2);
    pro.push_back(p3);
    pro.push_back(p4);
    pro.push_back(p5);
    pro.push_back(p6);
    pro.push_back(p7);
    pro.push_back(p8);
    pro.push_back(p9);
    pro.push_back(p10);

    cout << "If you want to insert a new product enter 1\n";
    cout << "If you want to update an existing product enter 2\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:
        char ch;

        do
        {
            cout << "Enter product_id : ";
            cin >> add.productid;
            cout << "Product Name : ";
            cin >> add.name;
            cout << "Product Catalogue : ";
            cin >> add.catalogue;
            cout << "Product Cost : ";
            cin >> add.cost;
            cout << "Product Price : ";
            cin >> add.price;
            cout << "Product Quantity : ";
            cin >> add.quantity;
            cin.ignore();
            cout << "Product discription : ";
            getline(cin, add.discription);
            pro.push_back(add);
            cout << "Do you want to insert another product (y/n) : ";
            cin >> ch;
        } while (ch == 'y');
        break;
    case 2:
        int search;
    lable:
        cout << "which item you update , please enter the product id : ";
        cin >> search;
        for (int i = 0; i < pro.size(); ++i)
        {
            if (search == pro[i].productid)
            {
                cheak == true;

                cout << "if you update item's name : (y/n)";
                cin >> ch;
                if (ch == 'y')
                {
                    cout << "Enter product Name : ";
                    cin >> pro[i].name;
                }
                cout << "if you update item's cost : (y/n)";
                cin >> ch;
                if (ch == 'y')
                {
                    cout << "Enter product cost : ";
                    cin >> pro[i].cost;
                }
                cout << "if you update item's price : (y/n)";
                cin >> ch;
                if (ch == 'y')
                {
                    cout << "Enter product price : ";
                    cin >> pro[i].price;
                }
                cout << "if you update item's Quantity: (y/n)";
                cin >> ch;
                if (ch == 'y')
                {
                    cout << "Enter product Quantity : ";
                    cin >> pro[i].quantity;
                }
                cout << "if you update item's Discription : (y/n)";
                cin >> ch;
                cin.ignore();
                if (ch == 'y')
                {
                    cout << "Enter product Discription : ";
                    getline(cin, pro[i].discription);
                }

                //  for (int i = 0; i < pro.size(); ++i) {
                //         cout << "Product details for ID " << pro[i].productid << ":\n";
                //         cout << "Name: " << pro[i].name << endl;
                //         cout << "Catalogue: " << pro[i].catalogue << endl;
                //         cout << "Cost: " << pro[i].cost << endl;
                //         cout << "Price: " << pro[i].price << endl;
                //         cout<< "discription : "<<pro[i].discription<<endl;
                //  }
            }
        }
    }
    //  cout << "updated Customer Information:\n";
    //     for (const auto& c : pro) {
    //         cout << "product ID : " << c.productid << endl;
    //         cout << "Name: " << c.name << endl;
    //         cout << "catalogue : " << c.catalogue << endl;
    //         cout << "Price : " << c.price << endl;
    //                 cout << "cost : " << c.cost << endl;
    //                         cout << "discription : " << c.discription<< endl;
    //                             cout << "quantitiy : " << c.quantity << endl;

    //         cout << "-------------------------\n";

    //     }
    ofstream myfile;
    myfile.open(into);
    if (myfile.is_open())
    {
        cout << "the file is successfully open!" << endl;
        myfile << "\t\tProduct Information" << endl;
        myfile << "------------------------------------------------------" << endl;
        for (int index = 0; index < pro.size(); index++)
        {
            myfile << "product ID : " << pro[index].productid << endl;
            myfile << "Name : " << pro[index].name << endl;
            myfile << "Catalogue : " << pro[index].cost << endl;
            myfile << "Cost : " << pro[index].cost << endl;
            myfile << "Price : " << pro[index].price << endl;
            myfile << "Quantity : " << pro[index].quantity << endl;
            myfile << "Discription : " << pro[index].discription << endl;

            myfile << "------------------------------------------------------" << endl;
        }
        myfile.close();
    }
    else
        cout << "Error opening file " << endl;
}

int main()
{
    vector<customer> user;
    vector<product> pro;
    vector<transaction> transact;
    string into = "product.txt";

    string record = "transaction.txt";

    string adder = ("customer.txt");

    customerAdder(adder, user);
    produc(into, pro);
    transactionsss(record, transact, pro, user);

    return 0;
}