
#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        fprintf(2, "sleep: missing duration\n");
        exit(1);
    }

    int duration = atoi(argv[1]);

    if (duration < 0)
    {
        fprintf(2, "sleep: negative duration\n");
        exit(1);
    }

    pause(duration);
    exit(0);
}
