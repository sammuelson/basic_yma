#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class VarState {
 public:
  void mapIndent();
  void mapDedent();
  void setValue(int crtLevel, const std::string& name, int value);
  int getValue(const std::string& name) const;
  void clear();

 private:
  // levelCounter_在Program中管理。
  // 用一个vector<unordered_map<变量名，变量值>>储存每层变量。
  // Dedent层数回退时，删除最后一层变量。
  vector<unordered_map<string, int>> map_values;
  // 再用一个unordered_map<string变量名，vector<int层数>>，记录变量所在层数。
  // 其中vector正序，Dedent时记得从上面的map遍历过来pop。
  unordered_map<string, vector<int>> where_int;
  // 调用变量时，从后2个map中都先搜索最大的层数，
};
