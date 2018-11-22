/*
 * Myfft.h
 *
 *  Created on: 2017-11-10
 *      Author: 208
 */

#ifndef MYFFT_H_
#define MYFFT_H_

#include <stdio.h>                  // C ���Ա�׼�������������
#include <math.h>                   // C ��ѧ������

#include <ti/mathlib/mathlib.h>             // DSP ��ѧ������
#include <ti/dsplib/dsplib.h>                // DSP ������

#define PI                3.141592654
#define F_TOL             (1e-06)

//���� MAXN���������128*128 �ٴ���Ҫ����ddr3��
#define MAXN 65536
#define WMAX 1024

void tw_gen(float *w, int n);
void tw_geni(float *w, int n);
void tw_gen_c(float *w, int n);
void tw_geni_c (float *w, int n);
//��άfftr2c
void fft2D_r2c(float *src, float *dst, int size_w, int size_h);
//��άifftc2c
void ifft2D_c2c(float *src, float *dst, int size_w, int size_h);

#endif /* MYFFT_H_ */
