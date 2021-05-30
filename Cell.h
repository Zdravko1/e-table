#ifndef CELL_H
#define CELL_H
#include <string>
#include "CellType.h"

using uint = unsigned int;

class Cell
{
  private:
    std::string content;
    std::string evaluatedContent;
    CellType type;
    uint rowId;
    uint columnId;

  public:
    Cell() {};
    Cell(std::string &content, CellType type, uint rowId, uint columnId) {
      this->content = content;
      this->type = type;
      this->rowId = rowId;
      this->columnId = columnId;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cell &cell);

    std::string getContent() const;
    std::string getEvaluatedContent() const;
    CellType getType() const;
    uint getRowId() const;
    uint getColumnId() const;

    void setContent(const std::string &content);
    void setType(CellType type);
    void setEvaluatedContent(const std::string &content);
};

#endif