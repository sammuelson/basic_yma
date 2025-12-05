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
  LETStatement(std::string source, std::string var, std::unique_ptr<Expression> expr);
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
  std::unique_ptr<Expression> expr_;
};

class PRINTStatement : public Statement {
public:
  PRINTStatement(std::string source, std::unique_ptr<Expression> expr);

  void execute(VarState& state, Program& program) const override;

private:
  std::unique_ptr<Expression> expr_;
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
  IFStatement(std::string source, std::unique_ptr<Expression> expr1, char op,
    std::unique_ptr<Expression> expr2, int line);
  void execute(VarState& state, Program& program) const override;

private:
  std::unique_ptr<Expression> expr1_;
  std::unique_ptr<Expression> expr2_;
  char op_;
  int line_;
};


