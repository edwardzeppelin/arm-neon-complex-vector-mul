#include "dsp-lecture.h"

void mul_vector_fast_cq15(int n, cint32_t* dst, cint16_t* src1, cint16_t* src2)
{
	for (int i = 0; i < n - (n % 4); i += 4) {
		int16x4x2_t src1_complex = vld2_s16((int16_t*)&src1[i]);
		int16x4x2_t src2_complex = vld2_s16((int16_t*)&src2[i]);
		int32x4_t result_real = vmlsl_s16(vmull_s16(src1_complex.val[0], src2_complex.val[0]), src1_complex.val[1], src2_complex.val[1]);
		int32x4_t result_imag = vmlal_s16(vmull_s16(src1_complex.val[0], src2_complex.val[1]), src1_complex.val[1], src2_complex.val[0]);
		dst[i].real = result_real[0];
		dst[i + 1].real = result_real[1];
		dst[i + 2].real = result_real[2];
		dst[i + 3].real = result_real[3];
		dst[i].imag = result_imag[0];
		dst[i + 1].imag = result_imag[1];
		dst[i + 2].imag = result_imag[2];
		dst[i + 3].imag = result_imag[3];
	}
	for (int i = n - (n % 4); i < n; ++i) {
		int32_t src1_real = src1[i].real;
		int32_t src1_imag = src1[i].imag;
		int32_t src2_real = src2[i].real;
		int32_t src2_imag = src2[i].imag;
		dst[i].real = src1_real * src2_real - src1_imag * src2_imag;
		dst[i].imag = src1_real * src2_imag + src1_imag * src2_real;
	}
}


