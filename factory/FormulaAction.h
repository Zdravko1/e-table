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

    bool isCellReference(const string &element);
    Cell* getCell(uint row, uint col, std::map<uint, std::vector<Cell>> &table);
    uint extractRow(const string &element);
    uint extractCol(const string &element);
    string trimTrailingZeros(const string &evaluation);
};

#endif