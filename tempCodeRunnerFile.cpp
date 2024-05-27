#include <iostream>
#include <string>
#include <cstdlib> // For exit function
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

using namespace std;

// Database credentials should be stored securely
const string SERVER = "DESKTOP-29SAKCH\\SQLEXPRESS";
const string DATABASE = "RETAL_DATABASE";
const string USERNAME = "sa";
const string PASSWORD = "29211212";

// Function prototypes
void handleError(SQLHANDLE handle, SQLSMALLINT type, RETCODE retCode);
void updateQuantity(SQLHDBC dbc);
void updatePrice(SQLHDBC dbc);
void transactionRecord(SQLHDBC dbc);
void InsertProduct(SQLHDBC dbc);
void InsertCustomer(SQLHDBC dbc);
void customerInformation(SQLHDBC dbc);
void productInformation(SQLHDBC dbc);
void EmployeeInformation(SQLHDBC dbc);
void compute(SQLHDBC dbc);
void processProducts(SQLHDBC dbc);

int main() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret; // ODBC API return status

    // Allocate an environment handle
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);

    // Allocate a connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    // Connect to the database
    string connStr = "DRIVER={SQL Server};SERVER=" + SERVER + ";DATABASE=" + DATABASE + ";UID=" + USERNAME + ";PWD=" + PASSWORD + ";";
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)connStr.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(dbc, SQL_HANDLE_DBC, ret);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        exit(EXIT_FAILURE);
    }

    int choice;
    while (true) {
        cout << "What do you want to see" << endl;
        cout << "1. Product Info" << endl;
        cout << "2. Employee Information" << endl;
        cout << "3. Customer Information" << endl;
        cout << "4. Process Products" << endl;
        cout << "5. Insert Product" << endl;
        cout << "6. Insert Customer" << endl;
        cout << "7. Transaction" << endl;
        cout << "8. Compute" << endl;
        cout << "9. Update Quantity" << endl;
        cout << "10. Update Price" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                productInformation(dbc);
                break;
            case 2:
                EmployeeInformation(dbc);
                break;
            case 3:
                customerInformation(dbc);
                break;
            case 4:
                processProducts(dbc);
                break;
            case 5:
                InsertProduct(dbc);
                break;
            case 6:
                InsertCustomer(dbc);
                break;
            case 7:
                transactionRecord(dbc);
                break;
            case 8:
                compute(dbc);
                break;
            case 9:
                updateQuantity(dbc);
                break;
            case 10:
                updatePrice(dbc);
                break;
            case 11:
                // Disconnect and free handles
                SQLDisconnect(dbc);
                SQLFreeHandle(SQL_HANDLE_DBC, dbc);
                SQLFreeHandle(SQL_HANDLE_ENV, env);
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void handleError(SQLHANDLE handle, SQLSMALLINT type, RETCODE retCode) {
    SQLSMALLINT i = 0;
    SQLINTEGER native;
    SQLCHAR state[7];
    SQLCHAR text[256];
    SQLSMALLINT len;
    SQLRETURN ret;

    while ((ret = SQLGetDiagRec(type, handle, ++i, state, &native, text, sizeof(text), &len)) != SQL_NO_DATA) {
        cout << "Message: " << text << endl;
        cout << "SQLSTATE: " << state << endl;
        cout << "Native error code: " << native << endl;
    }
}

void updateQuantity(SQLHDBC dbc) {
    string pname;
    int q;
    cout << "Enter name of new bought product: ";
    cin >> pname;
    cout << "Enter the quantity: ";
    cin >> q;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "UPDATE Product SET quantity = quantity + ? WHERE name = ?";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &q, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)pname.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void updatePrice(SQLHDBC dbc) {
    string pname;
    int np;
    cout << "Enter name of product you want to update the price: ";
    cin >> pname;
    cout << "Enter the new price: ";
    cin >> np;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "UPDATE Product SET price = ? WHERE name = ?";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &np, 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)pname.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void transactionRecord(SQLHDBC dbc) {
    string pname;
    int cid;
    int amount;

    cout << "Which product do you want to purchase: ";
    cin >> pname;
    cout << "Enter your ID: ";
    cin >> cid;
    cout << "Enter the amount you want to purchase: ";
    cin >> amount;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "INSERT INTO [transaction] (productid, customerid, amount) VALUES ((SELECT productid FROM Product WHERE [name] = ?), ?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)pname.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &cid, 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &amount, 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    updateQuantity(dbc);
}

void InsertProduct(SQLHDBC dbc) {
    Product products;
    cout << "Insert product information:" << endl;
    cout << "Product Name: ";
    cin >> products.name;
    cout << "Product Catalogue: ";
    cin >> products.catalogue;
    cout << "Product Cost: ";
    cin >> products.cost;
    cout << "Product Price: ";
    cin >> products.price;
    cout << "Product Quantity: ";
    cin >> products.quantity;
    cin.ignore();
    cout << "Product Description: ";
    getline(cin, products.description);

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "INSERT INTO Product (name, catalogue, cost, price, quantity, description) VALUES (?, ?, ?, ?, ?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)products.name.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)products.catalogue.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &products.cost, 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &products.price, 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &products.quantity, 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)products.description.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void InsertCustomer(SQLHDBC dbc) {
    Customer cust;
    cout << "Insert customer information:" << endl;
    cout << "First Name: ";
    cin >> cust.fname;
    cout << "Last Name: ";
    cin >> cust.lname;
    cout << "Date of Birth: ";
    cin >> cust.dob;
    cout << "Email: ";
    cin >> cust.email;
    cout << "City: ";
    cin >> cust.city;
    cin.ignore();
    cout << "Address: ";
    getline(cin, cust.address);

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "INSERT INTO Customer (fname, lname, dob, email, city, address) VALUES (?, ?, ?, ?, ?, ?)";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.fname.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.lname.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.dob.c_str(), 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.email.c_str(), 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.city.c_str(), 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cust.address.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void customerInformation(SQLHDBC dbc) {
    string cname;
    cout << "Enter customer name: ";
    cin >> cname;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "SELECT * FROM Customer WHERE fname LIKE ?";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    string cnamePattern = "%" + cname + "%";
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)cnamePattern.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLCHAR fname[50], lname[50], dob[50], email[50], city[50], address[100];
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_CHAR, fname, sizeof(fname), NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, lname, sizeof(lname), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, dob, sizeof(dob), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, email, sizeof(email), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, city, sizeof(city), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, address, sizeof(address), NULL);
            cout << "Customer Name: " << fname << " " << lname << endl;
            cout << "Date of Birth: " << dob << endl;
            cout << "Email: " << email << endl;
            cout << "City: " << city << endl;
            cout << "Address: " << address << endl << endl;
        }
    } else {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void productInformation(SQLHDBC dbc) {
    string pname;
    cout << "Enter product name: ";
    cin >> pname;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "SELECT * FROM Product WHERE name LIKE ?";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    string pnamePattern = "%" + pname + "%";
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)pnamePattern.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLCHAR name[50], catalogue[50], description[100];
        SQLINTEGER cost, price, quantity;
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_CHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, catalogue, sizeof(catalogue), NULL);
            SQLGetData(stmt, 3, SQL_C_SLONG, &cost, 0, NULL);
            SQLGetData(stmt, 4, SQL_C_SLONG, &price, 0, NULL);
            SQLGetData(stmt, 5, SQL_C_SLONG, &quantity, 0, NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, description, sizeof(description), NULL);
            cout << "Product Name: " << name << endl;
            cout << "Catalogue: " << catalogue << endl;
            cout << "Cost: " << cost << endl;
            cout << "Price: " << price << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Description: " << description << endl << endl;
        }
    } else {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void EmployeeInformation(SQLHDBC dbc) {
    string ename;
    cout << "Enter employee name: ";
    cin >> ename;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "SELECT * FROM Employee WHERE fname LIKE ?";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    string enamePattern = "%" + ename + "%";
    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)enamePattern.c_str(), 0, NULL);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLCHAR fname[50], lname[50], dob[50], email[50], city[50], address[100];
        SQLINTEGER salary;
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_CHAR, fname, sizeof(fname), NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, lname, sizeof(lname), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, dob, sizeof(dob), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, email, sizeof(email), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, city, sizeof(city), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, address, sizeof(address), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &salary, 0, NULL);
            cout << "Employee Name: " << fname << " " << lname << endl;
            cout << "Date of Birth: " << dob << endl;
            cout << "Email: " << email << endl;
            cout << "City: " << city << endl;
            cout << "Address: " << address << endl;
            cout << "Salary: " << salary << endl << endl;
        }
    } else {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void compute(SQLHDBC dbc) {
    // Sample computation
    cout << "Performing a sample computation:" << endl;

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    string query = "SELECT AVG(price) FROM Product";
    SQLPrepare(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

    SQLRETURN ret = SQLExecute(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLDOUBLE avgPrice;
        SQLFetch(stmt);
        SQLGetData(stmt, 1, SQL_C_DOUBLE, &avgPrice, 0, NULL);
        cout << "Average Price of Products: " << avgPrice << endl;
    } else {
        handleError(stmt, SQL_HANDLE_STMT, ret);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

int main() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Allocate an environment handle
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    // Set the ODBC version environment attribute
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    // Allocate a connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    // Connect to the DSN (Data Source Name)
    ret = SQLConnect(dbc, (SQLCHAR*)"DSN_NAME", SQL_NTS, (SQLCHAR*)NULL, 0, NULL, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        handleError(dbc, SQL_HANDLE_DBC, ret);
        return EXIT_FAILURE;
    }

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Insert Customer" << endl;
        cout << "2. Insert Product" << endl;
        cout << "3. Get Customer Information" << endl;
        cout << "4. Get Product Information" << endl;
        cout << "5. Get Employee Information" << endl;
        cout << "6. Perform a Sample Computation" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                InsertCustomer(dbc);
                break;
            case 2:
                InsertProduct(dbc);
                break;
            case 3:
                customerInformation(dbc);
                break;
            case 4:
                productInformation(dbc);
                break;
            case 5:
                EmployeeInformation(dbc);
                break;
            case 6:
                compute(dbc);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 0);

    // Disconnect from the DSN
    SQLDisconnect(dbc);
    // Free the connection handle
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    // Free the environment handle
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return EXIT_SUCCESS;
}
