#ifndef SUBTRACTION_ACTION_H
#define SUBTRACTION_ACTION_H
#include "../FormulaAction.h"

class SubtractionAction: virtual public FormulaAction {
  private:
    virtual char getAction() const override {
      return '-';
    }

    virtual string evaluate(double firstNumber, double secondNumber) override {
      return std::to_string(firstNumber - secondNumber);
    }
};

#endif