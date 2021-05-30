#include "CellParser.h"
#include "CellTypeUtil.h"
#include "CellTypeException.h"

Cell CellParser::parseCell(string rawCell, uint rowId, uint columnId) {
  string content = rawCell;

  // trim whitespaces
  content = trim(content);
  // determine the cell type, eg. INTEGER/DECIMAL/STRING/FORMULA
  CellType cellType = parseCellType(content);

  if (cellType == CellType::UNKNOWN) {
    throw CellTypeException(rowId, columnId, rawCell);
  }

  // remove quotes in case of "Hello world!" or "\"Quotes\""
  content = removeQuotes(content, cellType);
  
  return Cell(content, cellType, rowId, columnId);
}

string CellParser::trim(string rawContent) {
  string content = rawContent;
  bool hasWhiteSpaceOnly = true;

  for (int i = 0; i < content.size(); i++) {
    if (content[i] != ' ') {
      hasWhiteSpaceOnly = false;
      break;
    }
  }

  if (!hasWhiteSpaceOnly) {
    int leftWhiteSpaceEndPos = 0;
    int rightWhiteSpaceStartPos = 0;
    // optimize
    for (int i = 0; i < content.size(); i++) {
      if (content[i] != ' ') {
        break;
      } else {
        leftWhiteSpaceEndPos++;
      }
    }

    for (int i = content.size() - 1; i > 0; i--) {
      if (content[i] != ' ') {
        break;
      } else {
        rightWhiteSpaceStartPos++;
      }
    }

    content = content.substr(leftWhiteSpaceEndPos, content.size());
    content = content.substr(0, content.size() - rightWhiteSpaceStartPos);
  }

  return content;
}

CellType CellParser::parseCellType(const string &rawContent) {
  if (CellTypeUtil::isInteger(rawContent)) {
    return CellType::INTEGER;
  }

  if (CellTypeUtil::isDecimal(rawContent)) {
    return CellType::DECIMAL;
  }

  // formula
  if (CellTypeUtil::isFormula(rawContent)) {
    return CellType::FORMULA;
  }

  if (CellTypeUtil::isString(rawContent)) {
    return CellType::STRING;
  }

  return CellType::UNKNOWN;
}

string CellParser::removeQuotes(string rawContent, CellType cellType) {
  string content = rawContent;

  if (cellType == CellType::STRING) {
    if (content.size() >= 6 && content[0] == '"' && content[content.size() - 1] == '"'
        && content[1] == '\\' && content[content.size() - 3] == '\\') {
      // remove '"\' and '\"'
      content = content.substr(1, content.size());
      content = content.substr(0, content.size() - 1);
      content = content.substr(1, content.size());
      content = content.substr(0, content.size() - 2);
      content = content + '"';
      return content;
    }
    
    if (content.size() >= 2 && content[0] == '"' && content[content.size() - 1] == '"') {
      // remove '"'
      content = content.substr(1, content.size());
      content = content.substr(0, content.size() - 1);
      return content;
    }
  }

  return content;
}