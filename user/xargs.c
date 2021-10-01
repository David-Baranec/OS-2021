#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "usage: xargs command\n");
        exit(1);
    }

    int can_read = 1;
    char *_argv[MAXARG];
    char buf[BUF_SIZE];

    for (int i = 1; i < argc; ++i) {
        _argv[i - 1] = argv[i];
    }

    while (can_read) {
        char c;
        int _argv_cnt = argc - 1;
        int buf_idx = 0;
        int buf_begin = 0;
        while (1) {
            can_read = read(0, &c, sizeof(c));
            if (!can_read)
                exit(0);
            if (c == ' ' || c == '\n') {
                buf[buf_idx++] = 0;
                _argv[_argv_cnt++] = &buf[buf_begin];
                buf_begin = buf_idx;
                if (c == '\n')
                    break;
            } else {
                buf[buf_idx++] = c;
            }
        }

        _argv[_argv_cnt] = 0;

        if (fork() == 0) {
            exec(_argv[0], _argv);
        } else {
            wait(0);
        }
    }
    exit(0);
}