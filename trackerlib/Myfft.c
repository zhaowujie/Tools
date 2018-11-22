/*
 * Myfft2.c
 *
 *  Created on: 2017-11-10
 *      Author: 208
 */


/*
 * Myfft.c
 *
 *  Created on: 2017-11-10
 *      Author: 208
 */
#include "Myfft.h"


#pragma DATA_ALIGN(W, 8);
#pragma DATA_SECTION(W,".ddr_mem");
float W[WMAX<<1];

#pragma DATA_ALIGN (brev, 8);
unsigned char brev[64] =
{
	0x00, 0x20, 0x10, 0x30, 0x08, 0x28, 0x18, 0x38,
	0x04, 0x24, 0x14, 0x34, 0x0c, 0x2c, 0x1c, 0x3c,
	0x02, 0x22, 0x12, 0x32, 0x0a, 0x2a, 0x1a, 0x3a,
	0x06, 0x26, 0x16, 0x36, 0x0e, 0x2e, 0x1e, 0x3e,
	0x01, 0x21, 0x11, 0x31, 0x09, 0x29, 0x19, 0x39,
	0x05, 0x25, 0x15, 0x35, 0x0d, 0x2d, 0x1d, 0x3d,
	0x03, 0x23, 0x13, 0x33, 0x0b, 0x2b, 0x1b, 0x3b,
	0x07, 0x27, 0x17, 0x37, 0x0f, 0x2f, 0x1f, 0x3f
};


#pragma DATA_ALIGN(temp1,8);
#pragma DATA_SECTION(temp1,".ddr_mem");
float temp1[MAXNFFT<<1];

#pragma DATA_ALIGN(temp2,8);
#pragma DATA_SECTION(temp2,".ddr_mem");
float temp2[MAXNFFT<<1];

#pragma DATA_ALIGN(temp3,8);
#pragma DATA_SECTION(temp3,".ddr_mem");
float temp3[MAXNFFT<<1];



// 产生旋转因子r_2_c
void tw_gen(float *w, int n)

{
    int i, j, k;

    double n_float=PI /n;
    for(i = 1, k = 0; i < n >> 2; i++)
    {
        w[k    ] = sin(2 *i*n_float);
        w[k + 1] = cos(2 *i*n_float);

        k += 2;
    }

    for(j = 1; j <= n >> 3; j = j << 2)
    {
        for(i = 0; i < n >> 3; i += j)
        {
            w[k]     = (float)sin( 4 *i*n_float);
            w[k + 1] = (float)cos( 4 *i*n_float);
            w[k + 2] = (float)sin( 8 *i*n_float);
            w[k + 3] = (float)cos( 8 *i*n_float);
            w[k + 4] = (float)sin(12 *i*n_float);
            w[k + 5] = (float)cos(12 *i*n_float);

            k += 6;
        }
    }
}
//产生ifft c_2_r
void tw_geni(float *w, int n)
{
    int i, j, k;
    float n_float=PI /n;
    for(i = 1, k = 0; i < n >> 2; i++)
    {
        w[k    ] =  sin (2 * i*n_float);
        w[k + 1] = -cos (2 * i*n_float);

        k += 2;
    }

    for(j = 1; j <= n >> 3; j = j << 2)
    {
        for(i = 0; i < n >> 3; i += j)
        {
            w[k]     = (float) -sin ( 4 * i*n_float);
            w[k + 1] = (float)  cos ( 4 * i*n_float);
            w[k + 2] = (float) -sin ( 8 * i*n_float);
            w[k + 3] = (float)  cos ( 8 * i*n_float);
            w[k + 4] = (float) -sin (12 * i*n_float);
            w[k + 5] = (float)  cos (12 * i*n_float);

            k += 6;
        }
    }
}


