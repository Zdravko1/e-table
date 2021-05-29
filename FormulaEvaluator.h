#ifndef FORMULA_CALCULATOR_H
#define FORMULA_CALCULATOR_H
#include "Cell.h"
#include <string>
#include <map>
#include <vector>

using string = std::string;

class FormulaEvaluator {
  private:
    bool isAddition(const string &content);
    bool isSubtraction(const string &content);
    bool isMultiplication(const string &content);
    bool isDivision(const string &content);
    bool isPower(const string &content);
    bool isCellReference(const string &element);
    Cell* getCell(uint row, uint col, std::map<uint, std::vector<Cell>> &table);
    uint extractRow(const string &element);
    uint extractCol(const string &element);

    string add(const string &content, std::map<uint, std::vector<Cell>> &table);
    string subtract(const string &content);
    string multiply(const string &content);
    string divide(const string &content);
    string power(const string &content);

    string removeWhiteSpaces(const string &content);

  public:
    FormulaEvaluator() {};
    string evaluate(const Cell &cell, std::map<uint, std::vector<Cell>> &table);
};

#endif