#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int SIZE = 1000;
int tape[SIZE] = {0};
int* dp = tape;
int position = 0;

void interactive();
void compile(char* input);
void executeMode(char* input);
void execute(const char* input);
const char* stringFromFile(char* inputFile);

int main(int argc, char *argv[])
{
	for(int i = 1; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
	
	if(argc == 1)
		interactive();
	else if(argc == 3)
	{
		char* first = argv[1];
		char* second = argv[2];
		if (first[0] == '-' && first[1] == 'c')
		{
			compile(second);
		}
		else if (first[0] == '-' && first[1] == 'e')
		{
			executeMode(second);
		}
		else
		{
			cout << "Arguments passed did not fit the formatting expected. Please try again." << endl;
		}
	}
	
	else
	{
		cout << "Improper number of arguments passed. Please try again." << endl;
	}
	
	return 0;
}

void compile(char* inputFile)
{
	cout << "Entered compile mode. Compiling file: " << inputFile << endl;
	const char* input = stringFromFile(inputFile);
	cout << "File contents: " << input << endl;
	
	int i = 0;
	int loopCount = 1;
	
	cout 	<< "#include <iostream>" 	<< endl 
			<< "const int SIZE = 1000;" << endl
			<< "int tape[SIZE] = {0};"	<< endl
			<< "int *dp = tape;" 		<< endl << endl
			<< "int main() {" 			<< endl;
	while(input[i] != '\0')
	{
		for(int j = 0; j < loopCount; ++j)
			cout << "   ";
		
		switch(input[i])
		{
			case '+' :
			cout << "++*dp;";
			break;
			
			case '-' :
			cout << "--*dp;";
			break;
			
			case '>' :
			cout << "++dp;";
			break;
			
			case '<' :
			cout << "--dp;";
			break;
			
			case ':' :
			cout << "std::cout << *dp;";
			break;
			
			case '.' :
			cout << "std::cout << ((char) *dp);";
			break;
			
			case '{' :
			cout << "while (*dp) {";
			++loopCount;
			break;
			
			case '}' :
			cout << '}';
			--loopCount;
			break;
			
			default:
			++i;
			continue;
		}
			
		cout << endl;
		++i;
	}
	
	cout << endl << '}';
	
}

void executeMode(char* inputFile)
{
	cout << "Entered execute mode. Executing file: " << inputFile << endl;
	const char* input = stringFromFile(inputFile);
	cout << "File contents: " << input << endl;
	execute(input);
	
}

void execute(const char* input)
{
	int i = 0;
	while(input[i] != '\0')
	{
		switch(input[i])
			{
				case '+' :
				++*dp;
				break;
				
				case '-' :
				--*dp;
				break;
				
				case '>' :
				++dp;
				++position;
				break;
				
				case '<' :
				--dp;
				if(position > 0)
				--position;
				break;
				
				case ':' :
				cout << *dp;
				break;
				
				case '.' :
				cout << ((char) *dp);
				break;
				
				case '{' :
					{
						int j = (i+1);
						int braceCounter = 0;
						int loopClose = 0;
						while(true)
						{
							if(input[j] == '{')
							{
								braceCounter++;
							}
							else if(input[j] == '}')
							{
								if(braceCounter == 0)
								{
									loopClose = j;
									break;
								}
								else
								{
									braceCounter--;
								}
							}
							++j;
						}
						
						if(!(*dp))
						{
							i = loopClose;
							break;
						}
						
						string loopInput;
						int loopOpen = i;
						for(int n = (i + 1); n < loopClose; ++n)
						{
							loopInput += input[n];
						}
						execute(loopInput.c_str());
						
						i = loopOpen - 1;
						break;
					}
					
				default:
				break;
		}
		++i;
	}
}

void interactive()
{
	cout << "Entered interactive mode." << endl;
	int start = 0;
	int end = 10;
	char ptr = 28;
	while(true)
	{
		if(position < 5)
		{
			start = 0;
			end = 10;
		}
		else
		{
			start = position - 5;
			end = position + 5;
		}
		
		cout << "INDEX:   ";
		
		int i;
		for(i = start; i < end; ++i)
		{
			cout << setw(5) << i;
		}
		cout << endl;
		
		cout << "DATA:    ";
		for(i = start; i < end; ++i)
		{
			cout << setw(5) << tape[i];
		}
		cout << endl;
		
		cout << "CHAR:    ";
		for(i = start; i < end; ++i)
		{
			cout << setw(5) << ((char)tape[i]);
		}
		cout << endl;
		
		cout << "POINTER: ";
		if(position >= 5)
		{
			for(i = 0; i < 5; i++)
			{
				cout << "     ";
			}
			cout << setw(5) << ptr << endl;
		}
		else
		{
			for(i = 0; i < position; i++)
			{
				cout << "     ";
			}
			cout << setw(5) << ptr << endl;
		}
		
		bool valid = false;
		string command;
		do
		{
			cout << "Please enter a string of commands: " << endl;
			cin >> command;
			if(cin.good())
			{
				valid = true;
			}
			else
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << "Invalid input. Please re-enter." << endl;
			}
		} while (!valid);
		if(command == "exit")
			break;
		execute(command.c_str());
	}
}

const char* stringFromFile(char* inputFile)
{
	ifstream fin(inputFile);
	string fileContents;
	if(!fin)
	{
		cout << "Invalid file name. Could not read from file " << inputFile;
	}
	
	while(fin)
	{
		char c = fin.get();
		fileContents += c;
	}
	
	return fileContents.c_str();
}