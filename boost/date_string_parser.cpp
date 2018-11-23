// ysoftman
// boost datetimestring 파싱
#include <iostream>
#include <sstream>
#include <string>
#include <boost/date_time/format_date_parser.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/special_values_parser.hpp>

using namespace std;

bool parseDateString(string datestring)
{
	string dateformat("%Y%m%d%H%M%s");
	std::locale loc("");
	// 그레고리안 달력 타입으로 파싱
	// format_date_parser 는 년,월,일,달력등의 date_type 만 받을 수 있음
	boost::date_time::format_date_parser<boost::gregorian::date, char> *parser = new boost::date_time::format_date_parser<boost::gregorian::date, char>("", loc);
	boost::date_time::special_values_parser<boost::gregorian::date, char> svp;

	boost::gregorian::date d;
	try
	{
		d = parser->parse_date(datestring, dateformat, svp);
		cout << d << endl;
	}
	catch (...)
	{
		cout << "parse_date() exception!" << endl;
		return false;
	}

	return true;
}

int main()
{
	cout << "boost date_time_string test" << endl;
	// 정상적인 경우
	cout << "return :" << parseDateString("20060102150405") << endl;
	// 비정상적인 날짜
	cout << "return :" << parseDateString("20062102150405") << endl;
	// 시,분,초는 영향을 주지 않는다.
	cout << "return :" << parseDateString("20060102150495") << endl;

	return 0;
}
