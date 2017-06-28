// ysoftman
// limit 값 파악
#include <stdio.h>
#include <iostream>
#include <limits.h>

using namespace std;

int main()
{
    // http://www.cplusplus.com/reference/climits/
    // CHAR_BIT	Number of bits in a char object (byte)	8 or greater*
    // SCHAR_MIN	Minimum value for an object of type signed char	-127 (-27+1) or less*
    // SCHAR_MAX	Maximum value for an object of type signed char	127 (27-1) or greater*
    // UCHAR_MAX	Maximum value for an object of type unsigned char	255 (28-1) or greater*
    // CHAR_MIN	Minimum value for an object of type char	either SCHAR_MIN or 0
    // CHAR_MAX	Maximum value for an object of type char	either SCHAR_MAX or UCHAR_MAX
    // MB_LEN_MAX	Maximum number of bytes in a multibyte character, for any locale	1 or greater*
    // SHRT_MIN	Minimum value for an object of type short int	-32767 (-215+1) or less*
    // SHRT_MAX	Maximum value for an object of type short int	32767 (215-1) or greater*
    // USHRT_MAX	Maximum value for an object of type unsigned short int	65535 (216-1) or greater*
    // INT_MIN	Minimum value for an object of type int	-32767 (-215+1) or less*
    // INT_MAX	Maximum value for an object of type int	32767 (215-1) or greater*
    // UINT_MAX	Maximum value for an object of type unsigned int	65535 (216-1) or greater*
    // LONG_MIN	Minimum value for an object of type long int	-2147483647 (-231+1) or less*
    // LONG_MAX	Maximum value for an object of type long int	2147483647 (231-1) or greater*
    // ULONG_MAX	Maximum value for an object of type unsigned long int	4294967295 (232-1) or greater*
    // LLONG_MIN	Minimum value for an object of type long long int	-9223372036854775807 (-263+1) or less*
    // LLONG_MAX	Maximum value for an object of type long long int	9223372036854775807 (263-1) or greater*
    // ULLONG_MAX	Maximum value for an object of type unsigned long long int	18446744073709551615 (264-1) or greater*

    cout << "using cout" << endl;
    cout << "CHAR_BIT = " << cout << CHAR_BIT << endl;
    cout << "SCHAR_MIN = " << cout << SCHAR_MIN << endl;
    cout << "SCHAR_MAX = " << cout << SCHAR_MAX << endl;
    cout << "UCHAR_MAX = " << cout << UCHAR_MAX << endl;
    cout << "CHAR_MIN = " << cout << CHAR_MIN << endl;
    cout << "CHAR_MAX = " << cout << CHAR_MAX << endl;
    cout << "MB_LEN_MAX = " << cout << MB_LEN_MAX << endl;
    cout << "SHRT_MIN = " << cout << SHRT_MIN << endl;
    cout << "SHRT_MAX = " << cout << SHRT_MAX << endl;
    cout << "USHRT_MAX = " << cout << USHRT_MAX << endl;
    cout << "INT_MIN = " << cout << INT_MIN << endl;
    cout << "INT_MAX = " << cout << INT_MAX << endl;
    cout << "UINT_MAX = " << cout << UINT_MAX << endl;
    cout << "LONG_MIN = " << cout << LONG_MIN << endl;
    cout << "LONG_MAX = " << cout << LONG_MAX << endl;
    cout << "ULONG_MAX = " << cout << ULONG_MAX << endl;
    cout << "LLONG_MIN = " << cout << LLONG_MIN << endl;
    cout << "LLONG_MAX = " << cout << LLONG_MAX << endl;
    cout << "ULLONG_MAX = " << cout << ULLONG_MAX << endl;
    cout << endl;

    printf ("using printf()\n");
    printf ("INT_MIN = %d\n", INT_MIN);
    printf ("INT_MAX = %d\n", INT_MAX);
    printf ("UINT_MAX = %d\n", UINT_MAX);
    printf ("LONG_MIN = %ld\n", LONG_MIN);
    printf ("LONG_MAX = %ld\n", LONG_MAX);
    printf ("ULONG_MAX = %lu\n", ULONG_MAX);
    printf ("LLONG_MIN = %lld\n", LLONG_MIN);
    printf ("LLONG_MAX = %lld\n", LLONG_MAX);
    printf ("ULLONG_MAX = %llu\n", ULLONG_MAX);

    return 0;
}