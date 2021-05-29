#ifndef POWER_ACTION_H
#define POWER_ACTION_H
#include "../FormulaAction.h"
#include <cmath>

class PowerAction: virtual public FormulaAction {
  private:
    virtual char getAction() const override {
      return '^';
    }

    virtual string evaluate(int firstNumber, int secondNumber) override {
      return std::to_string(pow(firstNumber, secondNumber));
    }
};

#endif