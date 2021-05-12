#include <iostream>
#include "date.h"
#include "accounting.h"

using namespace std;

int main()
{
	// 中野君の口座
	Accounting nakano("中野隼人", 1000, Date(2125, 1, 24));
	string dw[] = {"日", "月", "火", "水", "木", "金", "土"};

	cout << "中野君¥n";
	cout << "氏　名＝" << nakano.name() << '¥n';
	cout << "資　産＝" << nakano.asset() << "円¥n";
	cout << "誕生日＝" << nakano.birthday();
	cout << "（" << dw[nakano.birthday().day_of_week()] << "）¥n";
}
