#ifndef MULTIPLICATION_ACTION_H
#define MULTIPLICATION_ACTION_H
#include "../FormulaAction.h"

class MultiplicationAction: virtual public FormulaAction {
  private:
    virtual char getAction() const override {
      return '*';
    }

    virtual string evaluate(double firstNumber, double secondNumber) override {
      return std::to_string(firstNumber * secondNumber);
    }
};

#endif