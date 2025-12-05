#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"

const unordered_map<string, int> init_int;

void VarState::mapIndent() {
  map_values.push_back({init_int});    // 准备该层的空map，以便记录新变量。
}

void VarState::mapDedent() {  // 在program中再检验层数合法性。
  // 删除where_int中最后一层的变量。
  auto it = map_values[map_values.size() - 1].begin();
  for (; it != map_values[map_values.size() - 1].end(); it++) {
    string name = it->first;
    if ((where_int.find(name)->second).size() == 1) {
      where_int.erase(name);
    }
    else {
      where_int.find(name)->second.pop_back();
    }
  }
  map_values.pop_back();
}

void VarState::setValue(int crtLevel, const std::string& name, int value) {
  if (map_values[map_values.size() - 1].count(name) == 1) {  // 该变量在本层已存在，现在重新赋值。
    auto it = map_values[map_values.size() - 1].find(name);
    it->second = value;
    (where_int.find(name)->second)[(where_int.find(name)->second).size() - 1] = crtLevel;
  }
  else {
    map_values[map_values.size() - 1].insert({name, value});
    if (where_int.count(name) == 1) {  // 该变量在较低层存在。
      where_int.find(name)->second.push_back(crtLevel);
    }
    else {
      where_int.find(name)->second.pop_back();  // 该变量名从未存在。
    }
  }
}

int VarState::getValue(const std::string& name) const {
  if (where_int.find(name) == where_int.end()) {
    throw BasicError("VARIABLE NOT DEFINED");
  }
  return where_int.find(name)->second[where_int.find(name)->second.size() - 1];
}

void VarState::clear() {
  where_int.clear();
  map_values.clear();
  map_values.push_back(init_int);
}
