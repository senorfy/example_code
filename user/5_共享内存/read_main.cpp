#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shared_memory_key", 1234);  // 共享内存的键值
    int shm_id = shmget(key, SHM_SIZE, 0666);  // 获取共享内存ID

    if (shm_id == -1) {
        perror("shmget");
        return 1;
    }

    void* shm_ptr = shmat(shm_id, 0, 0);  // 连接共享内存

    if (shm_ptr == (void*) -1) {
        perror("shmat");
        return 1;
    }

    // 读取共享内存中的数据
    char data[SHM_SIZE];
    strncpy(data, (char*)shm_ptr, SHM_SIZE);
    printf("Data read from shared memory: %s\n", data);

    // 分离共享内存
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        return 1;
    }

    return 0;
}