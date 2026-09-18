#include "dsp-lecture.h"
#include <stdio.h>

void mul_vector_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2)
{
    int i;

    cint32_t* ref = (cint32_t*)alloca(n * sizeof(cint32_t));

    mul_vector_ref_cq15(n, ref, src1, src2);

    mul_vector_fast_cq15(n, dst, src1, src2);

    for (i = 0; i < n; i++)
    {
        if (dst[i].real != ref[i].real || dst[i].imag != ref[i].imag)
        {
            fprintf(stderr, "Error at index %d: ref=(%d, %d) fast=(%d, %d)\n",
                i, ref[i].real, ref[i].imag, dst[i].real, dst[i].imag);
            exit(1);
        }
    }
}