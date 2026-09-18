#ifndef DSP_LECTURE_H
#define DSP_LECTURE_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <arm_acle.h>
#include <arm_neon.h>
#include <time.h>

#define N_MAX 65535

typedef struct { int16_t real,imag; } cint16_t;
typedef struct { int32_t real,imag; } cint32_t;

void mul_vector_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2);
void mul_vector_fast_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2);
void mul_vector_ref_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2);


#endif /* DSP_LECTURE_H */
