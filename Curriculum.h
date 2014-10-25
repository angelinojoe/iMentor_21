#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <string>
#include <vector>
#include "Utilities.h" //make upper
#include "Email.h"

using namespace Utilities;



class Curriculum
{

public:
	//Requires:
	//Modifies: text
	//Effects: Initailizes the Curriculum text 
	Curriculum(std::string textInput);

	//Requires:
	//Modifies:
	//Effects: Returns the Curriculum text
	std::string getCurriculumContent() const { return text; }

	//Requires:
	//Modifies:kewords
	//Effects: adds keywords into vector of keywords
	void addKeyWord(std::string keyword){ keywords.push_back(makeUpper(keyword)); numberOfKeywords++; }

	//Requires: index is between 0 and keywords.size() [0, keywords.size())
	//Modifies:kewords
	//Effects: returns key word at position index and "-1" if out of range
	std::string getKeyword(unsigned int index) const;

	//Requires: 
	//Modifies:
	//Effects: returns the number of keywords
	int getNumberOfKeyWords() const { return numberOfKeywords;  }

	//Requires: curriculum and email are both initialized
	//Modifies: email.score
	//Effects: Returns true of false if the email has passed a certain threshold of filtering
	//: will return true if at least 
	int filterByKeyword(Email & email);
private:
	std::string text;
	std::vector<std::string> keywords;
	int numberOfKeywords;

};

//Requires:
//Modifies: text
//Effects: Initilizes the Curriculum text 
Curriculum::Curriculum(std::string textInput) :numberOfKeywords(0)
{
	makeUpper(textInput);//make every character uppercase
	text = textInput; 
	

}

//Requires: index is between 0 and keywords.size() [0, keywords.size())
//Modifies:kewords
//Effects: returns keyword at position index and "-1" if out of range
std::string Curriculum::getKeyword(unsigned int index) const
{
	if (index < 0 || index >= keywords.size())
	{
		return "-1";
	}
	else
	{
		return keywords.at(index);
	}
}


int Curriculum::filterByKeyword(Email & email)
{
	int KeyWordindex = 0;
	int numberOfKeyWords = 0;


	while (KeyWordindex < getNumberOfKeyWords())
	{
		if (email.DoesEmailContainKeyWord(getKeyword(KeyWordindex)))
		{

			numberOfKeyWords += email.getNumberOfKeywordOccurences(getKeyword(KeyWordindex));
			email.addKeyWord(getKeyword(KeyWordindex));
			KeyWordindex++;

		}
	}

	return numberOfKeyWords;
}
#endif