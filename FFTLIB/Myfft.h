/*
 * Myfft.h
 *
 *  Created on: 2017-11-10
 *      Author: 208
 */

#ifndef MYFFT_H_
#define MYFFT_H_

#include <stdio.h>                  // C 语言标准输入输出函数库
#include <math.h>                   // C 数学函数库

#include <ti/mathlib/mathlib.h>             // DSP 数学函数库
#include <ti/dsplib/dsplib.h>                // DSP 函数库

#define PI                3.141592654
#define F_TOL             (1e-06)

//定义 MAXN最大是数据128*128 再大需要放在ddr3上
#define MAXN 65536
#define WMAX 1024

void tw_gen(float *w, int n);
void tw_geni(float *w, int n);
void tw_gen_c(float *w, int n);
void tw_geni_c (float *w, int n);
//二维fftr2c
void fft2D_r2c(float *src, float *dst, int size_w, int size_h);
//二维ifftc2c
void ifft2D_c2c(float *src, float *dst, int size_w, int size_h);

#endif /* MYFFT_H_ */
