#ifndef CELL_PARSER_H
#define CELL_PARSER_H
#include "util/Vector.h"
#include "Cell.h"

using string = std::string;
using uint = unsigned int;

class CellParser {
  private:
    string trim(const string &rawContent);
    string removeQuotes(const string &content, CellType cellType);
    bool isNumber(const string &content);
    bool isNumber(CellType cellType);
    bool isCellReference(const string &element);
    uint extractRow(const string &element);
    uint extractCol(const string &element);

  public:
    CellParser() {};
    Cell parseCell(const string &rawCell, uint rowId, uint columnId);
    CellType parseCellType(const string &rawContent);
    double parseContent(const string &rawContent, Vector<Vector<Cell>> &table);
    Cell* getCell(uint row, uint col, Vector<Vector<Cell>> &table);

    bool isInteger(const string &rawContent);
    bool isDecimal(const string &rawContent);

    /**
     * Checks if the given content starts with '='
     * And it's size is greater than 4.
     * Size 4 is the lowest possible for a formula.
     * eg. (=1+1)
     */
    bool isFormula(const string &rawContent);
    bool isString(const string &rawContent);
};

#endif