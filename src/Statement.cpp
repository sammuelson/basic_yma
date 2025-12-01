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

// TODO: Imply interfaces declared in the Statement.hpp.

// 一般指令

REMStatement::REMStatement(std::string source)
  : Statement(std::move(source)) {}
void execute(VarState& state, Program& program) {}  //无操作。

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

//todo
void ENDStatement::execute(VarState& state, Program& program) const {
  // program.endExecution();
}

GOTOStatement::GOTOStatement(std::string source, int line)
  : Statement(std::move(source)), line_(line) {}

//todo
void GOTOStatement::execute(VarState& state, Program& program) const {
  // program.jumpToLine(line_);
}

IFStatement::IFStatement(std::string source, Expression* expr1, char op,
  Expression* expr2, int line)
  : Statement(std::move(source)), expr1_(expr1), expr2_(expr2), op_(op), line_(line) {}
IFStatement::~IFStatement() {
  delete expr1_;
  delete expr2_;
}

void IFStatement::execute(VarState& state, Program& program) const { //todo????????????删除行
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
  //todo
  if (judge) {
    // program.jumpToLine(line_);
  }
}

// 解释器指令
//todo
RUNStatement::RUNStatement(std::string source) : Statement(std::move(source)) {}
void RUNStatement::execute(VarState& state, Program& program) const {
  // program.runStatement();
}

LISTStatement::LISTStatement(std::string source) : Statement(std::move(source)) {}
void LISTStatement::execute(VarState& state, Program& program) const {
  // program.listStatement();
}

CLEARStatement::CLEARStatement(std::string source) : Statement(std::move(source)) {}
void CLEARStatement::execute(VarState& state, Program& program) const {
  // program.clearStatement();
}

QUITStatement::QUITStatement(std::string source) : Statement(std::move(source)) {}
void QUITStatement::execute(VarState& state, Program& program) const {
  // program.quit();
}

HELPStatement::HELPStatement(std::string source) : Statement(std::move(source)) {}
void HELPStatement::execute(VarState& state, Program& program) const {
  std::cout << "Supported commands:" << std::endl;
  std::cout << "<line> REM <comment> - Comment" << std::endl;
  std::cout << "( <line> ) LET <var> = <expr> - Assign expression value to variable" << std::endl;
  std::cout << "( <line> ) PRINT <expr> - Evaluate and print expression" << std::endl;
  std::cout << "( <line> ) INPUT <var> - Read integer input and assign to variable" << std::endl;
  std::cout << "<line> END - End program execution" << std::endl;
  std::cout << "<line> GOTO <line> - Jump to specified line" << std::endl;
  std::cout << "<line> IF <expr1> <op> <expr2> THEN <line> - Conditional jump" << std::endl;
  std::cout << "<line> - Delete line" << std::endl;
  std::cout << "RUN - Start program execution" << std::endl;
  std::cout << "LIST - List all program lines" << std::endl;
  std::cout << "CLEAR - Clear all program lines" << std::endl;
  std::cout << "QUIT - Exit interpreter" << std::endl;
  std::cout << "HELP - Print this help message" << std::endl;
}