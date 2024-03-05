#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define iters (1e8)

int main() {
    clock_t time_begin, time_end, time_;
    int p[2], cnt;
    char buf[64];

    cnt = 0;
    time_begin = clock();
    pipe(p); // read from p[0], write to p[1]
    if (fork() == 0) {
        // child
        for (cnt = 0; cnt < iters; ++cnt)
            write(p[1], "a", 1);
        exit(0);
    }
    else {
        // father
        while(read(p[0], buf, 1)) {
            if (++cnt == iters) break;
        }
        time_end = clock();
        time_ = (time_end - time_begin) * 1000 / CLOCKS_PER_SEC;
        printf("it takes: %ld ms\n", time_);
        printf("%f bytes per ms\n", 1.0f * iters / time_);
        exit(0);
    }
}