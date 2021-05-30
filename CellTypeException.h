#ifndef CELL_TYPE_EXCEPTION_H
#define CELL_TYPE_EXCEPTION_H
#include <exception>
#include <string>

class CellTypeException: public std::exception {
  private:
    int row;
    int col;
    std::string content;
  public:
    CellTypeException(int row, int col, std::string content) {
      this->row = row;
      this->col = col;
      this->content = content;
    }
    int getRow() const {
      return row;
    }
    int getCol() const {
      return col;
    }
    std::string getContent() {
      return content;
    }
};

#endif