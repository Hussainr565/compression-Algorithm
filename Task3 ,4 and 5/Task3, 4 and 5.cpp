#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<conio.h>

using namespace std;


int Task3()
{
	ifstream input1;
	ifstream input2;
	ifstream para;
	ofstream comp;
	ofstream decom;

	input1.open("char.txt");
	input2.open("code.txt");
	para.open("para.txt");

	comp.open("compressedTask3.txt");
	decom.open("decompressedTask3.txt");

	if (!input1 || !input2 || !para)
	{
		cout << "Unable to open the files \n";
		input1.close();
		input2.close();
		para.close();
		comp.close();
		
		return 0;
	}
	char file1[55];
	int file2[55];
	for (int i = 0; i < 54; i++)
	{
		input1.get(file1[i]);
	}

	for (int i = 0; i < 54; i++)
	{
		input2 >> file2[i];
	}

	for (int i = 0; i < 54; i++)
	{
		comp << file1[i] << " " << file2[i] <<endl;
	}
	
	char para1[100], para2[100],lastread1;

	while (!para.eof())
	{
		int code[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			para.get(para1[i]);

			para2[i] = para1[i];
			
			if (para1[i] > 64 && para1[i] < 91)
			{
				para1[i] = para1[i] + 32;	
			}
		}

		unsigned char Compressed[3] = { 0 };

		int b = 0, z = 4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 54; j++)
			{
				if (file1[j] == para1[b])
				{
					if (para2[b] > 64 && para2[b] < 91)
					{
						code[i] = file2[53];
						i++;
						if (code[3] == file2[53])
						{  
							code[3] = 0;    
							z--;			
							para.putback(para2[z]);
						}
						if (i != 4)
						{
							code[i] = file2[j];
						}
					}
					else
					{
						code[i] = file2[j];
					}
				}
			}
			b++;
		}

		// Following Code will place the 4 6 bit codes
		// into 3 bytes

		Compressed[0] = code[0] << 2;
		Compressed[0] = (Compressed[0] | code[1] >> 4);
		comp << Compressed[0];

		Compressed[1] = (code[1] << 4);
		Compressed[1] = (Compressed[1] | code[2] >> 2);
		comp << Compressed[1];

		Compressed[2] = (code[2] << 6);
		Compressed[2] = Compressed[2] | code[3];
		comp << Compressed[2];


		// Following Code will retrieve the 4 characters
		// stored in 3 bytes using codebook and show
		// these characters on console
		unsigned char val[55];
		unsigned char C = Compressed[0] >> 2;
		int k = 0;

		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{	
					val[k] = val[k] - 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);
		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{
					val[k] = val[k] - 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));
		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{
					val[k] = val[k] - 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = ((Compressed[2] & 63));
		for (int j = 0; j < 54; j++)
		{
			if (code[3] != 0)
			{
				if (file2[j] == C)
				{
					val[k] = file1[j];
					if (lastread1 == '/')
					{
						val[k] = val[k] - 32;
						z--;
						para.putback(para2[z]);
					}
					lastread1 = val[k];
					if (val[k] != '/')
					{
						decom << val[k];
						break;
					}
				}
			}
		}
	}
}

