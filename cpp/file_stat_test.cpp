// ysoftman
// 파일 퍼미션 파악 및 변경
#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *fp = fopen("file.txt", "a");

    // 파일 상태 확인
    struct stat fs;
    stat("file.txt", &fs);
    printf("fs.st_mode : %o\n", fs.st_mode);
    // 100644 퍼미션 값
    unsigned int mode = S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    printf("mode : %o\n", mode);
    // 파일퍼미션 확인해서 644 가 아니면 644 로 변경
    if (fs.st_mode != mode) {
        chmod("file.txt", 0664);
        printf("file mode changed 0644\n");
    }

    fclose(fp);
    return 0;
}
