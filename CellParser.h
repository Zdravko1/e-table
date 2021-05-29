#ifndef CELL_PARSER_H
#define CELL_PARSER_H
#include "Cell.h"

using string = std::string;

class CellParser {
  private:
    string trim(string rawContent);
    CellType parseCellType(string rawContent);
    string removeQuotes(string content, CellType cellType);
  public:
    CellParser() {};
    Cell parseCell(string rawCell, uint rowId, uint columnId);
};

#endif