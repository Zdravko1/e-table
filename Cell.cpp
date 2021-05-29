#include "Cell.h"

std::string Cell::getContent() const {
  return content;
}

CellType Cell::getType() const {
  return type;
}

uint Cell::getRowId() const {
  return rowId;
}

uint Cell::getColumnId() const {
  return columnId;
}