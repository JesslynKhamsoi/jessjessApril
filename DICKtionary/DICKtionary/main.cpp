//int main(const char *argv []) 
//{
//	return 0;
//}

#include "dictionary.h"

int main(int argc,char *argv [])
{
	string file = argv[1];
	
	Dictionary test;
	test.parser(file);
	string str;
	char c;
		cout << "\nEnter a word to define: ";
	while (getline(cin, str))
	{
		for (auto & c : str)
		{
			c = toupper(c);
		}
		if (!(test.contains(str)))
		{
			cout << "Word not found.\n";
		}
		cout << "\nEnter a word to define: ";
		str = "";
	}
	
}