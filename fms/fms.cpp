#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;
int NumOfInPuts = 1, numberOfState = 1,size_of=0;
string** transTable = NULL;
string Instring;
string FinalS, IntialS, currentState;
bool accepted = false;
void display() {
	printf("\n");
	for (int row = 0; row < numberOfState; row++) {
		for (int col = 0; col < NumOfInPuts; col++) {
			if (transTable[row][col] == "=")
				printf("\t|");
			else {
				if (transTable[row][col] == IntialS && col == 0)
					cout <<"->"<< transTable[row][col]<<"\t|";
				else if (transTable[row][col] == FinalS && col == 0)
					cout << "["<<transTable[row][col] << "]\t|";
				else
					cout << transTable[row][col] << "\t|";
			}
		}
		printf("\n");
		for (int z = 0; z < NumOfInPuts; z++)
			printf("--------");
		printf("\n");
	}
}
void getData() {
	printf("enter the number of the states: ");
	scanf("%d", &numberOfState);
	printf("enter the number of inputs: ");
	scanf("%d", &NumOfInPuts);
	numberOfState++;
	NumOfInPuts++;
	transTable = new string*[numberOfState];
	for (int g = 0; g < numberOfState; g++) {
		transTable[g] = new string[NumOfInPuts];
	}
	printf("\nenter the INITIAL state: ");
	cin >> IntialS;
	printf("enter the FINAL state: ");
	cin >> FinalS;

	printf("\n");
	if (numberOfState <= 3) {
		transTable[1][0] = IntialS;
		transTable[2][0] = FinalS;
	}
	else {
		for (int x = 1; x < numberOfState; x++) {
			printf("enter the %d STATE: ", x);
			cin >> transTable[x][0];
		}
	}
	printf("\n");
	for (int col = 1; col < NumOfInPuts; col++) {
		printf("enter the %d INPUT: ", col);
		cin >> transTable[0][col];
	}


}
void nextState() {
	printf("\n");
	for (int row = 1; row < numberOfState; row++) {
		for (int col = 1; col < NumOfInPuts; col++) {
			cout << "what is the next state of (" << transTable[row][0] << ") if the input is " << transTable[0][col]<<" ? ";
			cin >> transTable[row][col];
		}
	}
}
/*void split(string str, char seperator)
{
	int currIndex = 0, i = 0;
	int startIndex = 0, endIndex = 0;
	while (i <= str.s)
	{
		if (str[i] == seperator || i == len(str))
		{
			endIndex = i;
			string subStr = "";
			subStr.append(str, startIndex, endIndex - startIndex);
			strings[currIndex] = subStr;
			currIndex += 1;
			startIndex = endIndex + 1;
		}
		i++;
	}
}*/
string* tokenize(string s, string del = "-")
{
	int start = 0;
	int end = s.find(del);

	int a = 1;
	while (end != -1) {
		//cout << s.substr(start, end - start) << endl<<endl;
		start = end + del.size();
		end = s.find(del, start);
		a++;
	}

	string* x = new string[a+1];
	a = 0;
	start = 0;
	end = s.find(del);
	while (end != -1) {
		x[a] = s.substr(start, end - start);
		start = end + del.size();
		end = s.find(del, start);
		a++;
	}

	x[a]= s.substr(start, end - start);
	a++;
	size_of = a;
	return x;
	//cout << s.substr(start, end - start);
}
void solving() {
	printf("enter a string to test: ");
	cin >> Instring;
	cout << " your input is: " << Instring<<"\n";
	//string* input = strtok(Instring. (),"-");
	string* inputString = NULL;
	inputString=tokenize(Instring, "-");
	//cout << x[0]<<" first";
	int size =size_of;
	currentState = IntialS;
	string nextState;
	cout << "=>" << transTable[1][0];
	int temp;
	for (int row = 1; row < numberOfState; row++) {
		if (IntialS == transTable[row][0])
			temp = row;
	}
	for (int c = 0; c < size; c++) {
		accepted = false;
		Instring = inputString[c];
		for (int row = 1; row < numberOfState; row++) {
			if (transTable[row][0] == currentState) {
				for (int col = 1; col < NumOfInPuts; col++) {
					if (Instring==transTable[0][col]) {
						cout << "=" << inputString[c] << "=>" << transTable[row][col];
						nextState = transTable[row][col];
						accepted = true;
						break;
					}

				}
			}
			if (accepted) {
				//row = 0;
				currentState = nextState;
				break;
			}
		}
	}
	if (accepted && currentState == FinalS)
		printf("\n\nACCEPTED\n");
	else
		printf("\n\nNOT ACCEPTED\n");
}
void main() {
	getData();
	nextState();
	solving();
	display();
}