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

struct Transaction
{
    int customerId;
    int productId;
    int transactionId;
    int amount;
    int date;
};

void updateQuantity()
{
    system("cls");

    cout << "\t====================================================================" << endl;
    cout << "\t              UPDATE QUANTITY                " << endl;
    cout << "\t===================================================================" << endl;
    cout << "";
    string pname;
    int q;
    cout << "\tEnter name of new bought product" << endl;
    cin >> pname;
    cout << "\tEnter the quantity: " << endl;
    cin >> q;

    string update = connStr + " -Q \"update product set quantity = quantity + " + to_string(q) + "where name = '" + pname + "'"
                                                                                                                            "\"";
    system(update.c_str());
}

void updatePrice()
{
    system("cls");
    cout << "\t=================================================================" << endl;
    cout << "\t              UPDATE PRICE                   " << endl;
    cout << "\t=================================================================" << endl;
    string pname;
    int np;
    cout << "\tEnter name of product you want to update the price: " << endl;
    cin >> pname;
    cout << "\tEnter the new price: " << endl;
    cin >> np;

    string update = connStr + " -Q \"update product set price = " + to_string(np) + "where name = '" + pname + "'"
                                                                                                               "\"";
    system(update.c_str());
}

void transactionRecord()
{
    system("cls");
    cout << "\t=================================================================" << endl;
    cout << "\t              RECORD TRANSACTION             " << endl;
    cout << "\t=================================================================" << endl;

    string pname;
    int cid;
    int amount;
    int result;

    cout << "\tWhich product do you want to purchase: ";
    cin >> pname;
    cout << "\tEnter your ID";
    cin >> cid;
    cout << "\tEnter the amount you want to Purchase";
    cin >> amount;

    string transact = connStr + " -Q \"insert into [transaction] (productid, customerid, amount) values ((select productid from product where [name] = '" + pname + "'), " + to_string(cid) + ", " + to_string(amount) + ")\"";

    string update = connStr + " -Q \"update product set quantity = quantity - " + to_string(amount) + "where name = '" + pname + "'"
                                                                                                                                 "\"";

    system(transact.c_str());
    system(update.c_str());
}

void InsertProduct()
{
    system("cls");
    cout << "\t=================================================================" << endl;
    cout << "              INSERT PRODUCT                 " << endl;
    cout << "\t=================================================================" << endl;
    Product products;
    cout << "\tInsert product Information" << endl;
    cout << "\tProduct Name ";
    cin >> products.name;
    cout << "\tProduct Catalogue : ";
    cin >> products.catalogue;
    cout << "\tProduct Cost : ";
    cin >> products.cost;
    cout << "\tProduct Price : ";
    cin >> products.price;
    cout << "\tProduct Quantity : ";
    cin >> products.quantity;
    cin.ignore();
    cout << "\tProduct description : ";
    getline(cin, products.description);

    string add = connStr + " -Q \"INSERT INTO Product (name, catalogue , cost, price, quantity,description) VALUES ( " + "'" + products.name + "'," + "'" + products.catalogue + "'," + to_string(products.cost) + "," + to_string(products.price) + "," + to_string(products.quantity) + ", '" + products.description + "'"
                                                                                                                                                                                                                                                                                                                         ")\"";

    system(add.c_str());

    cout << "product added successfully" << endl;
}

