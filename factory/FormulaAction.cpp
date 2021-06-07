#include "FormulaAction.h"
#include "../CellParser.h"

string FormulaAction::execute(const string &content, std::map<uint, std::vector<Cell>> &table) {
  char action = getAction();
  uint delimiterPos = content.find(action);

  string firstElement = content.substr(0, delimiterPos);
  string secondElement = content.substr(delimiterPos + 1, content.size() - delimiterPos);

  double firstNumber = 0;
  double secondNumber = 0;

  CellParser parser;

  firstNumber = parser.parseContent(firstElement, table);
  secondNumber = parser.parseContent(secondElement, table);

  return trimTrailingZeros(evaluate(firstNumber, secondNumber));
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