#include "pch.h"
#include "DataController.h"

#include <sstream>
#include <fstream>

#include <iostream>

#define COLUMN_NUM 2

void DataController::loadListFromCSVFile()
{
	ifstream data("actionData.csv");
	
	if (!data.is_open()) 
	{
		cerr << "file open error!" << endl;
		return;
	}

	string line;
		
	while (getline(data, line))
	{
		string comp;
		if (!line.compare("")) break;
		stringstream lineStream(line);

		string cell[COLUMN_NUM];

		int i = 0;

		for (int i = 0; i < COLUMN_NUM; i++)
		{
			getline(lineStream, cell[i], ',');
		}

		CString CCell[COLUMN_NUM];
		CCell[0] = cell[0].c_str();
		CCell[1] = cell[1].c_str();

		list.push_back(new DataRow(CCell[0], CCell[1]));

	}
}

vector<DataRow*>& DataController::getList()
{
	return this->list;
}

void DataController::SaveListToFile()
{

	ofstream myfile;

	myfile.open("actionData.csv");

	for (int i = 0; i < list.size() ; i++) 
	{
		myfile << MakeRowToOneStr(i);
	}

	myfile.close();
}

string DataController::MakeRowToOneStr(int i)
{
	string temp;
	temp = list.at(i)->getActionType() + "," + list.at(i)->getAttributes() + "\n";

	return temp;
}