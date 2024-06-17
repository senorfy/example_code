#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    int fd = 0;
    int len = 0;
    char buf[1024] = { 0 };

    //只读打开test
    fd = open("./test", O_RDONLY);
    if (fd < 0)
    {
        perror("open error");
        exit(1);
    }
    puts("open fifo read");

    //从管道中读取数据
    while ((len = read(fd, buf, sizeof(buf))) > 0)
    {
        write(STDOUT_FILENO, buf, len);
    }

    //如果read返回0，说明读到文件末尾或对端已关闭
    if (len == 0)
    {
        puts("peer is close or file end");
    }
    else
    {
        puts("read error");
    }

    close(fd);
    return 0;
}
