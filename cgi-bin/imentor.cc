#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main() {
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><body>";

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "cfg2014!");

        /* Connect to the MySQL test database */
        con->setSchema("imentor");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT id,content,score FROM emails");

        while (res->next()) {
            cout << res->getString("content");
            cout << res->getString("score") << endl;
        }

        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << "</body></html>";

    return EXIT_SUCCESS;
}

