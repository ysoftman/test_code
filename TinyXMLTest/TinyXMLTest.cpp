////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// TinyXML 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <stdio.h>
#include "tinyxml/tinyxml.h"

#if (_MSC_VER <= 1500) // Visual C++ 9.0(2008)
#pragma comment(lib, "./tinyxml/tinyxml_vc9_mtd.lib")
#elif (_MSC_VER <= 1600) // Visual C++ 10.0(2010)
#pragma comment(lib, "./tinyxml/tinyxml_vc10_mtd.lib")
#elif (_MSC_VER <= 1700) // Visual C++ 11.0(2012)
#pragma comment(lib, "./tinyxml/tinyxml_vc11_mtd.lib")
#endif

using namespace std;

namespace TINYXML
{
	class TestTinyXML
	{
	public:
		TestTinyXML();
		TestTinyXML(string buffer);
		~TestTinyXML();

		bool SetXML(string buffer);
		bool isXML();

	private:
		TiXmlDocument m_doc;
	};

}

namespace TINYXML
{
	TestTinyXML::TestTinyXML()
	{
		m_doc.Clear();
	}

	TestTinyXML::TestTinyXML(string buffer)
	{
		SetXML(buffer);
	}

	TestTinyXML::~TestTinyXML()
	{
		m_doc.Clear();
	}

	bool TestTinyXML::SetXML(string buffer)
	{
		//m_doc.Parse(buffer.c_str(), 0, TIXML_ENCODING_UTF8);
		m_doc.Parse(buffer.c_str(), 0, TIXML_ENCODING_UNKNOWN);

		return 1;
	}

	bool TestTinyXML::isXML()
	{
		if (m_doc.Error())
		{
			fprintf(stderr, "Error: %s\n", m_doc.ErrorDesc());
			fprintf(stderr, "This string is Text\n");
			return 0;
		}
		fprintf(stderr, "This string is XML\n");

		return 1;
	}
}

int main()
{
	printf("MSC_VER = %d\n", _MSC_VER);
	TINYXML::TestTinyXML tinyxml;
	string buffer = "<Player defaultvalue=\"hero\"> \
					<Name defaultvalue=\"홍길동\" /> \
					<E-Mail defaultvalue=\"ysoftman@naver.com\" /> \
					</Player>";
	printf("%s\n\n\n", buffer.c_str());
	tinyxml.SetXML(buffer);
	tinyxml.isXML();

	return 0;
}
