#pragma once

#include"DataRow.h"
#include <vector>
#include <string>

using namespace std;

class DataController
{

private:
	vector<DataRow*> list;

public:
	vector<DataRow*>& getList();
	void loadListFromCSVFile();
	void SaveListToFile();
	string MakeRowToOneStr(int i);
};