/***************************************计算复数fft的旋转因子***************************/
//产生fft c_2_c
void tw_gen_c(float *w, int n)
{

    int i, j, k;
    float n_float=PI /n;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {

            w[k]     = (float) sin (2 * i*n_float);
            w[k + 1] = (float) cos (2 * i*n_float);
            w[k + 2] = (float) sin (4 * i*n_float);
            w[k + 3] = (float) cos (4 * i*n_float);
            w[k + 4] = (float) sin (6 * i*n_float);
            w[k + 5] = (float) cos (6 * i*n_float);

            k += 6;
        }
    }
}
//产生ifft c_2_c
void tw_geni_c (float *w, int n)
{
    int i, j, k;
    float n_float=PI /n;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {

            w[k]     = (float) -sin (2 * i*n_float);
            w[k + 1] = (float)  cos (2 * i*n_float);
            w[k + 2] = (float) -sin (4 * i*n_float);
            w[k + 3] = (float)  cos (4 * i*n_float);
            w[k + 4] = (float) -sin (6 * i*n_float);
            w[k + 5] = (float)  cos (6 * i*n_float);

            k += 6;
        }
    }
}
//注意只能做N>=16的长度
void fft1D_r2c(float *src, float *dst, int size_w)
{
	unsigned char rad;
	rad=2;
	tw_gen(W, size_w);
	DSPF_sp_fftSPxSP_r2c(size_w,  src, W, dst, brev, rad, 0, size_w);
}
//注意只能做N>=8的长度
void ifft1D_c2c(float *src, float *dst, int size_w)
{

	unsigned char rad;
	rad=2;
	tw_geni_c(W, size_w);
	DSPF_sp_ifftSPxSP (size_w, src, W, dst, brev, rad, 0,size_w);
}
/****************************************************************************/
/*                                                                          */
/*              二维傅里叶正变换                                                         */
/*                                                                          */
/****************************************************************************/
void fft2D_r2c(float *src, float *dst, int size_w, int size_h)
{
	int i;
	unsigned char rad;
	rad=2;
//	if(size_w==4||size_w==16||size_w == 64 || size_w == 256||size_w == 1024)
//	{
//		rad = 4;
//	}
//	else
//	{
//		rad = 2;
//	}
	tw_gen(W, size_w);

	int size_w2=size_w<<1;

	for ( i = 0; i<size_h; i++)
	{
		DSPF_sp_fftSPxSP_r2c(size_w,  &src[size_w*i], W, &temp1[size_w2*i], brev, rad, 0, size_w);
	}
	//选择基底
//	if(size_h==4||size_h==16||size_h == 64 || size_h == 256||size_h==1024)
//	{
//		rad = 4;
//	}
//	else
//	{
//		rad = 2;
//	}
	tw_gen_c(W, size_h);

	int size_h2=size_h<<1;
	//进行复数矩阵转置，但是行与列必须是以2为底的数(原始矩阵，原矩阵的行，原矩阵的列，转换后的矩阵）
	DSPF_sp_mat_trans_cplx	(temp1, size_h, size_w, temp2);
	for (i = 0; i<size_w; i++)
	{
		DSPF_sp_fftSPxSP (size_h, &temp2[size_h2*i], W, &temp3[size_h2*i],  brev, rad, 0,size_h);
	}
	//进行复数矩阵转置，但是行与列必须是以2为底的数
	DSPF_sp_mat_trans_cplx(temp3, size_w,size_h,dst);

}
/****************************************************************************/
/*                                                                          */
/*              二维傅里叶反变换                                                         */
/*                                                                          */
/****************************************************************************/
void ifft2D_c2c(float *src, float *dst, int size_w, int size_h)
{
	int i;
	unsigned char rad;
	rad=2;
	//进行判断浪费时间所以直接用2； 比如8满足以2为底，不满足以4为底
//	if(size_h==4||size_h==16||size_h == 64 || size_h == 256||size_h==1024)
//	{
//		rad = 4;
//	}
//	else
//	{
//		rad = 2;
//	}

	tw_geni_c(W, size_h);
	DSPF_sp_mat_trans_cplx(src, size_h, size_w, temp1);

	int size_h2=size_h<<1;
	for (i = 0; i<size_w; i++)
	{
		DSPF_sp_ifftSPxSP (size_h, &temp1[size_h2*i], W, &temp2[size_h2*i], brev, rad, 0,size_h);
	}
	DSPF_sp_mat_trans_cplx(temp2, size_w,size_h, temp3);

//	if(size_w==4||size_w==16||size_w == 64 || size_w == 256||size_w == 1024)
//	{
//		rad = 4;
//	}
//	else
//	{
//		rad = 2;
//	}
	tw_geni_c(W, size_w);
	int size_w2=size_w<<1;
	for ( i = 0; i<size_h; i++)
	{
		DSPF_sp_ifftSPxSP (size_w, &temp3[size_w2*i], W, &dst[size_w2*i], brev, rad, 0, size_w);
	}

}

