#include "FormulaEvaluator.h"
#include "CellTypeUtil.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

string FormulaEvaluator::evaluate(const Cell &cell, std::map<uint, std::vector<Cell>> &table) {
  if (cell.getType() != CellType::FORMULA) {
    return cell.getContent();
  }

  string content = cell.getContent();

  // remove '='
  content = content.substr(1, content.size() - 1);

  // remove whitespaces
  content = removeWhiteSpaces(content);

  // add formulaType
  // TODO: simple calculations first, then with cells.

  if (isAddition(content)) {
    return add(content, table);
  }

  if (isSubtraction(content)) {
    return subtract(content);
  }

  if (isMultiplication(content)) {
    return multiply(content);
  }

  if (isDivision(content)) {
    return divide(content);
  }

  if (isPower(content)) {
    return power(content);
  }

  return cell.getContent();
}

// TODO refactor common parts.

string FormulaEvaluator::add(const string &content, std::map<uint, std::vector<Cell>> &table) {
  uint delimiterPos = content.find('+');

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
    if (leftCell != nullptr) {
      firstNumber = stoi(leftCell->getContent());
    }

    Cell* rightCell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (rightCell != nullptr) {
      secondNumber = stoi(rightCell->getContent());
    }
  }

  if (isCellReference(firstElement) && (CellTypeUtil::isInteger(secondElement) || CellTypeUtil::isDecimal(secondElement))) {
    Cell* cell = getCell(extractRow(firstElement), extractCol(firstElement), table);
    if (cell != nullptr) {
      firstNumber = stoi(cell->getContent());
    }

    secondNumber = stoi(secondElement);
  }

  if (isCellReference(secondElement) && (CellTypeUtil::isInteger(firstElement) || CellTypeUtil::isDecimal(firstElement))) {
    Cell* cell = getCell(extractRow(secondElement), extractCol(secondElement), table);
    if (cell != nullptr) {
      secondNumber = stoi(cell->getContent());
    }

    firstNumber = stoi(firstElement);
  }

  return std::to_string(firstNumber + secondNumber);
}

string FormulaEvaluator::subtract(const string &content) {
  uint delimiterPos = content.find('-');

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  if (CellTypeUtil::isInteger(firstElement) && CellTypeUtil::isInteger(secondElement)) {
    int firstInteger = std::stoi(firstElement);
    int secondInteger = std::stoi(secondElement);

    return std::to_string(firstInteger - secondInteger);
  }

  return content;
}

string FormulaEvaluator::multiply(const string &content) {
  uint delimiterPos = content.find('*');

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  if (CellTypeUtil::isInteger(firstElement) && CellTypeUtil::isInteger(secondElement)) {
    int firstInteger = std::stoi(firstElement);
    int secondInteger = std::stoi(secondElement);

    return std::to_string(firstInteger * secondInteger);
  }

  return content;
}

string FormulaEvaluator::divide(const string &content) {
  uint delimiterPos = content.find('/');

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  if (CellTypeUtil::isInteger(firstElement) && CellTypeUtil::isInteger(secondElement)) {
    int firstInteger = std::stoi(firstElement);
    int secondInteger = std::stoi(secondElement);

    return std::to_string(firstInteger / secondInteger);
  }

  return content;
}

string FormulaEvaluator::power(const string &content) {
  uint delimiterPos = content.find('^');

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  if (CellTypeUtil::isInteger(firstElement) && CellTypeUtil::isInteger(secondElement)) {
    int firstInteger = std::stoi(firstElement);
    int secondInteger = std::stoi(secondElement);

    return std::to_string(pow(firstInteger, secondInteger));
  }

  return content;
}

string FormulaEvaluator::removeWhiteSpaces(const string &content) {
  string result;
  int whiteSpaceCount = 0;

  for (int i = 0; i < content.size(); i++) {
    if (content[i] == ' ') {
      whiteSpaceCount++;
    }
  }

  char* chars = new char[content.size() - whiteSpaceCount + 1];
  int charsIdx = 0;

  for (int i = 0; i < content.size(); i++) {
    if (content[i] != ' ') {
      chars[charsIdx] = content[i];
      charsIdx++;
    }
  }

  chars[content.size() - whiteSpaceCount] = '\0';

  result = chars;

  delete chars;
  return result;
}

Cell* FormulaEvaluator::getCell(uint row, uint col, std::map<uint, std::vector<Cell>> &table) {
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

uint FormulaEvaluator::extractRow(const string &element) {
  uint rowStartPos = element.find('R');
  uint rowEndPos = element.find('C');

  string row = element.substr(rowStartPos + 1, element.size() - rowStartPos - rowEndPos - 1);

  return std::stoi(row);
}

uint FormulaEvaluator::extractCol(const string &element) {
  uint colStartPos = element.find('C');

  string col = element.substr(colStartPos + 1, element.size() - colStartPos - 1);

  return std::stoi(col);
}

bool FormulaEvaluator::isCellReference(const string &element) {
  return element.find('R') != string::npos && element.find('C') != string::npos;
}

bool FormulaEvaluator::isAddition(const string &content) {
  return content.find('+') != string::npos;
}

bool FormulaEvaluator::isSubtraction(const string &content) {
  return content.find('-') != string::npos;
}

bool FormulaEvaluator::isMultiplication(const string &content) {
  return content.find('*') != string::npos;
}

bool FormulaEvaluator::isDivision(const string &content) {
  return content.find('/') != string::npos;
}

bool FormulaEvaluator::isPower(const string &content) {
  return content.find('^') != string::npos;
}