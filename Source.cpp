#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>



using namespace std;

inline int CheckChar(char & sign)
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

char EncryptionChar(char & sign, int key)
{

	// ENCRYPTING
	
	//// Preparing correct key 
	if (key == 36 | key == 0 | key == -36)
	{
		return sign;
	}
	else if (key > 36)
	{
		key = key % 36;
	}
	else if (key < -36)
	{
		key = key % -36;
	}
	

	// Select correct case
	switch (CheckChar(sign))
	{
	case 0:	
		if (sign + key > 'z')
		{
			key = key + sign - 'z' - 1;
			sign = '0';
			EncryptionChar(sign, key);
		}
		else if (sign + key < 'a')
		{
			key = key + sign - 'a';
			sign = '9';
			EncryptionChar(sign, key);
		}
		else
		{
			return sign + key;
		}
		break;

	case 1:
		
		if (sign + key > 'Z')
		{
			key = key + sign - 'Z' - 1;
			sign = '0';
			EncryptionChar(sign, key);
		}
		else if (sign + key < 'A')
		{
			key = key + sign - 'A' + 1;
			sign = '9';
			EncryptionChar(sign, key);
		}
		else
		{
			return sign + key;
		}
		break;

	case 2:
		
		if (sign + key > '9')
		{
			key = key + sign - '9' - 1;
			sign = 'A';
			EncryptionChar(sign, key);
		}
		else if (sign + key < '0')
		{
			key = key + sign - '0' + 1;
			sign = 'Z';
			EncryptionChar(sign, key);
		}
		else 
		{
			return sign + key;
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

int LetterCounter(char & s, string & InputFileName)
{
	int counter = 0;
	fstream Handler;

	Handler.open(InputFileName, ios::in);

	if (Handler.good())
	{
		int counter = 0, size;
		char sign;

		// Checking how many chars are in the file
		Handler.seekg(0, ios::end);
		size = Handler.tellg();
		Handler.seekg(0);

		// Counting
		for (int i = 0; i < size; i++)
		{
			Handler.get(sign);
			if (sign == s)
			{
				counter++;
			}
		}
		return counter;
	}
	else
	{
		return 0;
	}

	Handler.close();
}

void CharacterCounterFromFile(string InputFileName, long double * arr)
{
	// capital letter 0-25
	int j = 0;
	for (char i = 'A'; i <= 'Z'; i++)
	{
		arr[j] = LetterCounter(i, InputFileName);
		j++;
	}

	// small letter 0-25
	j = 0;
	for (char i = 'a'; i <= 'z'; i++)
	{
		arr[j] += LetterCounter(i, InputFileName);
		
		j++;
	}
	
	double sum = 0;
	for (int i = 0; i < 36; i++)
		sum += arr[i];

	j = 26;
	for (char i = '0'; i <= '9'; i++)
	{
		arr[j] += LetterCounter(i, InputFileName);
		cout << "\t" << i << " -> " << (arr[j] * 100) / sum << "\n";
		j++;
	}

	j = 0;
	for (char i = 'a'; i <= 'z'; i++)
	{
		cout << "\t" << i << " -> " << (arr[j] * 100) / sum << "\n";
		j++;
	}


}

int main()
{
	cout << "-----------------------------------------------------\n\tPiotr Lewandowski - szyfr symetryczny\n-----------------------------------------------------\n";
	cout << "\n\t****** MENU: ******\n\n\t 1. Encription \n\t 2. Decription \n\t 3. Letter counter \n\n\t*******************\nOption: ";

	string name,name2;
	int menu, key, size;
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
		cin >> name;
		cout << "\n\tInsert key: ";
		cin >> key;
		DecriptionFromFile(name, key);
		break;

	case 3:

		cout << "\n\tCharacter counter: ... \n";
		size = 36;
		if (size != 0) {
			long double * CharCounter = new long double[size];

			for (int i = 0; i < size; i++)
			{
				CharCounter[i] = 0.0;
			}
			cout << "\tInsert name of  file: ";
			cin >> name;

			CharacterCounterFromFile(name, CharCounter);
			delete[]CharCounter;
		}
		break;	

	}

	

	cout << "\n\n\t";
	system("pause");
	return 0;
}