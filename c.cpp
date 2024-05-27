#include <iostream>
#include <cstdlib> // For system function

using namespace std;

int main()
{
    // Construct the SQL Server connection string
    string server = "DESKTOP-23P8VTG\\SQLEXPRESS"; // Escape backslash
    string database = "project";
    string username = "sa";
    string password = "admin";
    string sqlQuery = "SELECT * FROM Customersa"; // Define your SQL query
    string connStr = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \" "  + "\"";

    // Execute the SQL Server connection command
    int result = system(connStr.c_str());

    if (result == 0)
    {
        cout << "Query executed successfully!" << endl;
    }
    else
    {
        cerr << "Failed to execute the query." << endl;
    }

    return 0;
}