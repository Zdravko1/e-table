#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <map>
#include <vector>
#include "Cell.h"

using uint = unsigned int;

class Table
{
	private:
		uint rowCount;
		uint columnCount;
		uint longestCellLength = 0;
		std::map<uint, std::vector<Cell>> table;

		void parseRow(std::string rawRow, uint rowId);
		Cell parseCell(std::string rawCell, uint rowId, uint columnId);
		CellType parseCellType(std::string rawContent);

		// move to parser
		bool isInteger(std::string rawContent);
		bool isDecimal(std::string rawContent);

	public:
		Table() {}
		Table(uint rowCount, uint columnCount) {
			this->rowCount = rowCount;
			this->columnCount = columnCount;
		}
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

		uint getRowCount() const;
		uint getColumnCount() const;
};

#endif