#ifndef FORMULA_CALCULATOR_H
#define FORMULA_CALCULATOR_H
#include "Cell.h"
#include "factory/FormulaType.h"
#include <string>
#include <map>
#include <vector>

using string = std::string;

class FormulaEvaluator {
  private:
    string removeWhiteSpaces(const string &content);
    FormulaType determineActionType(const string &content);

  public:
    FormulaEvaluator() {};
    string evaluate(const Cell &cell, std::map<uint, std::vector<Cell>> &table);
};

#endif