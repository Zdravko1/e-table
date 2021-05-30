#include "Cell.h"

std::ostream& operator<<(std::ostream& os, const Cell &cell) {
  os << cell.getEvaluatedContent();
  return os;
}

std::string Cell::getContent() const {
  return content;
}

std::string Cell::getEvaluatedContent() const {
  return evaluatedContent;
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

void Cell::setContent(const std::string &content) {
  this->content = content;
}

void Cell::setType(CellType type) {
  this->type = type;
}

void Cell::setEvaluatedContent(const std::string &content) {
  this->evaluatedContent = content;
}