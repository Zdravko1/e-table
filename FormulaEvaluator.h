#ifndef FORMULA_CALCULATOR_H
#define FORMULA_CALCULATOR_H
#include "Cell.h"
#include "factory/FormulaType.h"
#include "util/Vector.h"
#include <string>

using string = std::string;

class FormulaEvaluator {
  private:
    string removeWhiteSpaces(const string &content);
    FormulaType determineActionType(const string &content);

  public:
    FormulaEvaluator() {};
    string evaluate(const Cell &cell, Vector<Vector<Cell>> &table);
};

#endif