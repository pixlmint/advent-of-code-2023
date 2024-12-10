#include <stdlib.h>
#include <time.h>

#include "aoc.h"

Perf *perf_init() {
    Perf *perf = malloc(sizeof(Perf));
    perf->timers = malloc(sizeof(Timer) * 6);
    perf->length = 0;
    perf->max_length = 6;

    return perf;
}

int timer_start(char *name, Perf *perf) {
    if (perf->length >= perf->max_length) {
        perf->max_length *= 1.5;
        perf->timers = realloc(perf->timers, sizeof(Timer) * perf->max_length);
    }
    
    Timer *t = malloc(sizeof(Timer));

    int pos = perf->length;
    perf->timers[pos] = t;
    perf->length++;

    t->name = name;
    t->start_time = clock();
    t->stop_time = 0;

    return pos;
}

void timer_stop(int timer, Perf *perf) {
    if (perf->length > timer && perf->timers[timer]->stop_time == 0) {
        perf->timers[timer]->stop_time = clock();
    }
}

void perf_report(Perf *perf) {
    printf("------------------------\n");
    for (int i = 0; i < perf->length; i++) {
        Timer *t = perf->timers[i];
        clock_t stop = t->stop_time;
        if (stop == 0) {
            stop = clock();
        }
        double time_taken = ((double) (stop - t->start_time)) / CLOCKS_PER_SEC;
        printf("%s: ", perf->timers[i]->name);
        if (time_taken * 1000 < 1) {
            printf("%fms\n", time_taken * 1000);
        } else {
            printf("%fs\n", time_taken);
        }
    }
    printf("------------------------\n");
}

void perf_close(Perf *perf) {
    for (int i = 0; i < perf->length; i++) {
        free(perf->timers[i]);
    }
    free(perf->timers);
    free(perf);
}
