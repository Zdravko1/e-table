#include "FormulaAction.h"
#include "../CellParser.h"

// delete
#include <iostream>

// refactor...
string FormulaAction::execute(const string &content, std::map<uint, std::vector<Cell>> &table) {
  char action = getAction();
  uint delimiterPos = content.find(action);

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  double firstNumber = 0;
  double secondNumber = 0;

  CellParser parser;

  // extract
  if ((parser.isInteger(firstElement) || parser.isDecimal(firstElement))
   && (parser.isInteger(secondElement) || parser.isDecimal(secondElement))) {
    
    if (parser.isInteger(firstElement)) {
      firstNumber = stoi(firstElement);
    } else {
      firstNumber = stod(firstElement);
    }

    if (parser.isInteger(secondElement)) {
      secondNumber = stoi(secondElement);
    } else {
      secondNumber = stod(secondElement);
    }
  }

  if (isCellReference(firstElement) && isCellReference(secondElement)) {
    Cell* leftCell = getCell(extractRow(firstElement), extractCol(firstElement), table);
    if (leftCell != nullptr && (leftCell->getType() == CellType::INTEGER || leftCell->getType() == CellType::DECIMAL)) {
      if (leftCell->getType() == CellType::INTEGER) {
        firstNumber = stoi(leftCell->getContent());
      } else {
        firstNumber = stod(leftCell->getContent());
      }
    }

    Cell* rightCell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (rightCell != nullptr && (rightCell->getType() == CellType::INTEGER || rightCell->getType() == CellType::DECIMAL)) {
      if (rightCell->getType() == CellType::INTEGER) {
        secondNumber = stoi(rightCell->getContent());
      } else {
        secondNumber = stod(rightCell->getContent());
      }
    }
  }

  if (isCellReference(firstElement) && (parser.isInteger(secondElement) || parser.isDecimal(secondElement))) {
    Cell* cell = getCell(extractRow(firstElement), extractCol(firstElement), table);

    if (cell != nullptr && (cell->getType() == CellType::INTEGER || cell->getType() == CellType::DECIMAL)) {
      if (cell->getType() == CellType::INTEGER) {
        firstNumber = stoi(cell->getContent());
      } else {
        firstNumber = stod(cell->getContent());
      }
    }

    if (parser.isInteger(secondElement)) {
      secondNumber = stoi(secondElement);
    } else {
      secondNumber = stod(secondElement);
    }
  }

  if (isCellReference(secondElement) && (parser.isInteger(firstElement) || parser.isDecimal(firstElement))) {
    Cell* cell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (cell != nullptr && (cell->getType() == CellType::INTEGER || cell->getType() == CellType::DECIMAL)) {
      if (cell->getType() == CellType::INTEGER) {
        secondNumber = stoi(cell->getContent());
      } else {
        secondNumber = stod(cell->getContent());
      }
    }

    if (parser.isInteger(firstElement)) {
      firstNumber = stoi(firstElement);
    } else {
      firstNumber = stod(firstElement);
    }
  }

  return trimTrailingZeros(evaluate(firstNumber, secondNumber));
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

string FormulaAction::trimTrailingZeros(const string &evaluation) {
  int trailingZeroCount = 0;
  bool isDecimal = false;

  for (int i = evaluation.size() - 1; i > 0; i--) {
    if (evaluation[i] != '0') {
      isDecimal = evaluation[i] == '.'; 
      break;
    }
    trailingZeroCount++;
  }

  string result = evaluation.substr(0, evaluation.size() - trailingZeroCount);

  if (isDecimal) {
    result = result.substr(0, result.size() - 1);
  }

  return result;
}