#ifndef FORMULA_ACTION_H
#define FORMULA_ACTION_H
#include <string>
#include "../Cell.h"
#include "../util/Vector.h"

using string = std::string;
using uint = unsigned int;

class FormulaAction {
  public:
    FormulaAction() {};
    string execute(const string &content, Vector<Vector<Cell>> &table);

  private:
    virtual string evaluate(double firstNumber, double secondNumber) = 0;
    virtual char getAction() const = 0;
    string trimTrailingZeros(const string &evaluation);
};

#endif