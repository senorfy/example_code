#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    int fd = 0;
    int len = 0;
    int ret;
    char buf[1024] = { 0 };
    mkfifo("./test", 0664);
    
#if 1
    //只写方式打开test
    fd = open("./test", O_WRONLY);
    if (fd < 0)
    {
		perror("open error");
		exit(1);
    }
#endif

#if 0
    fd = open("./test", O_WRONLY | O_NONBLOCK);//设置成非阻塞
    if (fd < 0)
    {
    //判断是否为对端没打开而导致ENXIO错误
		if (errno == ENXIO)
		{
			perror("open error");
		}
		exit(1);
    }
#endif

    puts("open fifo write");
    //向FIFO写入数据
    while ((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    {
		write(fd, buf, len);
    }
    close(fd);
    return 0;
}
