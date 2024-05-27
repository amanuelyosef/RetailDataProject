#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string server = "DESKTOP-29SAKCH\\SQLEXPRESS"; 
string database = "RETAL_DATABASE";
string username = "sa";
string password = "29211212";
string sqlQuery = "SELECT * FROM Customer"; 
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

struct Transaction {
    int customerId;
    int productId;
    int transactionId;
    int amount;
    int date; 
};


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
    int result;

    cout << "Which product do you want to purchase: ";
    cin >> pname;
    cout << "Enter your ID";
    cin >> cid;
    cout << "Enter the amount you want to Purchase";
    cin >> amount;

    string transact = connStr + " -Q \"insert into [transaction] (productid, customerid, amount) values ((select productid from product where [name] = '" + pname + "'), " + to_string(cid) + ", " + to_string(amount) + ")\"";

    string update = connStr + " -Q \"update product set quantity = quantity - " + to_string(amount) + "where name = '" + pname + "'""\"";

    system(transact.c_str());
    system(update.c_str());
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


    string custom = connStr + " -Q \"INSERT INTO Customer ( firstName,  lastName, [location],phone) VALUES ( " + "'" + custinfo.firstname + "'," + "'" + custinfo.lastname + "'," + "'" + custinfo.location + "'," + "'" + custinfo.phone + "'"")\"";

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



int main()
{
    int ans;

    cout<<"welcome to our Data management system"<<endl;
  label:
    cout<<"1) Display inforamtion on the database"<<endl;
    cout<<"2) Insert information"<<endl;
    cout<<"3) Update data"<<endl;

    cout<<"Enter your choice: "<<endl;
    cin>>ans;

    if(ans==1){
        cout<<"1)Display information about sales"<<endl;
        cout<<"2)Display Employee information"<<endl;
        cout<<"3)Display Customer information"<<endl;
        cout<<"4)Display Product information"<<endl;
        cout<<"5)Back To Main "<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>ans;

        if(ans==1){
            compute();

        }else if(ans==2){
            EmployeeInformation();
            
        }else if(ans==3){
            customerInformation();
            
        }else if(ans==4){
            productInformation();
        }else if(ans==5){
            goto label;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }else if(ans==2){
        cout<<"1) New customer inforamtion"<<endl;
        cout<<"2) New product inforamtion"<<endl;
        cout<<"3) Order"<<endl;
        cout<<"4) Main Menu "<<endl;

        cout<<"Enter your choice: "<<endl;
        cin>>ans;

        if(ans==1){
            InsertCustomer();
        }else if(ans==2){
            InsertProduct();
        }else if(ans==3){
            transactionRecord();
        
        }else if(ans==4){
            goto label;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }else if(ans==3){
        cout<<"1) Update product price"<<endl;
        cout<<"2) New added product"<<endl;
        
        cout<<"Enter your choice: "<<endl;
        cin>>ans;

        if(ans==1){
            updatePrice();
        }else if(ans==2){
            updateQuantity();
        }else{
            cout<<"Invalid input"<<endl;
        }
    }
    

    return 0;
}
