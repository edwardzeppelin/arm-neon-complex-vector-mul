# ARM NEON Complex Vector Multiplication (16-bit to 32-bit)

Performance benchmark and verification framework for complex vector multiplication accelerated using **ARM NEON SIMD intrinsics** (`vld2_s16`, `vmlsl_s16`, and `vmlal_s16`).

## Key Features
* **Complex Arithmetic**: Computes pairwise complex vector multiplication $(a + jb) \cdot (c + jd) = (ac - bd) + j(ad + bc)$.
* **De-interleaved Vector Load**: Uses `vld2_s16` to split real and imaginary components into separate 64-bit vector registers (`int16x4x2_t`) during data loading.
* **Fused Multiply-Accumulate / Multiply-Subtract**: Calculates real components using `vmlsl_s16` ($ac - bd$) and imaginary components using `vmlal_s16` ($ad + bc$).
* **Full 32-bit Precision Output**: Expands 16-bit complex inputs (`cint16_t`) to 32-bit complex outputs (`cint32_t`) without truncation.
* **Benchmarking & Testing**: Includes automated verification testbench measuring clock cycles (`clock()`) between NEON SIMD and reference C code.

## Project Structure
* `add_vector_fast.c` — Vectorized complex multiplication using ARM NEON intrinsics (`vld2_s16`, `vmlsl_s16`, `vmlal_s16`).
* `add_vector_ref.c` — Scalar reference implementation.
* `add_vector_tb.c` — Testbench with randomized complex vector generation and performance measurement.
* `add_vector.c` — Verification wrapper layer comparing fast and reference output vectors.
* `dsp-lecture.h` — Header file defining `cint16_t`, `cint32_t` structures and function prototypes.
* `Makefile` — Build script configured for ARMv7-A NEON target (`-march=armv7-a -mfpu=neon`).

## Build & Run

```bash
make
make test
```
