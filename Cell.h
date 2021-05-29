#ifndef CELL_H
#define CELL_H
#include <string>
#include "CellType.h"

using uint = unsigned int;

class Cell
{
  private:
    std::string content;
    CellType type;
    uint rowId;
    uint columnId;

  public:
    Cell() {};
    Cell(std::string content, CellType type, uint rowId, uint columnId) {
      this->content = content;
      this->type = type;
      this->rowId = rowId;
      this->columnId = columnId;
    }

    std::string getContent() const;
    CellType getType() const;
    uint getRowId() const;
    uint getColumnId() const;

    // TODO: formula implementation.
};

#endif