#ifndef EMAIL_H
#define EMAIL_H
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "Utilities.h" //make upper


using namespace Utilities;

class Email
{
public:
	//Requires: EmailContent contains a string of messege contained in email
	//Modifies: EmailContent, EmailID
	//Effects: inilizes Email Content and Email ID
	Email(const std::string & EmailContent);
	Email() :text(""), score(0){}

	//Requires: 
	//Modifies: 
	//Effects: returns the email content
	std::string getEmailContent()const{ return text; };

	//Requires:
	//Modifies:
	//Effects: returns true or false depending on rather or not email contains key word
	bool DoesEmailContainKeyWord(const std::string & keyword) const; 

	//Requires:
	//Modifies:
	//Effects: returns the number of occurences for a given keyword
	int getNumberOfKeywordOccurences(const std::string & keyword) const; 

	int getTotalNumberOfKeyWords()const { return keywordsContained.size(); }
	//Requires:
	//Modifies:
	//Effects: Returns the number of words in the email
	int getWordCount() const;

	//Requires:
	//Modifies:
	//Effects: adds keywords to list of key words used in text
	void addKeyWord(std::string keyword){ keywordsContained.push_back(keyword);  }

	int getScore()const { return score;  }

	//Requires: Score be between 1 and 5 inclusive [1,5]
	//Modifies: score
	//Effects: sets score
	void setScore(const int & score){ this->score = score;  }
	
	void printKeywordsContained(); 

private:
	//Key words contained
	std::vector<std::string> keywordsContained; 
	//Contents of the email
	std::string text;
	//calculated score for email which will be based on filting 
	int score; 
};


//Requires: EmailContent contains a string of messege contained in email
//Modifies: EmailContent, EmailID
//Effects: inilizes Email Content and Email ID
Email::Email(const std::string & EmailContent) :score(0)
{
	//make every character uppercase
	text = makeUpper(EmailContent);
	
}


//Requires:
//Modifies:
//Effects: returns true or false depending on rather or not email contains key word
bool Email::DoesEmailContainKeyWord(const std::string & keyword) const
{
	if (text.find(keyword) != text.npos)
	{
		return true; 
	}
	else
	{
		return false; 
	}
	return  (text.find(keyword) > 0) ? true : false;
}

//Requires:
//Modifies:
//Effects: returns the number of occurences for a given keyword
int Email::getNumberOfKeywordOccurences(const std::string & keyword) const
{
	int numberOfOccurrences = 0; 
	int pos = 0;
	bool endOfLine = false; //there are no more occurences of keyword in text
	while (!endOfLine)
	{
		pos = text.find(keyword, pos);

		if (pos != text.npos)
		{
			numberOfOccurrences++;
			pos++;
		}
		else
		{
			endOfLine = true; 
		}
		

		
	}
	return numberOfOccurrences; 
}

//Requires: text does not have any extra spacing. All words are separated by a single space
//Modifies:
//Effects: Returns the number of words in the email
int Email::getWordCount() const
{
	return getNumberOfKeywordOccurences(" ") + 2;
}


void Email::printKeywordsContained()
{
	for (unsigned int i = 0; i < keywordsContained.size(); i++)
	{
		std::cout << keywordsContained.at(i) << " "; 
	}
	std::cout << std::endl;

}


#endif