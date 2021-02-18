
#include <string>

class Accounting {
  std::string full_name; // 氏名
  long crnt_asset; // 資産

public:
  Accounting(std::string name, long amnt);

  std::string name() {return full_name;}
  long asset() {return crnt_asset;}

  void earn(long amnt);
  void spend(long amnt);
};
