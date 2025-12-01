### Statement 类设计

`Statement` 类是项目中用于表示和处理各种语句的核心类。它定义了所有支持的语句类型的基类和派生类，每个派生类对应一种具体的语句类型，封装了该类型语句的相关数据和行为。

`Statement` 类的继承结构如下：
```cpp
// TODO
Statement (抽象基类)
├── REMStatement (REM <comment>.表示注释行，程序忽略该行内容)
├── LETStatement (LET <var> = <expr>.表示将表达式的值赋给变量)
├── PRINTStatement (PRINT <expr>.表示计算表达式的值并打印输出)
├── INPUTStatement (INPUT <var>.表示输出一个 ?，之后从标准输入读取一个整数并赋值给变量)
├── ENDStatement (表示程序结束执行)
├── GOTOStatement (GOTO <line>。表示跳转到指定行号执行。)
└── IFStatement (IF <expr1> <op> <expr2> THEN <line>：条件跳转，若 expr1 和 expr2 通过操作符 op 比较为真，则跳转到指定行号执行。支持的操作符包括 =, <, >。 如果只有一个行号，代表删除对应指令。)


```

每个派生类都实现了基类 `Statement` 中的纯虚函数 `execute(VarState &varState, Program &program)`，用于执行该语句的具体逻辑。