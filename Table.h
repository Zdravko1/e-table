#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <map>
#include <vector>
#include "Cell.h"

using uint = unsigned int;
using string = std::string;

class Table
{
	private:
		uint rowCount;
		uint columnCount;
		uint longestCellLength = 0;
		std::map<uint, std::vector<Cell>> table;

		void parseRow(string rawRow, uint rowId);
		void printRowCells(const std::vector<Cell> &rowCells);
		void printEmptyRowCells(const std::vector<Cell> &rowCells);
		string formatCellContent(const string &cellContent, uint whiteSpaces);

	public:
		Table() {}
		void open(std::string fileName);
		void print();
		// TODO: implement
		void edit(/*row col content?*/);
		void close();
		void save();
		void saveAs(std::string fileName);
		void help();
		void exit();
		// end implement
};

#endif