// ysoftman
// ifstrea(파일 입력), ofstraem (파일 출력) 테스트
// http://www.cplusplus.com/reference/fstream/ofstream/open/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char filename[100] = "file_stream_test.txt";

    cout << "filename: " << filename << endl;

    // 파일 쓰기
    ofstream outFile;
    outFile.open(filename, std::ofstream::app);
    outFile.write("abcdefghijklmnopqrstuvwxyz\n", 27);
    outFile.close();

    // 파일 읽기
    ifstream inFile(filename);
    while (not inFile.eof())
    {
        char szBuffer[27] = {
            0,
        };
        inFile.read(szBuffer, 27);
        cout << szBuffer << endl;
    }
    inFile.close();

    return 0;
}
