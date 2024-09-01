#include <unistd.h>
#include "TcpServer.h"

int main(int argc, char *argv[]) {
#if 0
    if (argc < 3)
    {
        printf("./a.out port path\n");
        return -1;
    }
    unsigned short port = atoi(argv[1]);
    // 切换服务器的工作路径
    chdir(argv[2]);
#else
    unsigned short port = 10000;
    chdir("/home/sunke/code");
#endif
    // 启动服务器
    auto *server = new TcpServer(port, 4);
    server->run();

    return 0;
}
