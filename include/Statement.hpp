#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};


class REMStatement : public Statement {
public:
  explicit REMStatement(std::string source);
  void execute(VarState& state, Program& program) const override;
};

class LETStatement : public Statement {
public:
  LETStatement(std::string source, std::string var, Expression* expr);
  ~LETStatement();
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
  Expression* expr_;
};

class PRINTStatement : public Statement {
public:
  PRINTStatement(std::string source, Expression* expr);
  ~PRINTStatement();

  void execute(VarState& state, Program& program) const override;

private:
  Expression* expr_;
};

class INPUTStatement : public Statement {
public:
  INPUTStatement(std::string source, std::string var);
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
};

class ENDStatement : public Statement {
public:
  explicit ENDStatement(std::string source);
  void execute(VarState& state, Program& program) const override;
};

class GOTOStatement : public Statement {
public:
  GOTOStatement(std::string source, int line);
  void execute(VarState& state, Program& program) const override;

private:
  int line_;
};

class IFStatement : public Statement {
public:
  IFStatement(std::string source, Expression* expr1, char op, Expression* expr2, int line);
  ~IFStatement() override;
  void execute(VarState& state, Program& program) const override;

private:
  Expression* expr1_;
  Expression* expr2_;
  char op_;
  int line_;
};


