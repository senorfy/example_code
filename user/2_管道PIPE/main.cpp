#include <iostream>  
#include <unistd.h>  
#include <string.h>  
#include <errno.h>  

using namespace std;

int main()  
{  
    int fd[2];  
    int ret = pipe(fd);  
    if (ret == -1) {  
        cout << "pipe error" << endl;  
        return 1;  
    }  
    pid_t id = fork();  
    if (id == 0) {//child  
        int i = 0;  
        close(fd[0]);  
        char *child = "I am child!";  
        while (i < 5) {  
            write(fd[1], child, strlen(child) + 1);  
            sleep(2);  
            i++;  
        }  
    }  
    else if (id > 0) {//father  
        close(fd[1]);  
        char msg[100];  
        int j = 0;  
        while (j < 5) {  
            memset(msg,'\0', sizeof(msg));  
            ssize_t s = read(fd[0], msg, sizeof(msg));  
            if (s > 0) {  
                msg[s - 1] = '\0';  
            }  
            printf("%s\n", msg);  
            j++;  
        }  
    }  
    else {//error  
        cout << "fork error" << endl;  
        return 2;  
    }  
    return  0;  
}  