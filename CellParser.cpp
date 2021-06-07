#include "CellParser.h"
#include "CellTypeException.h"

Cell CellParser::parseCell(const string &rawCell, uint rowId, uint columnId) {
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

CellType CellParser::parseCellType(const string &rawContent) {
  if (isInteger(rawContent)) {
    return CellType::INTEGER;
  }

  if (isDecimal(rawContent)) {
    return CellType::DECIMAL;
  }

  // formula
  if (isFormula(rawContent)) {
    return CellType::FORMULA;
  }

  if (isString(rawContent)) {
    return CellType::STRING;
  }

  return CellType::UNKNOWN;
}

bool CellParser::isInteger(const string &rawContent) {
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

bool CellParser::isDecimal(const string &rawContent) {
  int dotPos = rawContent.find('.');
  if (dotPos == string::npos) {
    return false;
  }

  string leftSide = rawContent.substr(0, dotPos);
  string rightSide = rawContent.substr(dotPos + 1, rawContent.size() - dotPos - 1);

  return isInteger(leftSide) && isInteger(rightSide);
}

bool CellParser::isFormula(const string &rawContent) {
  return rawContent.size() > 1 && rawContent[0] == '=';
}

bool CellParser::isString(const string &rawContent) {
  return rawContent.size() > 2 && rawContent[0] == '"' && rawContent[rawContent.size() - 1] == '"';
}

string CellParser::trim(const string &rawContent) {
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

string CellParser::removeQuotes(const string &rawContent, CellType cellType) {
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