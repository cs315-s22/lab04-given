#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "armemu.h"

int quadratic_c(int x, int a, int b, int c);
int quadratic_s(int x, int a, int b, int c);

int midpoint_c(int start, int end);
int midpoint_s(int start, int end);

int max3_c(int a, int b, int c);
int max3_s(int a, int b, int c);

int get_bitseq_c(int n, int start, int end);
int get_bitseq_s(int n, int start, int end);

// quadratic_test calls the C, assembly, and emulated versions of quadratic
void quadratic_test(int x, int a, int b, int c) {
    int r;
    struct arm_state state;

    r = quadratic_c(x, a, b, c);
    printf("C: %d\n", r);

    r = quadratic_s(x, a, b, c);
    printf("Asm: %d\n", r);

    armemu_init(&state, (uint32_t *) quadratic_s, x, a, b, c);
    r = armemu(&state);
    printf("Emu: %d\n", r);
}

// midpoint_test calls the C, assembly, and emulated versions of midpoint
void midpoint_test(int start, int end) {
    int r;
    struct arm_state state;

    r = midpoint_c(start, end);
    printf("C: %d\n", r);

    r = midpoint_s(start, end);
    printf("Asm: %d\n", r);

    armemu_init(&state, (uint32_t *) midpoint_s, start, end, 0, 0);
    r = armemu(&state);
    printf("Emu: %d\n", r);
}

// max3_test calls the C, assembly, and emulated versions of max3
void max3_test(int a, int b, int c) {
    int r;
    struct arm_state state;

    r = max3_c(a, b, c);
    printf("C: %d\n", r);

    r = max3_s(a, b, c);
    printf("Asm: %d\n", r);

    armemu_init(&state, (uint32_t *) max3_s, a, b, c, 0);
    r = armemu(&state);
    printf("Emu: %d\n", r);
}

// get_bitseq_test calls the C, assembly, and emulated versions of get_bitseq
void get_bitseq_test(int n, int start, int end) {
    int r;
    struct arm_state state;

    r = get_bitseq_c(n, start, end);
    printf("C: %d\n", r);

    r = get_bitseq_s(n, start, end);
    printf("Asm: %d\n", r);

    armemu_init(&state, (uint32_t *) get_bitseq_s, n, start, end, 0);
    r = armemu(&state);
    printf("Emu: %d\n", r);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("usage: lab04 <prog> [<arg1> ...]\n");
        exit(-1);
    }

    if (!strcmp(argv[1], "quadratic")) {
        int x = atoi(argv[2]);
        int a = atoi(argv[3]);
        int b = atoi(argv[4]);
        int c = atoi(argv[5]);
        quadratic_test(x, a, b, c);
    } 
    else if (!strcmp(argv[1], "midpoint")) {
        int start = atoi(argv[2]);
        int end = atoi(argv[3]);
        midpoint_test(start, end);
    } else if (!strcmp(argv[1], "max3")) {
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        int c = atoi(argv[4]);
        max3_test(a, b, c);
    } else if (!strcmp(argv[1], "get_bitseq")) {
        int n = atoi(argv[2]);
        int start = atoi(argv[3]);
        int end = atoi(argv[4]);
        get_bitseq_test(n, start, end);
    } else {
        printf("usage: lab04 <prog> [<arg1> ...]\n");
        exit(-1);
    }

    return 0;
}
