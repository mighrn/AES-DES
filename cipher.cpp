#include <string>
#include <fstream>
#include <iostream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

void displayHelp();
void parseArg(int argc, char** argv, string args []);

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 */
	
	string input[5];
	parseArg(argc, argv, input);
	
	ofstream fout(input[4]);
	if(!fout.is_open() || !fout.good())
	{
		cout << "ERROR! Unable to open output file\n";
		exit(-1);
	}

	if (input[0] == "AES")
	{
		CipherInterface* cipher = new AES();
		cout << "AES\n";
		
		unsigned char user_key[17];
		for(int i = 0; i < 16; i++)
		{
			user_key[i + 1] = input[1][i];
		}
		
		if(input[2] == "ENC")
		{
			cout << "attempting to set enc key\n";
			user_key[0] = 0x00;
			cipher->setKey(user_key);
			
			string text;
			char f;
			ifstream fin(input[3]);
			if (!fin.is_open() || !fin.good())
			{
				cout << "ERROR! Unable to open input file\n";
				exit(-1);
			}
			else
			{
				while(fin >> noskipws >> f)
				{
					text.push_back(f);
				}
				fin.close();
			}
			cout << "textsize: " << text.size() << endl;
			cout << "text from file: '" << text << "'\n";
			
			int cst;
			if(text.size() > 16)
			{
				int add = 16 - (text.size() % 16);
				if(add != 16)
				{
					cout << "WARNING! Last text block is not 16 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			else
			{
				int add = 16 - (text.size() % 16);
				if(add != 16)
				{
					cout << "WARNING! Last text block is not 16 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			
			unsigned char* plaintext = (unsigned char*)text.c_str();
			int const CIPHERTEXTSIZE = cst;
			unsigned char ciphertext[CIPHERTEXTSIZE];
			
			for(int i = 0; i < cst / 16; i++)
			{
				cout << "encrypting " << plaintext + (i * 16) << endl;
				unsigned char* cipherpart = cipher->encrypt(plaintext + (i * 16));
				for(int j = 0; j < 16; j++)
				{
					ciphertext[j + (i * 16)] = (*(cipherpart + j));
				}
			}
			cout << "Whole ciphertext: '";
			for(int n = 0; n < CIPHERTEXTSIZE; n++)
			{
				cout << ciphertext[n];
				fout << ciphertext[n];
			}
			cout << "'\n";
		}
		else
		{
			cout << "attempting to set dec key\n";
			user_key[0] = 0x01;
			cipher->setKey(user_key);
			
			string text;
			char f;
			ifstream fin(input[3]);
			if (!fin.is_open() || !fin.good())
			{
				cout << "ERROR! Unable to open input file\n";
				exit(-1);
			}
			else
			{
				while(fin >> noskipws >> f)
				{
					text.push_back(f);
				}
				fin.close();
			}
			cout << "textsize: " << text.size() << endl;
			cout << "text from file: '" << text << "'\n";
			
			int cst;
			if(text.size() > 16)
			{
				int add = 16 - (text.size() % 16);
				if(add != 16)
				{
					cout << "WARNING! Last text block is not 16 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			else
			{
				int add = 16 - (text.size() % 16);
				if(add != 16)
				{
					cout << "WARNING! Last text block is not 16 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			
			unsigned char* ciphertext = (unsigned char*)text.c_str();
			int const PLAINTEXTSIZE = cst;
			unsigned char plaintext[PLAINTEXTSIZE];
			
			for(int i = 0; i < cst / 16; i++)
			{
				cout << "encrypting " << ciphertext + (i * 16) << endl;
				unsigned char* plainpart = cipher->decrypt(ciphertext + (i * 16));
				for(int j = 0; j < 16; j++)
				{
					plaintext[j + (i * 16)] = (*(plainpart + j));
				}
			}
			cout << "Whole plaintext: '";
			for(int n = 0; n < PLAINTEXTSIZE; n++)
			{
				cout << plaintext[n];
				fout << plaintext[n];
			}
			cout << "'\n";
		}
		
		delete cipher;
	}
	else
	{
		CipherInterface* cipher = new DES();
		if(!(cipher->setKey((unsigned char*)input[1].c_str())))
		{
			cout << "ERROR! Unable to set key\n";
			exit(-1);
		}
		
		if (input[2] == "ENC")
		{
			string text;
			char f;
			ifstream fin(input[3]);
			if (!fin.is_open() || !fin.good())
			{
				cout << "ERROR! Unable to open input file\n";
				exit(-1);
			}
			else
			{
				while(fin >> noskipws >> f)
				{
					text.push_back(f);
				}
				fin.close();
			}
			cout << "textsize: " << text.size() << endl;
			cout << "text from file: '" << text << "'\n";
			
			int cst;
			if(text.size() > 8)
			{
				int add = 8 - (text.size() % 8);
				if(add != 8)
				{
					cout << "WARNING! Last text block is not 8 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			else
			{
				int add = 8 - (text.size() % 8);
				if(add != 8)
				{
					cout << "WARNING! Last text block is not 8 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			
			unsigned char* plaintext = (unsigned char*)text.c_str();
			int const CIPHERTEXTSIZE = cst;
			unsigned char ciphertext[CIPHERTEXTSIZE];
			
			for(int i = 0; i < cst / 8; i++)
			{
				cout << "encrypting " << plaintext + (i * 8) << endl;
				unsigned char* cipherpart = cipher->encrypt(plaintext + (i * 8));
				for(int j = 0; j < 8; j++)
				{
					ciphertext[j + (i * 8)] = (*(cipherpart + j));
				}
			}
			cout << "Whole ciphertext: '";
			for(int n = 0; n < CIPHERTEXTSIZE; n++)
			{
				cout << ciphertext[n];
				fout << ciphertext[n];
			}
			cout << "'\n";
		}
		else
		{
			string text;
			char f;
			ifstream fin(input[3]);
			if (!fin.is_open() || !fin.good())
			{
				cout << "ERROR! Unable to open input file\n";
				exit(-1);
			}
			else
			{
				while(fin >> noskipws >> f)
				{
					text.push_back(f);
				}
				fin.close();
			}
			cout << "textsize: " << text.size() << endl;
			cout << "text from file: '" << text << "'\n";
			
			int cst;
			if(text.size() > 8)
			{
				int add = 8 - (text.size() % 8);
				if(add != 8)
				{
					cout << "WARNING! Last text block is not 8 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			else
			{
				int add = 8 - (text.size() % 8);
				if(add != 8)
				{
					cout << "WARNING! Last text block is not 8 bytes. Padding with NULL\n";
					for(int i = 0; i < add; i++)
					{
						text.push_back('\0');
					}
					cout << "new text size: " << text.size() << endl;
				}
				cst = text.size();
			}
			
			unsigned char* ciphertext = (unsigned char*)text.c_str();
			int const PLAINTEXTSIZE = cst;
			unsigned char plaintext[PLAINTEXTSIZE];
			
			for(int i = 0; i < cst / 8; i++)
			{
				cout << "decrypting " << ciphertext + (i * 8) << endl;
				unsigned char* plainpart = cipher->decrypt(ciphertext + (i * 8));
				for(int j = 0; j < 8; j++)
				{
					plaintext[j + (i * 8)] = (*(plainpart + j));
				}
			}
			cout << "Whole plaintext: '";
			for(int n = 0; n < PLAINTEXTSIZE; n++)
			{
				cout << plaintext[n];
				fout << plaintext[n];
			}
			cout << "'\n";
		}

		delete cipher;
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	fout.close();
	return 0;
}
void displayHelp()
{
	cout << "Usage:\n\t./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>\n"
		<< "\n<CIPHER NAME>\n\tChoose either AES or DES\n"
		<< "<KEY>\n\tEncryption key must be a 16 digit hexadecimal number (lowercase only)\n"
		<< "<ENC/DEC>\n\tChoose only one for Encryption or Decryption respectively\n"
		<< "<INPUT FILE>\n\tFilename or path to read input\n"
		<< "<OUTPUT FILE>\n\tFilename or path to write output\n";
}

void parseArg(int argc, char** argv, string args [])
{
	if (argc < 6)
	{
		cout << "ERROR! Too few arguments!\n";
		displayHelp();
		exit(-1);
	}
	else if (argc > 6)
	{
		cout << "ERROR! Too many arguments!\n";
		displayHelp();
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			args[i] = argv[i + 1];
		}

		if (args[0] != "AES" && args[0] != "DES")
		{
			cout << "ERROR! Invalid ciphername: " << args[0] << endl;
			displayHelp();
			exit(-1);
		}

		if (args[2] != "ENC" && args[2] != "DEC")
		{
			cout << "ERROR! Invalid cryption mode: " << args[2] << endl;
			displayHelp();
			exit(-1);
		}
	}
}
