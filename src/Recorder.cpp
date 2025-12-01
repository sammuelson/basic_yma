#include "Recorder.hpp"

#include <string>
#include <vector>
#include <iostream>
#include "Parser.hpp"
#include "Statement.hpp"
#include "utils/Error.hpp"

// 插入或覆盖指定行。
void Recorder::add(int line, Statement *stmt) {
  if (line <= 0) {
    throw BasicError("INVALID LINE NUMBER");
  }
  if (stmt == nullptr) {
    throw BasicError("SYNTAX ERROR");
  }
  auto it = statements_.find(line);
  if (it == statements_.end()) {
    statements_.insert({line, stmt});
  }
  else {
    it->second = stmt;
  }
}

// 删除行，不存在则无事发生。
void Recorder::remove(int line) {
  auto it = statements_.find(line);
  if (it != statements_.end()) {
    delete it->second;  // 释放语句对象
    statements_.erase(it);
  }
}

// 读取行号对应 Stmt ，不存在则返回 nullptr。
const Statement* Recorder::get(int line) const noexcept {
  auto it = statements_.find(line);
  if (it != statements_.end()) {
    return it->second;
  }
  return nullptr;
}

// 询问行号对应 Stmt 是否存在。
bool Recorder::hasLine(int line) const noexcept {
  if (statements_.find(line) == statements_.end()) {
    return false;
  }
  return true;
}

// 清空全部行。
void Recorder::clear() noexcept {
  for (auto it = statements_.begin(); it != statements_.end(); it++) {
    delete it->second;
  }
  statements_.clear();
}

// 按行号升序输出所有程序。
void Recorder::printLines() const {
  for (auto it = statements_.begin(); it != statements_.end(); it++) {
    std::cout << it->first << " " << it->second->text() << std::endl;
  }
}

// 返回大于 line 的最小行号，不存在则返回 -1。
int Recorder::nextLine(int line) const noexcept {
  auto it = statements_.upper_bound(line);
  if (it == statements_.end()) {
    return -1;
  }
  return it->first;
}