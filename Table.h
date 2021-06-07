#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <map>
#include <vector>
#include "Cell.h"
#include "util/String.h"

using uint = unsigned int;
using string = std::string;

class Table
{
	private:
		uint rowCount = 0;
		uint columnCount = 0;
		uint longestCellLength = 0;
		string file;
		std::map<uint, std::vector<Cell>> parsedTable;

		void evaluateCells();
		void parseRow(string rawRow, uint rowId);
		void printRowCells(const std::vector<Cell> &rowCells);
		void printEmptyRowCells(const std::vector<Cell> &rowCells);
		String formatCellContent(const String &cellContent, uint whiteSpaces);

	public:
		Table() {}
		void open(const string &fileName);
		void print();
		void edit(uint row, uint col, const string &content);
		void close();
		void save();
		void saveAs(const string &fileName);

		friend std::ostream& operator<<(std::ostream &os, const Table &table);
};

#endif