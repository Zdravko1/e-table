#include "FormulaAction.h"
#include "../CellTypeUtil.h"

// delete
#include <iostream>

string FormulaAction::execute(const string &content, std::map<uint, std::vector<Cell>> &table) {
  char action = getAction();
  uint delimiterPos = content.find(action);

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  int firstNumber = 0;
  int secondNumber = 0;

  // extract
  if ((CellTypeUtil::isInteger(firstElement)
    && CellTypeUtil::isInteger(secondElement))
   || (CellTypeUtil::isDecimal(firstElement)
    && CellTypeUtil::isDecimal(secondElement))) {
    
    firstNumber = stoi(firstElement);
    secondNumber = stoi(secondElement);
  }

  if (isCellReference(firstElement) && isCellReference(secondElement)) {
    Cell* leftCell = getCell(extractRow(firstElement), extractCol(firstElement), table);
    if (leftCell != nullptr && (leftCell->getType() == CellType::INTEGER || leftCell->getType() == CellType::DECIMAL)) {
      firstNumber = stoi(leftCell->getContent());
    }

    Cell* rightCell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (rightCell != nullptr && (rightCell->getType() == CellType::INTEGER || rightCell->getType() == CellType::DECIMAL)) {
      secondNumber = stoi(rightCell->getContent());
    }
  }

  if (isCellReference(firstElement) && (CellTypeUtil::isInteger(secondElement) || CellTypeUtil::isDecimal(secondElement))) {
    Cell* cell = getCell(extractRow(firstElement), extractCol(firstElement), table);
    if (cell != nullptr && (cell->getType() == CellType::INTEGER || cell->getType() == CellType::DECIMAL)) {
      firstNumber = stoi(cell->getContent());
    }

    secondNumber = stoi(secondElement);
  }

  if (isCellReference(secondElement) && (CellTypeUtil::isInteger(firstElement) || CellTypeUtil::isDecimal(firstElement))) {
    Cell* cell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (cell != nullptr && (cell->getType() == CellType::INTEGER || cell->getType() == CellType::DECIMAL)) {
      secondNumber = stoi(cell->getContent());
    }

    firstNumber = stoi(firstElement);
  }

  return evaluate(firstNumber, secondNumber);
}

Cell* FormulaAction::getCell(uint row, uint col, std::map<uint, std::vector<Cell>> &table) {
  std::map<uint, std::vector<Cell>>::iterator it;

  for (it = table.begin(); it != table.end(); it++) {
    if (it->first == row) {
      for (int i = 0; i < it->second.size(); i++) {
        if (it->second[i].getColumnId() == col) {
          return &it->second[i];
        }
      }
    }
  }

  return nullptr;
}

uint FormulaAction::extractRow(const string &element) {
  uint rowStartPos = element.find('R');
  uint rowEndPos = element.find('C');

  string row = element.substr(rowStartPos + 1, element.size() - rowStartPos - rowEndPos - 1);

  return std::stoi(row);
}

uint FormulaAction::extractCol(const string &element) {
  uint colStartPos = element.find('C');

  string col = element.substr(colStartPos + 1, element.size() - colStartPos - 1);

  return std::stoi(col);
}

bool FormulaAction::isCellReference(const string &element) {
  return element.find('R') != string::npos && element.find('C') != string::npos;
}