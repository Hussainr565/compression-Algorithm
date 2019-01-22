#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<conio.h>

using namespace std;

int compression()
{
	ifstream input1;
	ifstream input2;
	ifstream para;
	ofstream comp;
	ofstream comp1;

	input1.open("char.txt");
	input2.open("code.txt");
	para.open("para.txt");
	comp.open("check.txt");
	comp1.open("compressed.txt");
	if (!input1 || !input2 || !para)
	{
		cout << "Unable to open the files \n";
		return 0;
	}
	char file1[54];
	
	for (int i = 0; i < 53; i++)
	{
		input1.get(file1[i]);
	}
	int file2[54];

	for (int i = 0; i < 53; i++)
	{
		input2 >> file2[i];
	}
	
	for (int i = 0; i < 53; i++)
	{
		comp1 << file1[i] << " " << file2[i] << "\t"<<endl;
	}
	char para1[100];

	while (!para.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			para.get(para1[i]);

			if (para1[i] > 64 && para1[i] < 91)
			{
				para1[i] = para1[i] + 32;
			}
		}
		unsigned char Compressed[3] = { 0 };
		int code[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				if (file1[j] == para1[i])
				{
					code[i] = file2[j];
				}
			}
		}
		// Following Code will place the 4 6 bit codes
		// into 3 bytes

		Compressed[0] = code[0] << 2;
		Compressed[0] = (Compressed[0] | code[1] >> 4);

		comp << Compressed[0];
		comp1 << Compressed[0];
		Compressed[1] = (code[1] << 4);
		Compressed[1] = (Compressed[1] | code[2] >> 2);

		comp << Compressed[1];
		comp1 << Compressed[1];
		Compressed[2] = (code[2] << 6);
		Compressed[2] = Compressed[2] | code[3];

		comp << Compressed[2];
		comp1 << Compressed[2];
	}

	input1.close();
	input2.close();
	para.close();
	comp.close();
	comp1.close();
}

int decompressionTask1()
{
	ifstream input1;
	ifstream input2;
	ifstream comp;
	ofstream decom;

	input1.open("char.txt");
	input2.open("code.txt");
	comp.open("check.txt");
	decom.open("decompressedTask1.txt");

	if (!input1 || !input2 || !comp)
	{
		cout << "Unable to open the files \n";
		return 0;
	}
	char file1[54];
	for (int i = 0; i < 53; i++)
	{
		input1.get(file1[i]);
	}
	int file2[54];
	
	for (int i = 0; i < 53; i++)
	{
		input2 >> file2[i];
	}
	unsigned char Compressed[3];
	char compressed;
	while (!comp.eof())
	{
		for (int i = 0; i < 3; i++)
		{
			comp.get(compressed);
			Compressed[i] = compressed;
		}
		unsigned char val[53];

		unsigned char C = Compressed[0] >> 2;
		int k = 0;
		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				decom << val[k];
				break;
			}
		}
		k++;

		C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				decom << val[k];
				break;
			}
		}
		k++;

		C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				decom << val[k];
				break;
			}
		}
		k++;

		C = ((Compressed[2] & 63));

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				decom << val[k];
				break;
			}
		}
	}

	input1.close();
	input2.close();
	comp.close();
	decom.close();

}

int decompressionTask2()
{
	ifstream input1;
	ifstream input2;
	ifstream comp;
	ofstream decom;

	input1.open("char.txt");
	input2.open("code.txt");
	comp.open("check.txt");
	decom.open("decompressedTask2.txt");

	if (!input1 || !input2 || !comp)
	{
		cout << "Unable to open the files \n";
		return 0;
	}
	char file1[54];
	for (int i = 0; i < 53; i++)
	{
		input1.get(file1[i]);
	}

	int file2[54];
	for (int i = 0; i < 53; i++)
	{
		input2 >> file2[i];
	}
	char lastread1 = ' ', lastread2 = '.';
	unsigned char Compressed[3];
	char compressed;
	
	while (!comp.eof())
	{
		for (int i = 0; i < 3; i++)
		{
			comp.get(compressed);
			Compressed[i] = compressed;
		}
		unsigned char val[53];
		
		unsigned char C = Compressed[0] >> 2;
		int k = 0;
		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread2 == '.' && lastread1 == ' ')
				{	
					val[k] = val[k] - 32;
				}
				lastread2 = lastread1;
				lastread1 = val[k];
				decom << val[k];
				break;
			}
		}
		k++;

		C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread2 == '.' && lastread1 == ' ')
				{	
					val[k] = val[k] - 32;
				}
				lastread2 = lastread1;
				lastread1 = val[k];
				decom << val[k];
				break;
			}
		}
		k++;

		C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread2 == '.' && lastread1 == ' ')
				{
					val[k] = val[k] - 32;
				}
				lastread2 = lastread1;
				lastread1 = val[k];
				decom << val[k];
				break;
			}
		}
		k++;

		C = ((Compressed[2] & 63));

		for (int j = 0; j < 53; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread2 == '.' && lastread1 == ' ')
				{
					val[k] = val[k] - 32;
				}
				lastread2 = lastread1;
				lastread1 = val[k];
				decom << val[k];
				break;
			}
		}
	}

	input1.close();
	input2.close();
	comp.close();
	decom.close();
}

int main()
{
	int choice;
	cout << "enter your choice:" << endl << "1. Compression" << endl << "2. Decompression Task1" << endl
		<<"3. Decompression Task2"<<endl;
	cin >> choice;
	if (choice == 1)
	{
		compression();
	}
	if (choice == 2)
	{
		decompressionTask1();
	}
	if (choice == 3)
	{
		decompressionTask2();
	}

	return 0;
}