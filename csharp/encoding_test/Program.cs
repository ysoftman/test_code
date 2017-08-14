using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;	// Encoding
using System.Threading.Tasks;

namespace EncodingTest
{
    class Program
    {
        static void Main(string[] args)
        {
            int nNum = 123;
            Console.Write("{0:d}\n", nNum);

            // 인코딩 테스트
            string strLog = "";
            Console.Clear();
            strLog += "Encoding.Default.EncodingName: " + Encoding.Default.EncodingName + "(" + Encoding.Default.CodePage + ")\n";
            strLog += "Encoding.UTF8.EncodingName: " + Encoding.UTF8.EncodingName + "(" + Encoding.UTF8.CodePage + ")\n";
            Console.WriteLine(strLog);

            string strMsg = "YoonByoungHoon, 윤병훈 인코딩 테스트";
            Console.WriteLine("Default: " + strMsg);

            Encoding utf8 = Encoding.UTF8;
            Encoding cp949 = Encoding.GetEncoding(949);

            byte[] cp949bytes = cp949.GetBytes(strMsg);
            byte[] utf8bytes = Encoding.Convert(cp949, utf8, cp949bytes);
            Console.WriteLine("UTF8: " + cp949.GetString(utf8bytes));

            byte[] cp949bytes2 = Encoding.Convert(utf8, cp949, utf8bytes);
            Console.WriteLine("CP949: " + cp949.GetString(cp949bytes2));
        }
    }
}
