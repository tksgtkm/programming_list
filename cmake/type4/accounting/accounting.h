#ifndef ___Class_Accounting
#define ___Class_Accounting

#include <string>
#include "../date/date.h"

//===== 会計クラス =====//
class Accounting {
	std::string full_name;	// 氏名
	long crnt_asset;		// 資産
	Date birth;				// 誕生日

public:
	// コンストラクタ
	Accounting(const std::string& name, long amnt, const Date& op);

	void earn(long amnt);					// 収入がある
	void spend(long amnt);					// 支出がある

	std::string name() const  { return full_name; }		// 氏名を調べる
	long asset() const        { return crnt_asset; }	// 資産を調べる
	Date birthday() const     { return birth; }			// 誕生日を調べる
};

#endif
