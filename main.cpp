#include "Curriculum.h"
#include "Email.h"
#include "Utilities.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std; 


//Requires: number of emails corresponds with the number of strings in email text, there are number of text email objects created
//Modifies: emails, curriculum
//Effects: adds data  curriculum and emails
void inputData(std::string curriculumText, vector<std::string> & emailText,vector<int> & scores, Curriculum & curriculum, std::vector<Email> & emails)
{
	

	for (unsigned int i = 0; i < emailText.size(); i++)
	{
		emails.at(i) = Email(emailText.at(i));
		emails.at(i).setScore(scores.at(i));
	}
}

void filterData(Curriculum & curriculum, std::vector<Email> & emails)//filters all emails using given keywords
{
	for (unsigned int i = 0; i < emails.size(); i++)
	{
		curriculum.filterByKeyword(emails.at(i));
	}

}

void outPutData(Curriculum & curriculum, std::vector<Email> & emails)
{
	for (unsigned int i = 0; i < emails.size(); i++)
	{
		//cout << "Email #: " << i + 1 << endl;
		//number of key words used
	//	cout << "Number of keywords used: " << 
		//cout << emails.at(i).getTotalNumberOfKeyWords() << endl;
		//cout << "Key words used: " << endl;
	//	emails.at(i).printKeywordsContained(); 
	//	cout << "Number of words in message: " <<
		cout <<emails.at(i).getWordCount() << endl;
		//cout << "Given Score: " << emails.at(i).getScore() << endl << endl;

	}

}

void useFunction()
{
	ifstream inputfile("emails.txt");
	string inputtext; 
	vector<string> emails; 
	vector<int> scores;
	string inputscore; 
	
	

	while (!inputfile.eof())
	{
		getline(inputfile, inputtext);
		getline(inputfile, inputscore);
		emails.push_back(inputtext);
		scores.push_back(atoi(inputscore.c_str()));
	}

	Curriculum curriculum(" ");
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


	vector<Email> emailsvec(emails.size());

	inputData(" ", emails, scores, curriculum, emailsvec); 
	filterData(curriculum, emailsvec); 
	outPutData(curriculum, emailsvec); 

}

using namespace std; 

int main()
{
	/*
	//Input emails
	Email TestEmail("I believe that one day I will be a successful Engineer\n");
	cout << "Text " << TestEmail.getEmailContent() << endl << " contains ";
	cout << TestEmail.getWordCount() << " words" << endl;
	//Input Curriculums
	Curriculum TestCurriculum("Describe you ambitions");
	TestCurriculum.addKeyWord("Engineer");
	TestCurriculum.addKeyWord("success");
	TestCurriculum.addKeyWord("future");

	//createScores for emails based on Curriculums

	TestCurriculum.filterByKeyword(TestEmail); 
	*/
	useFunction();


	return 0; 
}



