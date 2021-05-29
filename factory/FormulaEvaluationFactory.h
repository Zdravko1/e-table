#ifndef FORMULA_EVALUATION_FACTORY_H
#define FORMULA_EVALUATION_FACTORY_H
#include "FormulaAction.h"
#include "FormulaType.h"
#include "actions/AdditionAction.h"
#include "actions/SubtractionAction.h"
#include "actions/MultiplicationAction.h"
#include "actions/DivisionAction.h"
#include "actions/PowerAction.h"

class FormulaEvaluationFactory {
  public:
    FormulaEvaluationFactory() {
      additionAction = new AdditionAction();
      subtractionAction = new SubtractionAction();
      multiplicationAction = new MultiplicationAction();
      divisionAction = new DivisionAction();
      powerAction = new PowerAction();
    }
    ~FormulaEvaluationFactory() {
      delete additionAction;
      delete subtractionAction;
      delete multiplicationAction;
      delete divisionAction;
      delete powerAction;
    }
    FormulaAction* getAction(FormulaType type) {
      switch(type) {
        case FormulaType::ADDITION:
          return new AdditionAction();
        case FormulaType::SUBTRACTION:
          return new SubtractionAction();
        case FormulaType::MULTIPLICATION:
          return new MultiplicationAction();
        case FormulaType::DIVISION:
          return new DivisionAction();
        case FormulaType::POWER:
          return new PowerAction();
        default: return nullptr;
      }
    }
  private:
    AdditionAction* additionAction;
    SubtractionAction* subtractionAction;
    MultiplicationAction* multiplicationAction;
    DivisionAction* divisionAction;
    PowerAction* powerAction;
};

#endif