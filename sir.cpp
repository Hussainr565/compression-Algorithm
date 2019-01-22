#include"stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;
int T = 0;
unsigned char CodeBook[64][2];
int CodeBookSize = 64;

int LoadCodeBook(ifstream& INPUT, int show = 0)
{
	int i;
	INPUT >> CodeBookSize;
	if (show)
		cout << CodeBookSize << endl;
	if (CodeBookSize > 64)
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
	if (CodeBookSize > 64)
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
		if (C> 64 && C < 92)
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

void Pack(unsigned char Code[], unsigned char Compressed[])
{
	Compressed[0] = (Code[0] << 2 | Code[1] >> 4);
	Compressed[1] = (Code[1] << 4 | Code[2] >> 2);
	Compressed[2] = (Code[2] << 6 | Code[3]);
}

void Unpack(unsigned char Compressed[], unsigned char Data[])
{
	unsigned char C = Compressed[0] >> 2;
	Data[0] = Find(C, 1);

	C = ((Compressed[0] & 3) << 4) | (Compressed[1] >> 4);
	Data[1] = Find(C, 1);

	C = (((Compressed[1] & 15) << 2) | (Compressed[2] >> 6));
	Data[2] = Find(C, 1);

	C = ((Compressed[2] & 63));
	Data[3] = Find(C, 1);
}

int Compress(string SourceFileName, string DestinationFileName)
{
	ifstream Codes;
	Codes.open("Codes.txt");
	if (!Codes)
		return -5;

	LoadCodeBook(Codes);
	Codes.close();

	ifstream IN;
	IN.open(SourceFileName.c_str());
	if (!IN)
		return -4;

	ofstream OUT;
	OUT.open(DestinationFileName.c_str());
	if (!OUT)
	{
		IN.close();
		return -3;
	}

	WriteCodeBook(OUT);

	unsigned char Data[4] = { 0 }, Code[4] = { 0 }, Compressed[3] = { 0 };

	while (!IN.eof())
	{
		Data[0] = Data[1] = Data[2] = Data[3] = 32;

		IN.peek();
		int i;
		for (i = 0; !IN.eof() && i< 4; i++)
		{
			char C;
			IN.get(C);
			Data[i] = static_cast<unsigned char>(C);
			Code[i] = Find(Data[i], 0);
			IN.peek();
		}
		if (i != 0)
		{
			if (i < 3)
			{
				//            cout<< "\nDo some thing about it\n";
			}
			Pack(Code, Compressed);
			OUT << Compressed[0] << Compressed[1] << Compressed[2];
		}
	}

	IN.close();
	OUT.close();
	return 0;
}

int Decompress(string  SourceFileName, string DestinationFileName)
{
	ifstream IN;
	IN.open(SourceFileName.c_str());
	if (!IN)
		return -4;

	LoadCodeBook(IN);
	char tmp;
	IN.get(tmp);

	ofstream OUT;
	OUT.open(DestinationFileName.c_str());
	if (!OUT)
	{
		IN.close();
		return -3;
	}

	unsigned char Data[4] = { 0 }, Compressed[3] = { 0 };

	while (!IN.eof())
	{
		Compressed[0] = Compressed[1] = Compressed[2] = 52;
		char C;
		IN.get(C);
		Compressed[0] = static_cast<unsigned char>(C);
		IN.get(C);
		Compressed[1] = static_cast<unsigned char>(C);
		IN.get(C);
		Compressed[2] = static_cast<unsigned char>(C);

		Unpack(Compressed, Data);
		OUT << (char)Data[0] << Data[1] << Data[2] << Data[3];
	}

	IN.close();
	OUT.close();
	return 0;
}

int main()
{
	cout << endl << Compress("Text2.txt", "CText.txt") << endl;
	cout << Decompress("CText.txt", "DText.txt") << endl;
	return 0;
}