int Task4()
{
	ifstream input1;
	ifstream input2;
	ifstream para;

	ofstream comp;
	ofstream decom;

	input1.open("input01.txt");
	input2.open("code.txt");
	para.open("para.txt");

	comp.open("compressedTask4.txt");
	decom.open("decompressedTask4.txt");

	if (!input1 || !input2 || !para)
	{
		cout << "Unable to open the files \n";
		input1.close();
		input2.close();
		para.close();
		comp.close();

		return 0;
	}
	char file1[55];
	int file2[55];
	for (int i = 0; i < 54; i++)
	{
		input1.get(file1[i]);
	}

	for (int i = 0; i < 54; i++)
	{
		input2 >> file2[i];
	}

	char para1[100], para2[100],lastread1;
	int counter = 0;
	char check[4] = { 0 }, check0[4] = { 0 };

	for (int i = 0; i < 54; i++)
	{
		comp << file1[i] << " " << file2[i] << endl;
	}

	while (!para.eof())
	{
		char check0[4] = { 0 };
		int code[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			para.get(para1[i]);

			para2[i] = para1[i];
			check0[i] = para2[i];

			if (para1[i] > 96 && para1[i] < 123)
			{		
				para1[i] = para1[i] - 32;
			}
		}

		unsigned char Compressed[3] = { 0 };

		int b = 0, z = 4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 54; j++)
			{
				if (file1[j] == para1[b])
				{
					if (para2[b] > 96 && para2[b] < 123)
					{
						code[i] = file2[53];
						i++;
						if (code[3] == file2[53])
						{  
							code[3] = 0;    
							z--;			
							para.putback(para2[z]);
						}
						if (i != 4)
						{
							code[i] = file2[j];
						}
					}
					else
					{
						code[i] = file2[j];
					}
				}
			}
			b++;
		}

		// Following Code will place the 4 6 bit codes
		// into 3 bytes

		Compressed[0] = code[0] << 2;
		Compressed[0] = (Compressed[0] | code[1] >> 4);
		comp << Compressed[0];

		Compressed[1] = (code[1] << 4);
		Compressed[1] = (Compressed[1] | code[2] >> 2);
		comp << Compressed[1];

		Compressed[2] = (code[2] << 6);
		Compressed[2] = Compressed[2] | code[3];
		comp << Compressed[2];


		// Following Code will retrieve the 4 characters
		// stored in 3 bytes using codebook and show
		// these characters on console
		unsigned char val[55];
		unsigned char C = Compressed[0] >> 2;
		int k = 0;

		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{	
					val[k] = val[k] + 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);
		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{
					val[k] = val[k] + 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));
		for (int j = 0; j < 54; j++)
		{
			if (file2[j] == C)
			{
				val[k] = file1[j];
				if (lastread1 == '/')
				{
					val[k] = val[k] + 32;
					z--;
					para.putback(para2[z]);
				}
				lastread1 = val[k];
				if (val[k] != '/')
				{
					decom << val[k];
					break;
				}
			}
		}
		k++;
		C = ((Compressed[2] & 63));
		for (int j = 0; j < 54; j++)
		{
			if (code[3] != 0)
			{

				if (file2[j] == C)
				{
					val[k] = file1[j];
					if (lastread1 == '/')
					{
						val[k] = val[k] + 32;
						z--;
						para.putback(para2[z]);
					}
					lastread1 = val[k];
					if (val[k] != '/')
					{
						decom << val[k];

						break;
					}
				}
			}
		}
	}
}

int comparisionTask3()
{
	ifstream input1;
	ifstream input2;
	ifstream para;
	ifstream decom;
	input1.open("char.txt");
	input2.open("code.txt");
	para.open("para.txt");
	decom.open("decompressedTask3.txt");

	if (!input1 || !input2 || !para || !decom)
	{
		cout << "files not available." << endl;
		return 0;
	}
	int i = 0, counter = 0;
	char org, obt;
	unsigned char original[100], obtained[100];
	while (!decom.eof())
	{
		para.get(org);
		original[i] = org;
		decom.get(obt);
		obtained[i] = obt;
		if (original[i] != obtained[i])
		{
			counter++;
		}
		i++;
	}
	cout << "Total differences between files= " << counter << endl;

	input1.close();
	input2.close();
	para.close();
	decom.close();

}

int comparisionTask4()
{
	ifstream input1;
	ifstream input2;
	ifstream para;
	ifstream decom;
	input1.open("input01.txt");
	input2.open("code.txt");
	para.open("para.txt");
	decom.open("decompressedTask4.txt");

	if (!input1 || !input2 || !para || !decom)
	{
		cout << "files not available." << endl;
		return 0;
	}
	int i = 0,counter=0;
	char org, obt; 
	unsigned char original[100], obtained[100];
	while (!decom.eof())
	{
		para.get(org);
		original[i] = org;
		decom.get(obt);
		obtained[i] = obt;
		if (original[i] != obtained[i])
		{
			counter++;
		}
		i++;
	}
	cout << "Total differences between files= " << counter << endl;

	input1.close();
	input2.close();
	para.close();
	decom.close();

}


int main()
{
		int opt;
		cout << "enter your choice:" << endl << "1. Task3" << endl << "2.Task4" << endl
			<< "3.Task3 Comparision" << endl << "4. Task4 Comparision" << endl;
		cin >> opt;

		if (opt == 1)
		{
			Task3();
		}
		if (opt == 2)
		{
			Task4();
		}
		if (opt == 3)
		{
			comparisionTask3();
		}
		if (opt == 4)
		{
			comparisionTask4();
		}
		if (opt<=0 || opt>4)
		{
			cout << "please enter correct choice." << endl;
		}
	
	return 0;
}