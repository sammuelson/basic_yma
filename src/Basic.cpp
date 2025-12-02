#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

void Help();

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {

      bool executed = false;
      TokenStream crt_TStream = lexer.tokenize(line);
      if (crt_TStream.size() == 1) {
        if (line == "RUN") {
          executed = true;
          program.run();
        }
        if (line == "LIST") {
          executed = true;
          program.list();
        }
        if (line == "CLEAR") {
          executed = true;
          program.clear();
        }
        if (line == "QUIT") {
          executed = true;
          return 0;
        }
        if (line == "HELP") {
          executed = true;
          Help();
        }
      }
      if (!executed) {
        ParsedLine crt_PLine = parser.parseLine(crt_TStream, line);
        if (crt_PLine.getLine()) {
          // 如果有行号，返回true
          int line_num = crt_PLine.getLine().value();
          if (crt_PLine.getStatement() == nullptr) {
            program.removeStmt(line_num);
          }
          else {
            // 存入指令集。
            Statement* crt_stmt = crt_PLine.fetchStatement();  //这样Pline析构之后就不会把这个指针删掉
            program.addStmt(line_num, crt_stmt);
          }
        }
        else {  // 直接执行。
          program.execute(crt_PLine.getStatement());
        }
      }

    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}


void Help() {
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