void InsertCustomer()
{

    system("cls");
    cout << "\t=================================================================" << endl;
    cout << " \t        INSERT CUSTOMER INFORMATION         " << endl;
    cout << "\t=================================================================" << endl;
    customer custinfo;
    cout << "\tEnter your customer information here:  " << endl;
    cout << "\tEnter first name : ";
    cin >> custinfo.firstname;
    cout << "\tEnter last name : ";
    cin >> custinfo.lastname;
    cin.ignore();
    cout << "\tEnter location : ";
    getline(cin, custinfo.location, '\n');
    cout << "\tEnter phone number : ";
    cin >> custinfo.phone;

    string custom = connStr + " -Q \"INSERT INTO Customer ( firstName,  lastName, [location],phone) VALUES ( " + "'" + custinfo.firstname + "'," + "'" + custinfo.lastname + "'," + "'" + custinfo.location + "'," + "'" + custinfo.phone + "'"
                                                                                                                                                                                                                                            ")\"";

    system(custom.c_str());

    cout << "\t\tProduct added successfully" << endl;
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
    char ch;
    bool check;
    system("cls");
    system("color A0");
    int ans;
    cout << "\t||================================================================================================||" << endl;
    cout << "\t||           WELCOME TO OUR RETAIL  DATA MANAGEMENT SYSTEM                                        || " << endl;
    cout << "\t||================================================================================================||\n"
         << endl;
label:
    system("color A0");

    cout << "        ||==================================================================================" << endl;
    cout << "        ||===================             MAIN MENU            =============================\n"
         << endl;
    cout << "        ||      1. Display information on the database" << endl;
    cout << "        ||      2. Insert information" << endl;
    cout << "        ||      3. Update data\n"
         << endl;
    cout << "        ||==================================================================================" << endl;
    cout << "        ||==================================================================================" << endl;

    cout << "                   Enter your choice: ";
    cin >> ans;

    if (ans == 1)
    {
    D:
        system("color 1F");
        system("cls");
        cout << "\t==========================================================================================" << endl;
        cout << "\t      Display information on the database\n";
        cout << "\t==========================================================================================" << endl;
        cout << "\t||               1. Display information about sales                                       ||" << endl;
        cout << "\t||               2. Display Employee information                                          ||" << endl;
        cout << "\t||               3. Display Customer information                                          ||" << endl;
        cout << "\t||               4. Display Product information                                           ||" << endl;
        cout << "\t||               5. Back To Main                                                          ||" << endl;
        cout << "\t==========================================================================================" << endl;
        cout << "\t==========================================================================================\n"
             << endl;

        cout << "        Enter your choice: ";
        cin >> ans;

        if (ans == 1)
        {
            compute();
            cout << "\n\tWant to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 2)
        {
            EmployeeInformation();
            cout << "\n\tWant to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 3)
        {
            customerInformation();
            cout << "\n\tWant to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 4)
        {
            productInformation();
            cout << "\n         Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 5)
        {
            system("cls");
            goto label;
        }
        else if (ans == 0)
        {
            cout << "\t=======================================================" << endl;
            cout << "\t======================THANK YOU========================" << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid input" << endl;
            system("cls");
            goto D;
        }
    }
    else if (ans == 2)
    {
    I:
        system("color E0");
        system("cls");
        cout << "       ======================================================================================" << endl;
        cout << "            Insert information             \n";
        cout << "       ======================================================================================" << endl;
        cout << "                              1. New customer information" << endl;
        cout << "                              2. New product information" << endl;
        cout << "                              3. Order" << endl;
        cout << "                              4. Main Menu " << endl;
        cout << "       ======================================================================================" << endl;
        cout << "       ======================================================================================\n"
             << endl;
        cout << "                      Enter your choice : ";
        cin >> ans;

        if (ans == 1)
        {
            check = true;
            while (check)
            {
                InsertCustomer();
                cout << "\n     Want to add another data?:";
                cin >> ch;
                if (ch == 'y')
                    check = true;
                else
                    check = false;
            }
            cout << "\n         Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 2)
        {
            check = true;
            while (check)
            {
                InsertProduct();
                cout << "\n           Want to add another data?:";
                cin >> ch;
                if (ch == 'y')
                    check = true;
                else
                    check = false;
            }
            cout << "\n           Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 3)
        {
            check = true;
            while (check)
            {
                transactionRecord();
                cout << "\n         Want to add another record?:";
                cin >> ch;
                if (ch == 'y')
                    check = true;
                else
                    check = false;
            }
            cout << "\n             Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 4)
        {
            system("cls");
            goto label;
        }
        else if (ans == 0)
        {
            exit(0);
        }
        else
        {
            cout << "Invalid input" << endl;
            goto I;
        }
    }
    else if (ans == 3)
    {
    p:
        system("color 70");
        system("cls");
        cout << "\t==================================================================================" << endl;
        cout << "\t                     UPDATE DATA                     " << endl;
        cout << "\t==================================================================================" << endl;

        cout << "\t                    1. Update product price" << endl;
        cout << "\t                     2. New added product" << endl;
        cout << "\t                     3. Main Menu \n"
             << endl;

        cout << "\t=================================================================================" << endl;
        cout << "==================================================================================\n"
             << endl;
        cout << "         Enter your choice: ";
        cin >> ans;

        if (ans == 1)
        {
            check = true;
            while (check)
            {
                updatePrice();
                cout << "Want to add another record?:";
                cin >> ch;
                if (ch == 'y')
                    check = true;
                else
                    check = false;
            }
            cout << "Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 2)
        {
            check = true;
            while (check)
            {
                updateQuantity();
                cout << "Want to add another record?:";
                cin >> ch;
                if (ch == 'y')
                    check = true;
                else
                    check = false;
            }
            cout << "Want to Display or Add another information(y/n)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto label;
            }
        }
        else if (ans == 3)
        {
            system("cls");
            goto label;
        }
        else if (ans == 0)
        {
            cout << "\t=======================================================" << endl;
            cout << "\t======================THANK YOU========================" << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid input" << endl;
            goto p;
        }
    }
    else if (ans == 0)
    {
        cout << "\t=======================================================" << endl;
        cout << "\t======================THANK YOU========================" << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid input" << endl;
        system("cls");
        goto label;
    }

    return 0;
}
