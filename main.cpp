#include "Curriculum.h"
#include "Email.h"
#include "Utilities.h"
#include <iostream>


//Requires: curriculum and email are both initialized
//Modifies: email.score
//Effects: Returns true of false if the email has passed a certain threshold of filtering
//: will return true if at least 
int filterByKeyword(const Curriculum & curriculum, Email & email, int minKeywordCount)
{
	int KeyWordindex = 0;
	int numberOfKeyWords = 0;


	while (KeyWordindex < curriculum.getNumberOfKeyWords())
	{
		if (email.DoesEmailContainKeyWord(curriculum.getKeyword(KeyWordindex)))
		{

			numberOfKeyWords += email.getNumberOfKeywordOccurences(curriculum.getKeyword(KeyWordindex));
			email.addKeyWord(curriculum.getKeyword(KeyWordindex));
			KeyWordindex++;

		}
	}

	return numberOfKeyWords;
}


using namespace std; 

int main()
{
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

	filterByKeyword(TestCurriculum, TestEmail, 5); 

	return 0; 
}



