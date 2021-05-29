#ifndef CELL_PARSER_H
#define CELL_PARSER_H
#include "Cell.h"

class CellParser {
  private:
  public:
    CellParser() {};
    Cell parseCell(std::string rawCell, uint rowId, uint columnId);
};

#endif