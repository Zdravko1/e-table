#ifndef CELL_PARSER_H
#define CELL_PARSER_H
#include "Cell.h"

using string = std::string;

class CellParser {
  private:
    string trim(const string &rawContent);
    string removeQuotes(const string &content, CellType cellType);
  public:
    CellParser() {};
    Cell parseCell(const string &rawCell, uint rowId, uint columnId);
    CellType parseCellType(const string &rawContent);
    bool isInteger(const string &rawContent);
    bool isDecimal(const string &rawContent);
    bool isFormula(const string &rawContent);
    bool isString(const string &rawContent);
};

#endif