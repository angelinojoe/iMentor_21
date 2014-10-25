#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
 
#include <regex>

#include "Curriculum.h"
#include "Email.h"
#include "Utilities.h"
#include <vector>
#include <cmath>

using namespace std;

void inputData(std::string curriculumText, vector<std::string> & emailText,vector<int> & scores, Curriculum & curriculum, std::vector<Email> & emails)
{

	for (unsigned int i = 0; i < emailText.size(); i++)
	{
		emails.push_back(Email(emailText.at(i)));
		emails.back().setScore(scores.at(i));
	}
}

void filterData(Curriculum & curriculum, std::vector<Email> & emails)//filters all emails using given keywords
{
	for (unsigned int i = 0; i < emails.size(); i++)
	{
		curriculum.filterByKeyword(emails.at(i));
	}

}

void outPutData(Curriculum & curriculum, std::vector<Email> & emails, int id)
{
    if (id == -1) {
        for (unsigned int i = 0; i < emails.size(); i++)
        {
            cout << "Email #: " << i + 1 << "<br />";
            //number of key words used
            cout << "Number of keywords used: " << emails.at(i).getTotalNumberOfKeyWords() << "<br />";
            cout << "Key words used: ";
            emails.at(i).printKeywordsContained(); 
            cout << "<br />";
            cout << "Number of words in message: "  <<emails.at(i).getWordCount() << "<br />";
            cout << "Given Score: " << emails.at(i).getScore() << "<br />";
            cout << "Predicted Score: " << round(((0.3397*emails.at(i).getTotalNumberOfKeyWords() + .0061*emails.at(i).getWordCount() + 2.1566)) / 2) << "<br /><br />";

        }
    } else {
        cout << "Email #: " << id << "<br />";
        //number of key words used
        cout << "Number of keywords used: " << emails.at(id-1).getTotalNumberOfKeyWords() << "<br />";
        cout << "Key words used: ";
        emails.at(id-1).printKeywordsContained(); 
        cout << "<br />";
        cout << "Number of words in message: "  <<emails.at(id-1).getWordCount() << "<br />";
        cout << "Given Score: " << emails.at(id-1).getScore() << "<br />";
        cout << "Predicted Score: " << round(((0.3397*emails.at(id-1).getTotalNumberOfKeyWords() + .0061*emails.at(id-1).getWordCount() + 2.1566)) / 2) << "<br /><br />";
    }

}

void useFunction(vector<string>& emails, vector<int>& scores, string& curriculumText, int id)
{

	Curriculum curriculum(curriculumText);

	curriculum.addKeyWord("mindset");
	curriculum.addKeyWord("fix");
	curriculum.addKeyWord("growth");
	curriculum.addKeyWord("Success");
	curriculum.addKeyWord("college");
	curriculum.addKeyWord("hard");
	curriculum.addKeyWord("work");
	curriculum.addKeyWord("dedication");
	curriculum.addKeyWord("intelligence");
	curriculum.addKeyWord("lack");
	curriculum.addKeyWord("practice");
	curriculum.addKeyWord("high");
	curriculum.addKeyWord("low");
	curriculum.addKeyWord("moment");
	curriculum.addKeyWord("experience");
	curriculum.addKeyWord("event");
	curriculum.addKeyWord("positive");
	curriculum.addKeyWord("negative");

	vector<Email> emailsvec;

	inputData(curriculumText, emails, scores, curriculum, emailsvec); 
	filterData(curriculum, emailsvec); 
	outPutData(curriculum, emailsvec, id); 
}

void queryParse(std::string word, std::map<std::string, std::string>& queries) {
    std::string::size_type pos;

    for (pos = 0; pos < word.size(); ++pos)
    {
        if (word[pos] == '&')
            word[pos] = ' ';
    }

    std::istringstream sin(word);
    sin >> word;
    while (sin)
    {
        pos = word.find_first_of("=");
        if (pos != std::string::npos)
        {
            std::string key = word.substr(0,pos);
            std::string value = word.substr(pos+1);

            queries[key] = value;
        }
        sin >> word;
    }
}

namespace Utility {
    std::string urlEncode(const std::string &url);
    std::string urlDecode(const std::string &encoded);
     
    std::string charToHex(unsigned char c);
    unsigned char hexToChar(const std::string &str);
 
    std::string urlEncode(const std::string &toEncode) {
        std::ostringstream out;
         
        for(std::string::size_type i=0; i < toEncode.length(); ++i) {
            short t = toEncode.at(i);
             
            if(
                t == 45 ||          // hyphen
                (t >= 48 && t <= 57) ||       // 0-9
                (t >= 65 && t <= 90) ||       // A-Z
                t == 95 ||          // underscore
                (t >= 97 && t <= 122) ||  // a-z
                t == 126            // tilde
            ) {
                out << toEncode.at(i);
            } else {
                out << charToHex(toEncode.at(i));
            }
        }
         
        return out.str();
    }
 
    std::string urlDecode(const std::string &toDecode) {
        std::ostringstream out;
         
        for(std::string::size_type i=0; i < toDecode.length(); ++i) {
            if(toDecode.at(i) == '%') {
                std::string str(toDecode.substr(i+1, 2));
                out << hexToChar(str);
                i += 2;
            } else {
                out << toDecode.at(i);
            }
        }
         
        return out.str();
    }
 
    std::string charToHex(unsigned char c) {
        short i = c;
         
        std::stringstream s;
         
        s << "%" << std::setw(2) << std::setfill('0') << std::hex << i;
         
        return s.str();
    }
 
    unsigned char hexToChar(const std::string &str) {
        short c = 0;
         
        if(!str.empty()) {
            std::istringstream in(str);
             
            in >> std::hex >> c;
             
            if(in.fail()) {
                throw std::runtime_error("stream decode failure");
            }
        }
         
        return static_cast<unsigned char>(c);
    }
}

int main() {
    const char* query = getenv("QUERY_STRING");
    string query_string(query);

    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><body>";

    //cout << Utility::urlDecode(query_string) << "<br />";

    map<std::string, std::string> query_pairs;
    queryParse(Utility::urlDecode(query_string), query_pairs);

    map<std::string, std::string>::iterator it;
    int id = -1;

    for (std::map<string, string>::iterator it=query_pairs.begin(); it!=query_pairs.end(); ++it) {
        //cout << it->first << " => " << it->second << "<br />";
        if (it->first.compare("id") == 0) id = stoi(it->second);
    }

    //cout << "id is " << id;

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
        res = stmt->executeQuery("SELECT content FROM curriculums LIMIT 1");

        string curriculumText;

        while (res->next()) {
            curriculumText = res->getString("content");
        }

        res = stmt->executeQuery("SELECT content,score FROM emails");

        vector<std::string> emailText;
        vector<int> scores;

        while (res->next()) {
            emailText.push_back(res->getString("content"));
            scores.push_back(res->getInt("score"));
        }

        useFunction(emailText, scores, curriculumText, id);

/*
        Curriculum curriculum(curriculumText);
        std::vector<Email> emails;

        inputData(curriculumText, emailText, scores, curriculum, emails);
        outPutData(emails);
*/

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

