// ysoftman
// 파일 무한 읽기 테스트
// 이 프로그램이 파일 하나를 (아주 천천히)읽고 있는 와중에, 파일을 삭제하거나 수정하였을때 현상을 보기 위함
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function

int main()
{
    fprintf(stdout, "file read...\n");
    FILE *fp = fopen("infinite_file.txt", "rb");
    if (fp == NULL)
    {
        fprintf(stdout, "can't load infinite_file.txt\n");
        fclose(fp);
        exit(-1);
    }
    char c = NULL;
    while ((c = fgetc(fp)) != EOF)
    {
        fprintf(stdout, "%c", c);
        // wait for xxx seconds
        sleep(1);
    }

    fprintf(stdout, "finish\n");
    fclose(fp);
    return 0;
}
