#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For system function

using namespace std;

// string server = "DESKTOP-29SAKCH\\SQLEXPRESS"; // Escape backslash
// string database = "RETAL_DATA";
// string username = "sa";
// string password = "29211212";

// string connStr = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password;

string server = "DESKTOP-29SAKCH\\SQLEXPRESS"; // Escape backslash
string database = "RETAL_DATABASE";
string username = "sa";
string password = "29211212";
string sqlQuery = "SELECT * FROM Customer"; // Define your SQL query
//+ " -Q \"SELECT * FROM Customer"  + "\"";
string connStr = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password;
struct customer
{
    int customerId;
    string firstname;
    string lastname;
    string location;
    string phone;
};
struct Product
{
    int productId;
    string name;
    string catalogue;
    int cost;
    int price;
    int quantity;
    string description;
};

struct Transaction
{
    int customerId;
    int productId;
    int transactionId;
    int amount;
    int date;
};
void productInformation();

void EmployeeInformation();

void customerInformation();

void processProducts();

void InsertProduct();
void productInformation();

void InsertCustomer();

void compute();

void transactionRecord();

void updateQuantity();

void updatePrice();

int main()
{

    int result;

    cout << "What do you want to see" << endl;
    cout << "1. product info\n2. Employee Information\n3. Customer Information\n4. process product\n 5.insert product \n 6. insert custormer\n 7. Transaction\n " << endl;
    int n;
    cin >> n;

    switch (n)
    {
    case 1:
        productInformation();
        break;
    case 2:
        EmployeeInformation();
        break;
    case 3:
        customerInformation();
        break;
    case 5:
        InsertProduct();
        productInformation();
        break;
    case 6:
        InsertCustomer();
        break;
    case 7:
        compute();
        break;
    case 8:
        transactionRecord();
        break;
    case 9:
        updateQuantity();
        break;
    case 10:
        updatePrice();
        break;
    default:
        cout << "error" << endl;
    }

    return 0;
}
void updateQuantity()
{
    string pname;
    int q;
    cout << "Enter name of new bought product" << endl;
    cin >> pname;
    cout << "Enter the quantity: " << endl;
    cin >> q;

    string update = connStr + " -Q \"update product set quantity = quantity + " + to_string(q) + "where name = '" + pname + "'"
                                                                                                                            "\"";
    system(update.c_str());
}

void updatePrice()
{
    string pname;
    int np;
    cout << "Enter name of product you want to update the price: " << endl;
    cin >> pname;
    cout << "Enter the new price: " << endl;
    cin >> np;

    string update = connStr + " -Q \"update product set price = " + to_string(np) + "where name = '" + pname + "'"
                                                                                                               "\"";
    system(update.c_str());
}

void transactionRecord()
{

    string pname;
    int cid;
    int amount;

    cout << "Which product do you want to purchase: ";
    cin >> pname;

    // SQL query to check if the product exists with the given product code
    string check_query = connStr + " -Q \"SELECT COUNT(*) FROM product WHERE name = '" + pname + "'\" -h-1 -W";

    FILE *pipe = _popen(check_query.c_str(), "r");
    if (!pipe)
    {
        cout << "Failed to run query.\n";
        return;
    }
    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        result += buffer;
    }
    _pclose(pipe);

    int count = stoi(result);
    if (count == 0)
    {
        cout << "\n\n\t Product not found.";
        return; // Exit the function
    }

    char ans;
    cout << "Are you new customer or not (y/n)";
    cin >> ans;
    if (ans == 'y' || ans == 'Y')
    {
        InsertCustomer();
    }
    else
    {
        cout << "Enter your ID";
        cin >> cid;

        // string check_id = connStr + " -Q \"SELECT COUNT(*) FROM customer WHERE customerid = " + to_string(cid) + "\" -h-1 -W";

        // FILE* p = _popen(check_id.c_str(),"r");
        // if(!p){
        //     cout<< "Failed to run query.\n";
        //     return;
        // }
        // char buf[128];
        // result = "";
        //  while (fgets(buf, sizeof(buf), pipe) != NULL) {
        //     result += buf;
        // }
        // _pclose(p);
        // count = stoi(result);
        // if (count == 0) {

        // }

        cout << "Enter the amount you want to Purchase";
        cin >> amount;
        string transact = connStr + " -Q \"insert into [transaction] (productid, customerid, amount) values ((select productid from product where [name] = '" + pname + "'), " + to_string(cid) + ", " + to_string(amount) + ")\"";

        string update = connStr + " -Q \"update product set quantity = quantity - " + to_string(amount) + "where name = '" + pname + "'"
                                                                                                                                     "\"";

        system(transact.c_str());
        system(update.c_str());
    }
    }

    void InsertProduct()
    {
        Product products;
        cout << "Insert product Information" << endl;
        cout << "Product Name ";
        cin >> products.name;
        cout << "Product Catalogue : ";
        cin >> products.catalogue;
        cout << "Product Cost : ";
        cin >> products.cost;
        cout << "Product Price : ";
        cin >> products.price;
        cout << "Product Quantity : ";
        cin >> products.quantity;
        cin.ignore();
        cout << "Product description : ";
        getline(cin, products.description);

        string add = connStr + " -Q \"INSERT INTO Product (name, catalogue , cost, price, quantity,description) VALUES ( " + "'" + products.name + "'," + "'" + products.catalogue + "'," + to_string(products.cost) + "," + to_string(products.price) + "," + to_string(products.quantity) + ", '" + products.description + "'"
                                                                                                                                                                                                                                                                                                                             ")\"";

        system(add.c_str());

        cout << "product added successfully" << endl;
    }
    void InsertCustomer()
    {
        customer custinfo;
        cout << "Enter your customer information here:  " << endl;
        cout << "Enter first name : ";
        cin >> custinfo.firstname;
        cout << "Enter last name : ";
        cin >> custinfo.lastname;
        cin.ignore();
        cout << "Enter location : ";
        getline(cin, custinfo.location, '\n');
        cout << "Enter phone number : ";
        cin >> custinfo.phone;

        string custom = connStr + " -Q \"INSERT INTO Customer ( firstName,  lastName, [location],phone) VALUES ( " + "'" + custinfo.firstname + "'," + "'" + custinfo.lastname + "'," + "'" + custinfo.location + "'," + "'" + custinfo.phone + "'"
                                                                                                                                                                                                                                                ")\"";

        system(custom.c_str());

        cout << "product added successfully" << endl;
    }
    void customerInformation()
    {
        string Info = connStr + " -Q \"select * from customer\"";
        system(Info.c_str());
    }
    void productInformation()
    {
        string Info = connStr + " -Q \"select * from Product\"";
        system(Info.c_str());
    }
    void EmployeeInformation()
    {
        string Info = connStr + " -Q \"select * from employeeInfo\"";
        system(Info.c_str());
    }
    void compute()
    {
        string pts = connStr + " -Q \"select sum(price * amount) as TotalSale,sum((price * amount) - (cost * amount)) as profit,sum(price * amount) * 0.15 as Tax from [transaction] T join product P on T.productid  = P.productid;\"";
        system(pts.c_str());
    }
