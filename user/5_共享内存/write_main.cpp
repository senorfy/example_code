#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shared_memory_key", 1234);  // 共享内存的键值
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);  // 创建共享内存

    if (shm_id == -1) {
        perror("shmget");
        return 1;
    }

    void* shm_ptr = shmat(shm_id, 0, 0);  // 连接共享内存

    if (shm_ptr == (void*) -1) {
        perror("shmat");
        return 1;
    }

    // 写入数据到共享内存
    char data[] = "Hello, shared memory!";
    strncpy((char*)shm_ptr, data, SHM_SIZE);

    // 分离共享内存
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}