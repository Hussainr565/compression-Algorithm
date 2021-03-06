#include"stdafx.h"
#include <iostream>
#include <fstream>
#include<conio.h>

using namespace std;
int T = 0;
unsigned char CodeBook[54][2];
int CodeBookSize = 54;
ifstream INPUT;
ofstream OUTPUT;

int LoadCodeBook(ifstream& INPUT, int show = 0)
{
	int i;
	INPUT >> CodeBookSize;
	if (show)
		cout << CodeBookSize << endl;
	if (CodeBookSize > 54)
		return -1;

	for (i = 0; !INPUT.eof() && i<CodeBookSize; i++)
	{
		int N[2];
		INPUT >> N[0] >> N[1];
		if (show)
			cout << N[0] << "\t" << N[1] << endl;
		CodeBook[i][0] = static_cast<unsigned char>(N[0]);

		CodeBook[i][1] = static_cast<unsigned char>(N[1]);

	}
	if (i < CodeBookSize)
		return -2;

	return 0;
}

int WriteCodeBook(ofstream& OUTPUT)
{
	if (CodeBookSize > 54)
		return -1;
	OUTPUT << CodeBookSize;

	for (int i = 0; i<CodeBookSize; i++)
	{
		OUTPUT << " " << static_cast<int>(CodeBook[i][0]) << " " << static_cast<int> (CodeBook[i][1]);
	}
	OUTPUT << endl;
	return 0;
}

unsigned char Find(unsigned char C, int SearhIndex)
{
	if (SearhIndex == 0)
	{
		if (C> 64 && C < 91)
			C += 32;
	}
	for (int j = 0; j < CodeBookSize; j++)
		if (CodeBook[j][SearhIndex] == C)
			return CodeBook[j][1 - SearhIndex];

	//cout<<"\n NOT FOUND "<< (int)C<<endl;
	if (SearhIndex == 0)
		return 52;
	return 32;
}

int Compress()
{
	ifstream Codes;
	Codes.open("Codes.txt");
	if (!Codes)
		return -5;

	LoadCodeBook(Codes);
	Codes.close();

	ifstream IN;
	IN.open("parafile.txt");
	if (!IN)
		return -4;

	ofstream OUT,decomp;
	OUT.open("comp.txt");
	decomp.open("decompressed.txt");

	if (!OUT)
	{
		IN.close();
		return -3;
	}
	
	WriteCodeBook(OUT);

	unsigned char Data[4] = { 0 }, Compressed[3] = { 0 };
	
	while (!IN.eof())
	{
		int Code[4] = { 0 };

		char check[4] = { 0 };
		for (int i = 0; i< 4; i++)
		{

			IN.get(check[i]);
			Data[i] = check[i];
			if (check[i]> 64 && check[i] < 91)
				check[i] += 32;
		
		}
		
		int b = 0, c = 3;
		for (int i = 0; i< 4; i++)
		{
			if (Data[b] > 64 && Data[b] < 91)
			{
				Code[i] = 50;
				i++;
				IN.putback(Data[c--]);
			
				if (i != 4)
					Code[i] = Find(check[b], 0);
			}
			else 
			{
				Code[i] = Find(check[b], 0);
			}
			b++;
		}
		
		Compressed[0] = (Code[0] << 2 | Code[1] >> 4);
		Compressed[1] = (Code[1] << 4 | Code[2] >> 2);
		Compressed[2] = (Code[2] << 6 | Code[3]);
		OUT << Compressed[0] << Compressed[1] << Compressed[2];

		unsigned char samp[4];
		unsigned char C = Compressed[0] >> 2 ;
		samp[0] = Find(C,1);
		C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);
		samp[1] = Find(C, 1);
		C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));
		samp[2] = Find(C, 1);
		C = ((Compressed[2] & 63));
		samp[3] = Find(C, 1);
		
		for (int k = 0; k < 4; k++)
		{
			if (samp[k] != ']')
			{
				decomp << samp[k];
			}
			if (samp[k] == ']')
			{
				k++;
				if (k < 4)
				{
					samp[k] -= 32;
					decomp << samp[k];
				}
			}
		}
		samp[0] = samp[1] = samp[2] = samp[3] = 0;	
	}
	IN.close();
	OUT.close();
	decomp.close();
	return 0;
}


int main()
{
	INPUT.open("input.txt");

	if (!INPUT)
	{
		cout << "Code File Error";
		return -55;
	}
	LoadCodeBook(INPUT);
	Compress();
	
	INPUT.close();
	
	return 0;
}
