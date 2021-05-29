#ifndef DIVISION_ACTION_H
#define DIVISION_ACTION_H
#include "../FormulaAction.h"

class DivisionAction: virtual public FormulaAction {
  private:
    virtual char getAction() const override {
      return '/';
    }

    virtual string evaluate(int firstNumber, int secondNumber) override {
      if (secondNumber == 0) {
        return "ERROR";
      }
      return std::to_string(firstNumber / secondNumber);
    }
};

#endif