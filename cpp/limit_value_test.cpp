// ysoftman
// limit 값 파악
#include <limits.h>
#include <stdio.h>

#include <iostream>

using namespace std;

int main() {
    // http://www.cplusplus.com/reference/climits/
    // CHAR_BIT	Number of bits in a char object (byte)	8 or greater*
    // SCHAR_MIN	Minimum value for an object of type signed char	-127 (-27+1) or less*
    // SCHAR_MAX	Maximum value for an object of type signed char	127 (27-1) or greater*
    // UCHAR_MAX	Maximum value for an object of type unsigned char	255 (28-1) or
    // greater* CHAR_MIN	Minimum value for an object of type char	either SCHAR_MIN or
    // 0 CHAR_MAX	Maximum value for an object of type char	either SCHAR_MAX or
    // UCHAR_MAX MB_LEN_MAX	Maximum number of bytes in a multibyte character, for any locale
    // 1 or greater* SHRT_MIN	Minimum value for an object of type short int	-32767 (-215+1) or
    // less* SHRT_MAX	Maximum value for an object of type short int	32767 (215-1) or greater*
    // USHRT_MAX	Maximum value for an object of type unsigned short int	65535 (216-1) or
    // greater* INT_MIN	Minimum value for an object of type int	-32767 (-215+1) or less* INT_MAX
    // Maximum value for an object of type int	32767 (215-1) or greater* UINT_MAX	Maximum
    // value for an object of type unsigned int	65535 (216-1) or greater* LONG_MIN	Minimum
    // value for an object of type long int	-2147483647 (-231+1) or less* LONG_MAX	Maximum
    // value for an object of type long int	2147483647 (231-1) or greater* ULONG_MAX
    // Maximum value for an object of type unsigned long int	4294967295 (232-1) or greater*
    // LLONG_MIN	Minimum value for an object of type long long int	-9223372036854775807
    // (-263+1) or less* LLONG_MAX	Maximum value for an object of type long long int
    // 9223372036854775807 (263-1) or greater* ULLONG_MAX	Maximum value for an object of type
    // unsigned long long int	18446744073709551615 (264-1) or greater*

    cout << "using cout" << endl;
    cout << "CHAR_BIT = " << CHAR_BIT << endl;
    cout << "SCHAR_MIN = " << SCHAR_MIN << endl;
    cout << "SCHAR_MAX = " << SCHAR_MAX << endl;
    cout << "UCHAR_MAX = " << UCHAR_MAX << endl;
    cout << "CHAR_MIN = " << CHAR_MIN << endl;
    cout << "CHAR_MAX = " << CHAR_MAX << endl;
    cout << "MB_LEN_MAX = " << MB_LEN_MAX << endl;
    cout << "SHRT_MIN = " << SHRT_MIN << endl;
    cout << "SHRT_MAX = " << SHRT_MAX << endl;
    cout << "USHRT_MAX = " << USHRT_MAX << endl;
    cout << "INT_MIN = " << INT_MIN << endl;
    cout << "INT_MAX = " << INT_MAX << endl;
    cout << "UINT_MAX = " << UINT_MAX << endl;
    cout << "LONG_MIN = " << LONG_MIN << endl;
    cout << "LONG_MAX = " << LONG_MAX << endl;
    cout << "ULONG_MAX = " << ULONG_MAX << endl;
    cout << "LLONG_MIN = " << LLONG_MIN << endl;
    cout << "LLONG_MAX = " << LLONG_MAX << endl;
    cout << "ULLONG_MAX = " << ULLONG_MAX << endl;
    cout << endl;

    printf("using printf()\n");
    printf("INT_MIN = %d\n", INT_MIN);
    printf("INT_MAX = %d\n", INT_MAX);
    printf("UINT_MAX = %u\n", UINT_MAX);
    printf("LONG_MIN = %ld\n", LONG_MIN);
    printf("LONG_MAX = %ld\n", LONG_MAX);
    printf("ULONG_MAX = %lu\n", ULONG_MAX);
    printf("LLONG_MIN = %lld\n", LLONG_MIN);
    printf("LLONG_MAX = %lld\n", LLONG_MAX);
    printf("ULLONG_MAX = %llu\n", ULLONG_MAX);

    cout << endl << "using std::numeric_limits" << endl;
    cout << "std::numeric_limits<short>::min() = " << std::numeric_limits<short>::min() << endl;
    cout << "std::numeric_limits<short>::max() = " << std::numeric_limits<short>::max() << endl;
    cout << "std::numeric_limits<unsigned short>::max() = "
         << std::numeric_limits<unsigned short>::max() << endl;
    cout << "std::numeric_limits<int>::min() = " << std::numeric_limits<int>::min() << endl;
    cout << "std::numeric_limits<int>::max() = " << std::numeric_limits<int>::max() << endl;
    cout << "std::numeric_limits<unsigned int>::max() = "
         << std::numeric_limits<unsigned int>::max() << endl;
    cout << "std::numeric_limits<long>::min() = " << std::numeric_limits<long>::min() << endl;
    cout << "std::numeric_limits<long>::max() = " << std::numeric_limits<long>::max() << endl;
    cout << "std::numeric_limits<unsigned long>::max() = "
         << std::numeric_limits<unsigned long>::max() << endl;
    cout << "std::numeric_limits<double>::min() = " << std::numeric_limits<double>::min() << endl;
    cout << "std::numeric_limits<double>::max() = " << std::numeric_limits<double>::max() << endl;
    return 0;
}