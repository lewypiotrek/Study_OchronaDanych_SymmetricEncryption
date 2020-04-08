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

void EncryptionFromFile(string InputFileName, int key)
{
	fstream Handler;
	fstream	HandlerOut;
	char sign;
	int intSign, shift;

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

			HandlerOut.open("Encrypted.txt", ios::out);
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
		cout << "Encrypted.\n";
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


int main()
{
	cout << "----------------------------------------------------------\n\tPiotr Lewandowski - szyfr symetryczny\n----------------------------------------------------------\n";
	

	//cout << DescriptionChar('0',-2);

	//cout << "Encripting ... \n";
	EncryptionFromFile("test.txt", 3);



	cout << "\n\n\t";
	system("pause");
	return 0;
}