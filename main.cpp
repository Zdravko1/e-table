#include <string>
#include <iostream>
#include <fstream>
#include "Table.h"

int main()
{
	Table table;
	table.open("test.txt");
	table.print();
}