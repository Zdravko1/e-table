#include "Table.h"
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
  // TODO: refactor
  int currentRow = 1;
  int currentColumn = 1;
  std::map<uint, std::vector<Cell>>::iterator it;
  for (it = table.begin(); it != table.end(); it++) {
    for (int i = 0; i < it->second.size(); i++) {
      std::cout << it->second[i].getContent();

      // extract
      if (longestCellLength > it->second[i].getContent().size()) {
        uint arrSize = longestCellLength - it->second[i].getContent().size();
        char* intervals = new char[arrSize + 1];
        for (int i = 0; i < arrSize; i++) {
          intervals[i] = ' ';
        }
        intervals[arrSize] = '\0';
        std::cout << intervals;
        delete intervals;
      }

      // end extract, maybe next line aswell

      std::cout << '|';
    }

    // extract - add remaining columns
    if (it->second.size() < columnCount) {
      for (int i = 0; i < columnCount - it->second.size(); i++) {
        char* intervals = new char[longestCellLength + 1];
        for (int i = 0; i < longestCellLength; i++) {
          intervals[i] = ' ';
        }
        intervals[longestCellLength] = '\0';
        std::cout << intervals << '|';
        delete intervals;
      }
    }

    // end extract, maybe next line aswell

    std::cout << std::endl;
  }
}

void Table::parseRow(std::string rawRow, uint rowId) {
  std::string rawCell;
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
      cell = parseCell(rawCell, rowId, columnId++);

      row.push_back(cell);

      // move current position + 1 to skip the delimiter
      currentParsePos = i + 1;
    }
  }

  rawCell = rawRow.substr(currentParsePos, rawRow.size() - currentParsePos);
  cell = parseCell(rawCell, rowId, columnId);
  row.push_back(cell);

  table.insert(std::pair<uint, std::vector<Cell>>(rowId, row));
  columnCount = columnCount < columnId ? columnId : columnCount;
}

Cell Table::parseCell(std::string rawCell, uint rowId, uint columnId) {
  std::string content = rawCell;

  // TODO: trim whitespaces if there is content != whitespace
  // extract
  bool hasWhiteSpaceOnly = true;
  for (int i = 0; i < content.size(); i++) {
    if (content[i] != ' ') {
      hasWhiteSpaceOnly = false;
      break;
    }
  }

  if (!hasWhiteSpaceOnly) {
    int leftWhiteSpaceEndPos = 0;
    int rightWhiteSpaceStartPos = 0;
    // optimize
    for (int i = 0; i < content.size(); i++) {
      if (content[i] != ' ') {
        break;
      } else {
        leftWhiteSpaceEndPos++;
      }
    }

    for (int i = content.size() - 1; i > 0; i--) {
      if (content[i] != ' ') {
        break;
      } else {
        rightWhiteSpaceStartPos++;
      }
    }

    content = content.substr(leftWhiteSpaceEndPos, content.size());
    content = content.substr(0, content.size() - rightWhiteSpaceStartPos);
  }
  // end extract

  if (longestCellLength < content.size()) {
    longestCellLength = content.size();
  }

  CellType cellType = parseCellType(rawCell);

  // extract/refactor
  if (content.size() >= 6 && content[0] == '"' && content[content.size() - 1] == '"'
      && content[1] == '\\' && content[content.size() - 3] == '\\') {
    // remove '"\' and '\"'
    content = content.substr(1, content.size());
    content = content.substr(0, content.size() - 1);
    content = content.substr(1, content.size());
    content = content.substr(0, content.size() - 2);
    content = content + '"';
    return Cell(content, cellType, rowId, columnId);
  }
  
  if (content.size() >= 2 && content[0] == '"' && content[content.size() - 1] == '"') {
    // remove '"'
    content = content.substr(1, content.size());
    content = content.substr(0, content.size() - 1);
  }
  // end extract/refactor
  
  return Cell(content, cellType, rowId, columnId);
}

CellType Table::parseCellType(std::string rawContent) {
  if (isInteger(rawContent)) {
    return CellType::INTEGER;
  }

  if (isDecimal(rawContent)) {
    return CellType::DECIMAL;
  }

  // formula
  if (rawContent[0] == '=') {
    return CellType::FORMULA;
  }

  return CellType::STRING;
}

bool Table::isInteger(std::string rawContent) {
  int idx = 0;
  if (rawContent[idx] == '+' || rawContent[idx] == '-') {
    idx++;
  }

  for (idx; idx < rawContent.size(); idx++) {
    if (rawContent[idx] < '0' || rawContent[idx] > '9') {
      return false;
    }
  }

  return true;
}

bool Table::isDecimal(std::string rawContent) {
  std::string content = rawContent;

  if (content[0] == '+' || content[0] == '-') {
    content = content.substr(0, 1);
  }

  int dotPos = rawContent.find('.');
  if (dotPos == std::string::npos) {
    return false;
  }

  std::string leftSide = rawContent.substr(0, dotPos);
  std::string rightSide = rawContent.substr(dotPos + 1, rawContent.size() - dotPos - 1);

  return isInteger(leftSide) && isInteger(rightSide);
}

uint Table::getRowCount() const {
  return rowCount;
}

uint Table::getColumnCount() const {
  return columnCount;
}