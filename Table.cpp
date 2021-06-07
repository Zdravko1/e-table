#include "Table.h"
#include "CellParser.h"
#include "FormulaEvaluator.h"
#include "CellTypeException.h"
#include <fstream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

void Table::open(const std::string &fileName) {
  std::string line;
	std::ifstream tableFile(fileName);

	if (!tableFile.good())
	{
		std::cout << "Could not open the given file: " << fileName << "." << std::endl;
		return;
	}

  uint rowId = 1;

  try {
    while (getline(tableFile, line)) {
      parseRow(line, rowId++);
    }
  } catch (CellTypeException e) {
    tableFile.close();
    close();
    std::cout << "Error: row " << e.getRow() << ", col " << e.getCol()
              << ", " << e.getContent() << " is unknown type." << std::endl;
    return;
  }

  rowCount = rowId;
  file = fileName;

	tableFile.close();
  evaluateCells();
}

void Table::print() {
  for (int i = 0; i < parsedTable.size(); i++) {
    // print the row cells and add blank cells 
    // if the row has less cells than the row with the highest cell count
    printRowCells(parsedTable[i]);
    printEmptyRowCells(parsedTable[i]);
    std::cout << std::endl;
  }
}

void Table::edit(uint row, uint col, const string &content) {
  CellParser parser;

  Cell* cell = parser.getCell(row, col, parsedTable);

  if (cell == nullptr) {
    std::cout << "Unknown cell on row: " << row << ", col: " << col << ".";
  }

  Cell newCell;

  try {
    newCell = parser.parseCell(content, row, col);
  } catch (CellTypeException e) {
    std::cout << "Error: row " << e.getRow() << ", col " << e.getCol() << ", " 
              << e.getContent() << " is unknown type." << std::endl;
    return;
  }

  cell->setContent(newCell.getContent());
  cell->setType(newCell.getType());
  evaluateCells();
}

void Table::save() {
  saveAs(file);
}

void Table::saveAs(const std::string &fileName) {
  std::ofstream tableFile(fileName);
  tableFile << (*this);
  std::cout << "Saved " << fileName << std::endl;
  close();
}

void Table::close() {
  parsedTable.clear();
  rowCount = 0;
  columnCount = 0;
  longestCellLength = 0;
}

std::ostream& operator<<(std::ostream &os, const Table &table) {
  for (int j = 0; j < table.parsedTable.size(); j++) {
    for (int i = 0; i < table.parsedTable[j].size(); i++) {
      os << table.parsedTable[j][i];
      if (i < table.parsedTable[j].size() - 1) {
        os << ',';
      } else {
        os << '\n';
      }
    }
  }
  return os;
}

void Table::evaluateCells() {
  FormulaEvaluator evaluator;

  for (int i = 0; i < parsedTable.size(); i++) {
    for (int j = 0; j < parsedTable[i].size(); j++) {
      Cell &cell = parsedTable[i][j];
      string evaluatedContent = evaluator.evaluate(cell, parsedTable);
      cell.setEvaluatedContent(evaluatedContent);
    }
  }
}

void Table::parseRow(std::string rawRow, uint rowId) {
  std::string rawCell;
  CellParser parser;
  Cell cell;

  int currentParsePos = 0;
  int columnId = 1;

  Vector<Cell> row;

  if (rawRow.size() == 0) {
    parsedTable.add(row);
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

      row.add(cell);

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

  row.add(cell);

  parsedTable.add(row);

  columnCount = columnCount < columnId ? columnId : columnCount;
}

void Table::printRowCells(const Vector<Cell> &rowCells) {
  FormulaEvaluator evaluator;

  for (int i = 0; i < rowCells.size(); i++) {
    String content(rowCells[i].getEvaluatedContent().c_str());

    if (longestCellLength > content.size()) {
      uint whiteSpaces = longestCellLength - content.size();
      content = formatCellContent(content, whiteSpaces);
    }

    std::cout << content << '|';
  }
}

void Table::printEmptyRowCells(const Vector<Cell> &rowCells) {
  if (rowCells.size() < columnCount) {
    for (int i = 0; i < columnCount - rowCells.size(); i++) {
      String content = "";
      content = formatCellContent(content, longestCellLength);
      std::cout << content << '|';
    }
  }
}

String Table::formatCellContent(const String &cellContent, uint whiteSpaces) {
  String content(cellContent.c_str());
  char* intervals = new char[whiteSpaces + 1];

  for (int i = 0; i < whiteSpaces; i++) {
    intervals[i] = ' ';
  }

  intervals[whiteSpaces] = '\0';
  String result(intervals);

  delete[] intervals;

  content += result;

  return content;
}