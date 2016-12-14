

#include "DICKtionary.h"

int main(int argc,char *argv []) //takes in a string, which will be treated as a file name
{
	string file = argv[1]; // turning char*[] into string
	
	Dictionary test; // create dictionary type
	test.parser(file); //call parser to create hash table with values
	string str; // for user input
	char c; //to change each char in user input to upper case
		cout << "\n\nEnter a word to define: "; //promt user
	while (getline(cin, str)) // this will get user input, as well as detect if they entered EOF
	{
		for (auto & c : str) //go through string and convert it to uppercase
		{
			c = toupper(c);
		}
		if (!(test.contains(str))) // searchin for word user entered, if found contains() prints definition
		{
			cout << "\n\nWord not found."; //if not found display message
		}
		cout << "\n\nEnter a word to define: "; //ask for another word
		str = ""; //clear string for next word
	}
	
}