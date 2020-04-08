#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

inline int CheckChar(char sign)
{
	//	small letter
	if (sign >= 'a' && sign <= 'z') return 0;
	//	capital letter
	if (sign >= 'A' && sign <= 'Z') return 1;
	//	number
	if (sign >= '0' && sign <= '9')	return 2;
	//	the rest
	return 3;
}

char EncryptionChar(char sign, int key)
{
	int intSign = (int)sign;
	int shift = intSign + key;

	// DECRIPTING
	switch (CheckChar(sign))
	{
	case 0:	// small letter
		if (shift > 'z')
		{
			intSign = '0' + (shift - 'z') - 1;
			return (char)intSign;
		}
		else if (shift < 'a')
		{
			intSign = '9' + (shift - 'a') + 1;
			return (char)intSign;
		}
		else
		{
			intSign = intSign + key;
			return (char)intSign;
		}
		break;

	case 1:
		if (shift > 'Z')
		{
			intSign = '0' + (shift - 'Z') - 1;
			return (char)intSign;
		}
		else if (shift < 'A')
		{
			intSign = '9' + (shift - 'A') + 1;
			return (char)intSign;
		}
		else
		{
			intSign = intSign + key;
			return (char)intSign;
		}
		break;

	case 2:
		if (shift > '9')
		{
			intSign = 'a' + (shift - '9') - 1;
			return (char)intSign;
		}
		else if (shift < '0')
		{
			intSign = 'z' + (shift - '0') + 1;
			return (char)intSign;
		}
		else
		{
			intSign = intSign + key;
			return (char)intSign;
		}
		break;

	case 3:
		return sign;
		break;

	default:
		throw "Incorrect input file - unexpected char in file.";
		return '#';
		break;
	}
}

void EncryptionFromFile(string InputFileName,string OutputFileName, int key)
{
	fstream Handler;
	fstream	HandlerOut;
	char sign;

	try
	{
		Handler.open(InputFileName, ios::in);
		if (Handler.good())
		{
			// Checking how many chars are contained in the file
			Handler.seekg(0, ios::end);
			int size;
			size = Handler.tellg();
			Handler.seekg(0);

			HandlerOut.open(OutputFileName, ios::out);
			if (HandlerOut.good())
			{
				for (int i = 0; i < size; i++)
				{
					Handler.get(sign);
					HandlerOut << EncryptionChar(sign, key);
				}
			}
			else
			{
				throw "Cannot save/open Encrypted.txt";
			}								
		}
		else
		{
			string error = "Cannot open file " + InputFileName;
			throw error;
		}

		Handler.close();
		cout << "Done.\n";
	}
	catch(string & error)
	{
		cout << "\nERROR:\t" + error + "\n";
	}
	catch (...)
	{
		cout << "\nERROR:\t Unhandled exception \n";
	}
}

void DecriptionFromFile(string InputFileName, int key)
{
	key = key * (-1);
	EncryptionFromFile(InputFileName, "Decrypted.txt", key);
}

int main()
{
	cout << "----------------------------------------------------------\n\tPiotr Lewandowski - szyfr symetryczny\n----------------------------------------------------------\n";
	cout << "\n\t****** MENU: ******\n\n\t 1. Encription \n\t 2. Decription \n\t 3. Letter counter \n";

	string name;
	int menu, key;
	cin >> menu;

	switch (menu)
	{
	case 1:
		cout << "Encripting ... \n";
		
		cout << "\tInsert name of file: ";
		cin >> name;
		cout << "\n\tInsert  key:";
		cin >> key;

		EncryptionFromFile(name, "Encrypted.txt", key);

		break;

	case 2:
		cout << "Decripting ... \n";
		cout << "\tInsert name of file: ";
		//cin >> name;
		name = "Encrypted.txt";
		cout << "\n\tInsert  key:";
		cin >> key;

		DecriptionFromFile(name, key);
		
		break;

	case 3:

		break;
	}

	
	



	cout << "\n\n\t";
	system("pause");
	return 0;
}