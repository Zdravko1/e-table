#ifndef TABLE_H
#define TABLE_H
#include <string>
#include "Cell.h"
#include "util/Vector.h"
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
		Vector<Vector<Cell>> parsedTable;

		void evaluateCells();
		void parseRow(string rawRow, uint rowId);
		void printRowCells(const Vector<Cell> &rowCells);
		void printEmptyRowCells(const Vector<Cell> &rowCells);
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