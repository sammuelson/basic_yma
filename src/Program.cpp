#include "Program.hpp"

#include <string>
#include "Parser.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "utils/Error.hpp"

Program::Program() : programCounter_(-1), programEnd_(false), levelCounter_(0) {}

// 添加一行程序。
void Program::addStmt(int line, Statement* stmt) {
  if (line <= 0) {
    throw BasicError("INVALID LINE NUMBER");
  }
  recorder_.add(line, stmt);
}

// 删除行号对应的语句。
void Program::removeStmt(int line) {
  recorder_.remove(line);
}

// 按行号升序执行程序，支持 GOTO/IF 改变 PC。
void Program::run() {
  programEnd_ = false;
  programCounter_ = recorder_.nextLine(0);
  while (programCounter_ > 0 && !programEnd_) {
    Statement* crt_stmt = recorder_.getStmt(programCounter_);
    int crt_pc = programCounter_;
    execute(crt_stmt);
    if (!programEnd_ && programCounter_ != -1 && crt_pc == programCounter_) {
      programCounter_ = recorder_.nextLine(programCounter_);
    }
  }
  programEnd();
}

// 输出 `<line> <stmt>`。
void Program::list() const {
  recorder_.printLines();
}

// 清空 Recorder 与 VarState
void Program::clear() {
  recorder_.clear();
  vars_.clear();
}

// 进入一层。
void Program::indent() {
  levelCounter_ += 1;
  vars_.mapIndent();
}

// 退出一层。
void Program::dedent() {
  // 检验层数合法性.
  if (levelCounter_ <= 0) {
    throw BasicError("INVALID DEDENT");
  }
  levelCounter_ -= 1;
  vars_.mapDedent();
}

// 执行一条语句
void Program::execute(Statement* stmt) {
  if (stmt == nullptr) {return; }
  stmt->execute(vars_, *this);
}

// 获取当前层数。
int Program::getLC() const noexcept {
  return levelCounter_;
}

// 获取当前行号，RUN 期间有效
int Program::getPC() const noexcept {
  return programCounter_;
}

// 强制改变 PC，用于 GOTO/IF
void Program::changePC(int line) {
  if (line <= 0) {
    throw BasicError("INVALID LINE NUMBER");
  }
  // 检查目标行号是否存在
  if (!recorder_.hasLine(line)) {
    throw BasicError("LINE NUMBER ERROR");
  }
  programCounter_ = line;
}

void Program::programEnd() {
  programEnd_ = true;
  programCounter_ = -1;
}

void Program::resetAfterRun() noexcept {
  programEnd_ = false;
  programCounter_ = -1;
}