#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }


REMStatement::REMStatement(std::string source)
  : Statement(std::move(source)) {}
void REMStatement::execute(VarState& state, Program& program) const {}  //无操作。

LETStatement::LETStatement(std::string source, std::string var, Expression* expr)
  : Statement(std::move(source)), var_(std::move(var)), expr_(expr) {}
LETStatement::~LETStatement() { delete expr_; }

void LETStatement::execute(VarState& state, Program& program) const {
  int value = expr_->evaluate(state);
  state.setValue(var_, value);
}

PRINTStatement::PRINTStatement(std::string source, Expression* expr)
  : Statement(std::move(source)), expr_(expr) {}
PRINTStatement::~PRINTStatement() { delete expr_; }

void PRINTStatement::execute(VarState& state, Program& program) const {
  int value = expr_->evaluate(state);
  std::cout << value << std::endl;
}

INPUTStatement::INPUTStatement(std::string source, std::string var)
  : Statement(std::move(source)), var_(std::move(var)) {}

void INPUTStatement::execute(VarState& state, Program& program) const {
  std::cout << "?";
  int value;
  std::cin >> value;
  state.setValue(var_, value);
}

ENDStatement::ENDStatement(std::string source)
  : Statement(std::move(source)) {}

void ENDStatement::execute(VarState& state, Program& program) const {
  program.programEnd();
}

GOTOStatement::GOTOStatement(std::string source, int line)
  : Statement(std::move(source)), line_(line) {}

void GOTOStatement::execute(VarState& state, Program& program) const {
  program.changePC(line_);
}

IFStatement::IFStatement(std::string source, Expression* expr1, char op,
  Expression* expr2, int line)
  : Statement(std::move(source)), expr1_(expr1), expr2_(expr2), op_(op), line_(line) {}
IFStatement::~IFStatement() {
  delete expr1_;
  delete expr2_;
}

void IFStatement::execute(VarState& state, Program& program) const {
  int value1 = expr1_->evaluate(state);
  int value2 = expr2_->evaluate(state);
  bool judge = false;
  switch (op_) {
    case '=':
      judge = (value1 == value2);
      break;
    case '<':
      judge = (value1 < value2);
      break;
    case '>':
      judge = (value1 > value2);
      break;
  }
  if (judge) {
    program.changePC(line_);
  }
}
