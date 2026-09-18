#include "dsp-lecture.h"
#include <stdio.h>

void random_cvector(int n, cint16_t* v)
{
    for (int i = 0; i < n; i++)
    {
        v[i].real = mrand48() & 0xFFFF;
        v[i].imag = mrand48() & 0xFFFF;
    }
}

void mul_vector_tb_cq15(long seed, unsigned runs)
{
    unsigned run;
    int i, n;

    cint32_t* dst = NULL;
    cint32_t* dst_ref = NULL;
    cint16_t* src1 = NULL;
    cint16_t* src2 = NULL;

    srand48(seed);

    for (run = 0; run < runs; run++)
    {
        n = lrand48() % N_MAX;
        dst = (cint32_t*)realloc(dst, n * sizeof(cint32_t));
        dst_ref = (cint32_t*)realloc(dst_ref, n * sizeof(cint32_t));
        src1 = (cint16_t*)realloc(src1, n * sizeof(cint16_t));
        src2 = (cint16_t*)realloc(src2, n * sizeof(cint16_t));

        random_cvector(n, (cint16_t*)src1);
        random_cvector(n, (cint16_t*)src2);

        // Тест эталонной функции
        clock_t ref_start = clock();
        mul_vector_ref_cq15(n, dst_ref, src1, src2);
        clock_t ref_finish = clock();
        clock_t ref_time = ref_finish - ref_start;
        printf("Ref time: %ld ticks\n", (long)ref_time);

        // Тест быстрой SIMD функции
        clock_t fast_start = clock();
        mul_vector_fast_cq15(n, dst, src1, src2);
        clock_t fast_finish = clock();
        clock_t fast_time = fast_finish - fast_start;
        printf("Fast time: %ld ticks\n", (long)fast_time);

        // Проверка совпадения результатов
        for (i = 0; i < n; i++)
        {
            if (dst[i].real != dst_ref[i].real || dst[i].imag != dst_ref[i].imag)
            {
                fprintf(stderr, "Error at index %d: ref=(%d, %d) fast=(%d, %d)\n",
                    i, dst_ref[i].real, dst_ref[i].imag,
                    dst[i].real, dst[i].imag);
                exit(1);
            }
        }
        printf("Run %d: OK (n=%d)\n", run, n);
    }

    free(dst);
    free(dst_ref);
    free(src1);
    free(src2);
}

int main()
{
    mul_vector_tb_cq15(4711, 100);
    printf("Success\n");
    return 0;
}
