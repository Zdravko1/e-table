#ifndef CELL_TYPE_UTIL_H
#define CELL_TYPE_UTIL_H
#include <string>

using string = std::string;

class CellTypeUtil {
  public:
    static bool isInteger(const string &rawContent) {
      int idx = 0;
      if (rawContent[idx] == '+' || rawContent[idx] == '-') {
        idx++;
      }

      for (idx; idx < rawContent.size(); idx++) {
        if (rawContent[idx] < '0' || rawContent[idx] > '9') {
          return false;
        }
      }

      return true;
    }

    static bool isDecimal(const string &rawContent) {
      string content = rawContent;

      if (content[0] == '+' || content[0] == '-') {
        content = content.substr(0, 1);
      }

      int dotPos = rawContent.find('.');
      if (dotPos == string::npos) {
        return false;
      }

      string leftSide = rawContent.substr(0, dotPos);
      string rightSide = rawContent.substr(dotPos + 1, rawContent.size() - dotPos - 1);

      return isInteger(leftSide) && isInteger(rightSide);
    }

    static bool isFormula(const string &rawContent) {
      return rawContent.size() > 1 && rawContent[0] == '=';
    }
};

#endif