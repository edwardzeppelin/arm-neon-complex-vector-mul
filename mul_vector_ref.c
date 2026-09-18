#include "dsp-lecture.h"
#include <limits.h> 

void mul_vector_ref_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2)
{
    int i;
    cint16_t* c_src1 = (cint16_t*)src1;
    cint16_t* c_src2 = (cint16_t*)src2;

    for (i = 0; i < n; i++)
    {
        int32_t a = c_src1[i].real;
        int32_t b = c_src1[i].imag;
        int32_t c = c_src2[i].real;
        int32_t d = c_src2[i].imag;

        // (a + jb) * (c + jd) = (ac - bd) + j(ad + bc)
        int32_t real_part = a * c - b * d;
        int32_t imag_part = a * d + b * c;

        dst[i].real = real_part;
        dst[i].imag = imag_part;
    }
}