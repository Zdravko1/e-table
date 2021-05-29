#include "Table.h"
#include "CellParser.h"
#include "FormulaEvaluator.h"
#include <fstream>
#include <string>
#include <iostream>

void Table::open(std::string fileName) {
  std::string line;
	std::ifstream table_file(fileName);

	if (!table_file.good())
	{
		std::cout << "Could not open file." << std::endl;
		return;
	}

  uint rowId = 1;
	while (getline(table_file, line))
	{
		parseRow(line, rowId++);
	}

  rowCount = rowId;

	table_file.close();
}

void Table::print() {
  std::map<uint, std::vector<Cell>>::iterator it;

  for (it = table.begin(); it != table.end(); it++) {
    // print the row cells and add blank cells 
    // if the row has less cells than the row with the highest cell count
    printRowCells(it->second);
    printEmptyRowCells(it->second);
    std::cout << std::endl;
  }
}

void Table::parseRow(std::string rawRow, uint rowId) {
  std::string rawCell;
  CellParser parser;
  Cell cell;

  int currentParsePos = 0;
  int columnId = 1;

  std::vector<Cell> row;

  if (rawRow.size() == 0) {
    table.insert(std::pair<uint, std::vector<Cell>>(rowId, row));
    return;
  }

  for (int i = 0; i < rawRow.size(); i++) {
    if (rawRow[i] == ',') {
      rawCell = rawRow.substr(currentParsePos, i - currentParsePos);
      cell = parser.parseCell(rawCell, rowId, columnId++);

      // refactor/extract?
      if (longestCellLength < cell.getContent().size()) {
        longestCellLength = cell.getContent().size();
      }
      // end refactor/extract

      row.push_back(cell);

      // move current position + 1 to skip the delimiter
      currentParsePos = i + 1;
    }
  }

  rawCell = rawRow.substr(currentParsePos, rawRow.size() - currentParsePos);
  cell = parser.parseCell(rawCell, rowId, columnId);

  // refactor/extract?
  if (longestCellLength < cell.getContent().size()) {
    longestCellLength = cell.getContent().size();
  }
  // end refactor/extract

  row.push_back(cell);

  table.insert(std::pair<uint, std::vector<Cell>>(rowId, row));
  columnCount = columnCount < columnId ? columnId : columnCount;
}

void Table::printRowCells(const std::vector<Cell> &rowCells) {
  FormulaEvaluator evaluator;
  for (int i = 0; i < rowCells.size(); i++) {
    string content = evaluator.evaluate(rowCells[i], table);

    if (longestCellLength > content.size()) {
      uint whiteSpaces = longestCellLength - content.size();
      content = formatCellContent(content, whiteSpaces);
    }

    std::cout << content << '|';
  }
}

void Table::printEmptyRowCells(const std::vector<Cell> &rowCells) {
  if (rowCells.size() < columnCount) {
    for (int i = 0; i < columnCount - rowCells.size(); i++) {
      string content = formatCellContent("", longestCellLength);
      std::cout << content << '|';
    }
  }
}

string Table::formatCellContent(const string &cellContent, uint whiteSpaces) {
  string content = cellContent;
  char* intervals = new char[whiteSpaces + 1];

  for (int i = 0; i < whiteSpaces; i++) {
    intervals[i] = ' ';
  }

  intervals[whiteSpaces] = '\0';
  content += intervals;

  delete[] intervals;
  return content;
}