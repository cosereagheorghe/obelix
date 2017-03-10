#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

size_t N = 100;
uint64_t *a;

/*
 * return the largest positive integer k suck that k^3 <= n
 */
size_t cbrtint(size_t n)
{
    size_t k = (size_t)(floor(cbrt((double)n)));
    while (k*k*k <= n) ++k;
    return(--k);
}

int cbrtint_test(void)
{
    size_t k=0;

    printf("cbrtint_test: start ...\n");
    for (size_t n = 0; n < 100*1000*1000; ++n) {
        if (n%(1000*1000) == 0)
            printf("n=%d\n", n/(1000*1000));
        k = cbrtint(n);
        if (k*k*k > n) {
            printf("cbrtint_test: fail: n=%lld, k=%lld\n", n, k);
            assert(0);
            return(-1);
        }
        k++;
        if (k*k*k <= n) {
            printf("cbrtint_test: fail: n=%lld, k=%lld\n", n, k);
            assert(0);
            return(-2);
        }
    }
    printf("cbrtint_test: passed\n");
    return(0);
}

int mem_init(size_t sz)
{
    size_t n;
    N = sz;
    n = (1 + (sz+1)/21) * sizeof(uint64_t);
    a = malloc(n); assert(a); memset(a, 0xFF, n);
    return(0);
}

void mem_fini(void)
{
    free(a);
}

void mem_set(size_t k, int val)
{
    assert(k <= N);
    a[k/21] &= ~(7LL << (3*(k%21)));
    a[k/21] |= ((val-1) & 7LL) << (3*(k%21));
}

int mem_get(size_t k)
{
    assert(k <= N);
    return(1 + ((a[k/21] & (7LL<<(3*(k%21)))) >> (3*(k%21))));
}

int mem_test(void)
{
    size_t i,r,sz;

    printf("mem_test: start ...\n");
    for (sz = 1; sz < 1024; ++sz) {
        mem_init(sz);
        mem_set(0, 7);
        mem_set(sz, 3);
        for (r = 0; r < 8; ++r) {
            for (i = 1; i < sz; ++i)
                mem_set(i, 1 + (i*i*5 + r)%8);
            for (i = 1; i < sz; ++i)
                assert(mem_get(i) == 1 + (5*i*i + r)%8);
            assert(mem_get(sz) == 3);
            assert(mem_get(0) == 7);
        }
        mem_fini();
    }
    printf("mem_test: passed\n");

    return(0);
};

void test(void)
{
    mem_test();
    cbrtint_test();
}


uint64_t T(uint64_t k)
{
    return((k*(k+1)*(k+2))/6);
}

void help(const char *prog)
{
    printf("Usage: %s <num>\n", prog);
}


#define MAXSOL 1024
int main(int argc, char *argv[])
{
    size_t sz, n;
    size_t k, k1, k2;
    int val;
    int sol[MAXSOL]; int tops;
    int min;

    if (argc == 1) {
        help(argv[0]);
        return(-1);
    }
    sz = atoll(argv[1]);
    if (sz < 0) {
        help(argv[0]);
        return(-1);
    }

    mem_init(sz);
    for (n = 1; n <= N; ++n) {
        if (n%1000000==0) printf("n=%d\n", n/1000000);
        k1 = cbrtint((6*n)/8); k2 = cbrtint(6*n);
        while (n < T(k2)) --k2;
        if (n == T(k2)) {
            mem_set(n,1);
            printf("%llu 1 %llu\n", n, k2);
            continue;
        }
        for (k = k1; k <= k2; ++k) {
            val = mem_get(n - T(k)) + 1;
            min = mem_get(n);
            if (val < min) {
                min = val;
                mem_set(n, min);
                tops = 0;
                sol[tops++] = k;
            } else if (val == min) {
                assert(tops < MAXSOL);
                sol[tops++] = k;
            }
            if (min == 2) break;
        }
        printf("%llu %llu", n, min);
        for (k = 0; k < tops; ++k)
            printf(" %d", sol[k]);
        printf("\n");
    }
    mem_fini();
}
