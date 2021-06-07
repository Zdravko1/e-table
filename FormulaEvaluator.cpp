#include "FormulaEvaluator.h"
#include "factory/FormulaEvaluationFactory.h"

string FormulaEvaluator::evaluate(const Cell &cell, std::map<uint, std::vector<Cell>> &table) {
  if (cell.getType() != CellType::FORMULA) {
    return cell.getContent();
  }

  string content = cell.getContent();

  // remove '='
  content = content.substr(1, content.size() - 1);

  // remove whitespaces
  content = removeWhiteSpaces(content);

  FormulaEvaluationFactory factory;

  FormulaType formulaType = determineActionType(content);

  if (formulaType != FormulaType::NONE)
    return factory.getAction(formulaType)->execute(content, table);
  else
    return cell.getContent();
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

  delete[] chars;
  return result;
}

FormulaType FormulaEvaluator::determineActionType(const string &content) {
  if (content.find('+') != string::npos) {
    return FormulaType::ADDITION;
  }
  if (content.find('-') != string::npos) {
    return FormulaType::SUBTRACTION;
  }
  if (content.find('*') != string::npos) {
    return FormulaType::MULTIPLICATION;
  }
  if (content.find('/') != string::npos) {
    return FormulaType::DIVISION;
  }
  if (content.find('^') != string::npos) {
    return FormulaType::POWER;
  }

  return FormulaType::NONE;
}