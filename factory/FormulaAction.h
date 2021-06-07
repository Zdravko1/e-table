#ifndef FORMULA_EVALUATION_ACTION_H
#define FORMULA_EVALUATION_ACTION_H
#include <string>
#include <map>
#include <vector>
#include "../Cell.h"

using string = std::string;
using uint = unsigned int;

class FormulaAction {
  public:
    FormulaAction() {};
    string execute(const string &content, std::map<uint, std::vector<Cell>> &table);

  private:
    virtual string evaluate(double firstNumber, double secondNumber) = 0;
    virtual char getAction() const = 0;
    string trimTrailingZeros(const string &evaluation);
};

#endif