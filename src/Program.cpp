// TODO
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