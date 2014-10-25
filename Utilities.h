#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <cstring>
#include <vector>

namespace Utilities
{
	//Requires:
	//Modifies: input
	//Effects: make every character in uppercase 
	std::string  makeUpper(const std::string & inputText)
	{
		std::string input = inputText; 
		for (unsigned int i = 0; i < input.size(); i++)
		{
			input.at(i) = toupper(input.at(i));
		}
		
		return input;
	}
	


	

}

#endif