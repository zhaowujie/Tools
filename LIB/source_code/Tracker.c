#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "para.h"
#include "Tracker.h"

/************************************************************************/
/*                     定义数据                                                                      */
/************************************************************************/
/************************************************************************/
/*                     定义数据                                                                      */
/************************************************************************/



#pragma DATA_ALIGN(img, 8);
#pragma DATA_SECTION(img,".ddr_mem");
float  img[Mpatch*Mpatch];

#pragma DATA_ALIGN( xs, 8);
#pragma DATA_SECTION( xs,".ddr_mem");
int  xs[Mpatch];

#pragma DATA_ALIGN( ys, 8);
#pragma DATA_SECTION(ys,".ddr_mem");
int  ys[Mpatch];

#pragma DATA_ALIGN(patch, 8);
#pragma DATA_SECTION(patch,".ddr_mem");
uint8  patch[Mpatch*Mpatch];


#pragma DATA_ALIGN(tmp, 8);
#pragma DATA_SECTION(tmp,".ddr_mem");
float  tmp[Mpatch*Mpatch];

#pragma DATA_ALIGN(xyf, 8);
#pragma DATA_SECTION(xyf,".ddr_mem");
float  xyf[2*Mpatch*Mpatch];

#pragma DATA_ALIGN(xyf_temp1, 8);
#pragma DATA_SECTION(xyf_temp1,".ddr_mem");
float  xyf_temp1[2*Mpatch*Mpatch];



//
#pragma DATA_ALIGN(xyf_temp2, 8);
#pragma DATA_SECTION(xyf_temp2,".ddr_mem");
float  xyf_temp2[Mpatch*Mpatch];

#pragma DATA_ALIGN(xy, 8);
#pragma DATA_SECTION(xy,".ddr_mem");
float  xy[Mpatch*Mpatch];


#pragma DATA_ALIGN(xyf_temp2, 8);
#pragma DATA_SECTION(xyf_temp2,".ddr_mem");
float  xyf_temp2[Mpatch*Mpatch];


#pragma DATA_ALIGN(xy, 8);
#pragma DATA_SECTION(xy,".ddr_mem");
float  xy[Mpatch*Mpatch];




#pragma DATA_ALIGN(k, 8);
#pragma DATA_SECTION(k,".ddr_mem");
float  k[Mpatch*Mpatch];


#pragma DATA_SECTION(trackerpara,".ddr_mem");
tracker_para  trackerpara;

#pragma DATA_SECTION(targetpara,".ddr_mem");
target_para targetpara;

#pragma DATA_ALIGN(y, 8);
#pragma DATA_SECTION(y,".ddr_mem");
float y[Mpatch*Mpatch];

#pragma DATA_ALIGN(yf, 8);
#pragma DATA_SECTION(yf,".ddr_mem");
float yf[2*Mpatch*Mpatch];

#pragma DATA_ALIGN(han0, 8);
#pragma DATA_SECTION(han0,".ddr_mem");
float han0[Mpatch];

#pragma DATA_ALIGN(han1, 8);
#pragma DATA_SECTION(han1,".ddr_mem");
float han1[Mpatch];

#pragma DATA_ALIGN(cos_window, 8);
#pragma DATA_SECTION(cos_window,".ddr_mem");
float cos_window[Mpatch*Mpatch];


#pragma DATA_ALIGN(x, 8);
#pragma DATA_SECTION(x,".ddr_mem");
float x[Mpatch*Mpatch];

#pragma DATA_ALIGN(xf, 8);
#pragma DATA_SECTION(xf,".ddr_mem");
float xf[2*Mpatch*Mpatch];

#pragma DATA_ALIGN(kf, 8);
#pragma DATA_SECTION(kf,".ddr_mem");
float kf[2*Mpatch*Mpatch];


#pragma DATA_ALIGN(z, 8);
#pragma DATA_SECTION(z,".ddr_mem");
float z[Mpatch*Mpatch];


#pragma DATA_ALIGN(new_alphaf, 8);
#pragma DATA_SECTION(new_alphaf,".ddr_mem");
float new_alphaf[2*Mpatch*Mpatch];


#pragma DATA_ALIGN(new_z, 8);
#pragma DATA_SECTION(new_z,".ddr_mem");
float new_z[Mpatch*Mpatch];

#pragma DATA_ALIGN(response_temp1, 8);
#pragma DATA_SECTION(response_temp1,".ddr_mem");
float response_temp1[2*Mpatch*Mpatch];

#pragma DATA_ALIGN(response_temp2, 8);
#pragma DATA_SECTION(response_temp2,".ddr_mem");
float response_temp2[2*Mpatch*Mpatch];

#pragma DATA_ALIGN(response, 8);
#pragma DATA_SECTION(response,".ddr_mem");
float response[Mpatch*Mpatch];

#pragma DATA_ALIGN(kf_real, 8);
#pragma DATA_SECTION(kf_real,".ddr_mem");
float kf_real[Mpatch*Mpatch];
//函数声明
void gaussian_shaped_labels(float sigma,int* sz,float*labels);
void hann(int length,float *out);
void get_subwindow(uint8* im, float* pos, int height, int width, int *sz, float* cos_window, float* feat);
void circshift(float * in, float *out, int*sz, int x, int y);
void dense_gauss_kernel(float *xf, float*yf, int *sz, float sigma, float *kf);
void linear_correlation(float *xf, float *yf, int *sz, float *xyfsum);
//全局
int i,j, frame,sz[2]={4,4};
float output_sigma;
float  pos[2];
int   height, width,dim, row, col;
float tmpwh1,  tmpwh2,  tmpwh3, tmpwh4;
float factor;
int windowSize ;
int  window_2;
void trackerInit(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara) // 第一帧训练跟踪滤波器
{

	//frame number

	height = (*targetpara).height;
	width =(*targetpara).width;
	pos[0] = (*targetpara).pos[0];
	pos[1] = (*targetpara).pos[1];

	while(sz[0] < (*targetpara).target_sz[0] * (1 + (*trackerpara).padding))
	{
		sz[0]=sz[0]<<1;
	}
	while(sz[1] < (*targetpara).target_sz[1] * (1 + (*trackerpara).padding))
	{
		sz[1]=sz[1]<<1;
	}

	output_sigma = sqrtsp((*targetpara).target_sz[0]* (*targetpara).target_sz[1]) * (*trackerpara).output_sigma_factor;

	windowSize = sz[0]*sz[1];
	window_2= windowSize<<1;

	gaussian_shaped_labels(output_sigma, sz, y);


	fft2D_r2c(y, yf, sz[1],sz[0]);

	 //////////////////////用于流水线优化的中间变量///////////////

	int tmpCos1,tmpCos2;
	////////////////////////////////////////////////////////////

	hann(sz[0],han0);
	hann(sz[1],han1);

	for (i = 0; i < sz[0]; i++)
	{
		for (j = 0; j < sz[1]; j++)
		{
			tmpwh1 = han0[i] * han1[j];
			tmpCos1 = i*sz[1];
			tmpCos2 = tmpCos1+ j;
			cos_window[tmpCos2] =tmpwh1 ;
		}
	}


	//预处理结束---------------------------------------------------------------------
	get_subwindow(im, pos, height, width, sz, cos_window, x);

	////////////////////////////做FFT正变换得到频域特征////////////////////

	fft2D_r2c(x, xf, sz[1],sz[0]);
/////////////////////////////////////做高斯自相关进行初始化模型///////////////////////////////
//	dense_gauss_kernel(xf, xf, sz, (*trackerpara).sigma, kf);
	#if MOSSE
		linear_correlation(xf, xf, sz, kf);
	#endif
	#if (!MOSSE)
		dense_gauss_kernel(xf, xf, sz,  (*trackerpara).sigma,  kf);
	#endif
	////////////////////////////////////做自相关结束///////////////////////////////

	for (i = 0; i < window_2;)
	{
		kf[i] += (*trackerpara).lambda;
		tmpwh1=1.0/(kf[i]*kf[i]+kf[i+1]*kf[i+1]);

		tmpwh2=yf[i] * kf[i] + yf[i+1] * kf[i+1];
		tmpwh3=yf[i+1] * kf[i] - yf[i] * kf[i+1];
		new_alphaf[i] = tmpwh2*tmpwh1;
		new_alphaf[i+1] = tmpwh3*tmpwh1;
		i++;
		i++;
	}
	memcpy(zf, xf, window_2* sizeof(float));
	memcpy(alphaf, new_alphaf, window_2* sizeof(float));
	(*targetpara).pos[0]=pos[0];
	(*targetpara).pos[1]=pos[1];



}

void tracker(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara) // 两帧之间的跟踪
{
	factor = (*trackerpara).interp_factor;
	height = (*targetpara).height;
	width =(*targetpara).width;

	pos[0] = (*targetpara).pos[0];
	pos[1] = (*targetpara).pos[1];
	get_subwindow(im, pos, height, width, sz, cos_window, x);
///////////////////做FFT变换/////////////////////////////////////
	fft2D_r2c(x, xf, sz[1],sz[0]);

/////////////////////////////////////做高斯互相关得到第二帧位置/////////////////////////////////

	#if MOSSE
		linear_correlation(xf, zf, sz, kf);
	#endif
	#if (!MOSSE)
		dense_gauss_kernel(xf, zf, sz,  (*trackerpara).sigma,  kf);
	#endif
/////////////////////////////////////////////////////////////////////////
   //复数相乘
	for (i = 0; i < window_2; )
	{
		tmpwh1 = alphaf[i] * kf[i];
		tmpwh2 = alphaf[i+1] * kf[i+1];
		tmpwh3 = alphaf[i] *  kf[i+1];
		tmpwh4 = alphaf[i+1] * kf[i];
		response_temp1[i] = tmpwh1-tmpwh2 ;
		response_temp1[i+1] = tmpwh3+tmpwh4;
		i++;
		i++;

	}

//////////////////////////////做ifft/////////////////////////////////
	ifft2D_c2c(response_temp1, response_temp2, sz[1], sz[0]);

	 for(i =0 ; i<windowSize; i++)
	 {
		 response[i] = response_temp2[2*i];//取实部
	 }
	int ny=0;
	ny = DSPF_sp_maxidx(response, windowSize);
	row = ny /  sz[1]+1; //
	col = fmodf(ny, sz[1])+1;   //

	pos[0] = pos[0]-floor(sz[0]>>1)+ row; //这里与mosse不一样
	pos[1] = pos[1]-floor(sz[1]>>1)+ col; //这里与mosse不一样
	(*targetpara).pos[0]=pos[0];
	(*targetpara).pos[1]=pos[1];

}
void trackerUpdate(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara)  // 更新模板
{
/************************模型更新**********************************/
	factor = (*trackerpara).interp_factor;
	height = (*targetpara).height;
	width =(*targetpara).width;

	pos[0] = (*targetpara).pos[0];
	pos[1] = (*targetpara).pos[1];
	get_subwindow(im, pos, height, width, sz, cos_window, x);
	fft2D_r2c(x, xf, sz[1],sz[0]);

	#if MOSSE
		linear_correlation(xf, xf, sz, kf);
	#endif
	#if (!MOSSE)
		dense_gauss_kernel(xf, xf, sz,  (*trackerpara).sigma,  kf);
	#endif

	float sq_factor= 1 -  (*trackerpara).interp_factor;
	for (i = 0;  i < window_2; )
	{
		kf[i] += (*trackerpara).lambda;
		tmpwh1=1.0/(kf[i]*kf[i]+kf[i+1]*kf[i+1]);
		tmpwh2=yf[i] * kf[i] + yf[i+1] * kf[i+1];
		tmpwh3=yf[i+1] * kf[i] - yf[i] * kf[i+1];
		new_alphaf[i] = tmpwh2*tmpwh1;
		new_alphaf[i+1] = tmpwh3*tmpwh1;
		alphaf[i] =sq_factor* alphaf[i] +factor* new_alphaf[i];
		alphaf[i+1] = sq_factor * alphaf[i+1] + factor* new_alphaf[i+1];
		zf[i] =sq_factor * zf[i] + factor * xf[i];
		zf[i+1] =sq_factor * zf[i+1] + factor * xf[i+1];
		i++;
		i++;
	}
}


void gaussian_shaped_labels(float sigma, int* sz, float*labels)
{
	int i, j;
	int tmp1 = sz[0] >> 1;//(int)floor((float)sz[0] / 2)
	int tmp2 = sz[1] >> 1;//(int)floor((float)sz[1] / 2)
	float sigma2 = -0.5/(sigma*sigma);
	int dist;
	int sqtemp1,sqtemp2,sqtemp3;
	int position;
	//evaluate a Gaussian with the peak at the center element
	sqtemp1=tmp1 - 1;
	sqtemp2=tmp2 - 1;
	sqtemp3=sqtemp1*sz[1];
	for (i = -sqtemp1; i <= tmp1; i++)
	{
		for (j = -sqtemp2; j <= tmp2; j++)
		{
			dist =i*i + j*j;
			position=sqtemp3+i*sz[1]+j +sqtemp2;
			labels[position] = expsp(sigma2 *dist );//-0.5 / (sigma*sigma)
		}
	}

}

void hann(int length, float *out)
{
	int i;
	float n = 2 * PI / (length - 1);
	for (i = 0; i<length; i+=2)
	{
		out[i] = 0.5*(1 - cossp(n*i));
		out[i+1] = 0.5*(1 - cossp(n*(i+1)));
	}
}

void get_subwindow(uint8* im, float* pos, int height, int width, int *sz, float* cos_window, float* feat)
{
	int i, j;


	int tmp1 = sz[0] >> 1;
	int tmp2 = sz[1] >> 1;
	for (i = 0; i<sz[0]; i++)
	{
		xs[i] = floor(pos[0]) + i - tmp1;
		if (xs[i]<0)
			xs[i] = 0;
		else if (xs[i]>(height - 1))
			xs[i] = height - 1;
	}
	for (i = 0; i<sz[1]; i++)
	{
		ys[i] = floor(pos[1]) + i - tmp2;
		if (ys[i]<0)
			ys[i] = 0;
		else if (ys[i]>(width - 1))
			ys[i] = width - 1;
	}
	////////////////////////////中间变量/////////////////////////

	 int temp1,temp2,temp3;

	for (i = 0; i < sz[0]; i++)
	{
		for (j = 0; j < sz[1]; j++)
		{
			temp1=xs[i] * width;
			temp2=temp1+ys[j];
			temp3=i*sz[1] + j;
			patch[temp3] = im[temp2];
		}
	}


	float temop=1.0/255.0;

	for (i = 0; i<sz[0] * sz[1]; i++)
	{
		img[i]=(float)patch[i] *temop-0.5;
	}
	for (i = 0; i<sz[0] * sz[1]; i++)
	{
		feat[i]  =img[i] *cos_window[i];
	}



}
void circshift(float * in, float *out, int*sz, int x, int y)
{
	int i, j;
	if (x >= 0)
	{
		int sqtemp1,sqtemp2;

		sqtemp1= sz[0]*sz[1];
		sqtemp2=x*sz[1];

		for (i = 0; i < sqtemp2; i++)
		{
			tmp[i]= in[sqtemp1-sqtemp2 + i];
		}
		for (i = 0; i < (sqtemp1-sqtemp2); i++)
		{
			tmp[i + sqtemp2] = in[i];
		}
	}
	else
	{
		x = -x;
		int sqtemp1,sqtemp2,sqtemp3;
		sqtemp1= sz[0]*sz[1];
		sqtemp2=x*sz[1];
		sqtemp3=sqtemp1-sqtemp2;

		for (i = 0; i <sqtemp3; i++)
		{
			tmp[i] = in[sqtemp2 + i];
		}
		for (i = 0; i < sqtemp2; i++)
		{
			tmp[i + sqtemp3] = in[i];
		}


	}
	if (y >= 0)
	{
		int  sqtemp4;
		sqtemp4=sz[1] - y;
		for (i = 0; i<sz[0]; i++)
		{
			for (j = 0; j < y; j++)
			{
				out[i*sz[1] + j] = tmp[i*sz[1] + j + sqtemp4];
			}
			for (j = 0; j < sqtemp4; j++)
			{
				out[i*sz[1] + y + j] = tmp[i*sz[1] + j];
			}
		}
	}
	else
	{
		y = -y;
		//left
		int  sqtemp4;
		sqtemp4=sz[1] - y;
		for (i = 0; i<sz[0]; i++)
		{
			for (j = 0; j <sqtemp4 ; j++)
			{
				out[i*sz[1] + j] = tmp[i*sz[1] + j + y];
			}
			for (j = 0; j < y; j++)
			{
				out[i*sz[1] + sqtemp4+ j] = tmp[i*sz[1] + j];
			}
		}
	}

}
void dense_gauss_kernel(float *xf, float*yf, int *sz, float sigma, float *kf)
{
	float tmpwh1,  tmpwh2,  tmpwh3, tmpwh4,sqtemp1;

	int i;

	int temp1,temp2;
	temp1 = sz[0]>>1;
	temp2 = sz[1]>>1;

	int  windowSize,window_2;
	windowSize=sz[0]*sz[1];
	window_2=windowSize<<1;


	float yy = 0,xx = 0,ss=0;
    //复数求模
	for(i=0; i < window_2;)
	{
		tmpwh1=xf[i] * xf[i];
		tmpwh2=xf[i+1] * xf[i+1];
		tmpwh3=yf[i ] * yf[i];
		tmpwh4=yf[i+1] * yf[i+1];
		xx += (tmpwh1  + tmpwh2);
		yy += (tmpwh3  +  tmpwh4);
		i++;
		i++;
	}

	xx /= windowSize;
	yy /= windowSize;
	//复数共轭相乘c_mul_conjugate(xf[i], yf[i], &xyf[i]);
	for (i = 0; i<window_2;)
	{
		tmpwh1=xf[i] * yf[i];
		tmpwh2=xf[i+1] * yf[i+1];
		tmpwh3=xf[i+1] * yf[i] ;
		tmpwh4=xf[i] * yf[i+1];
		xyf[i] = tmpwh1 +tmpwh2 ;
		xyf[i+1] = tmpwh3 -tmpwh4 ;
		i++;
		i++;
	}

	ifft2D_c2c(xyf, xyf_temp1, sz[1],sz[0]);


	for(i=0;i<windowSize;i++)
	{
		xyf_temp2[i] = xyf_temp1[2*i];

	}

	circshift(xyf_temp2, xy, sz,temp1, temp2);


	ss = xx + yy;
	float windowSize_temp=1.0 /windowSize;

	sqtemp1=ss*windowSize_temp;
	float sigma2 = -1.0/(sigma*sigma);
	for (i = 0; i<windowSize; i++)
	{
		k[i] = expsp(sigma2 * MAX(0, sqtemp1 - 2*xy[i] *windowSize_temp));
	}

	fft2D_r2c(k, kf,sz[1],  sz[0]);

}

void linear_correlation(float *xf, float *yf, int *sz, float *xyfsum)
{
	int i;
	int N = sz[0]*sz[1];
	memset(xyfsum, 0, 2 * N * sizeof(float));

	for (i = 0; i<N; i++)
	{
		//c_mul_conjugate(xf[i], yf[i], &xyf[i]);
		xyf[2*i] = xf[2*i]*yf[2*i] + xf[2*i+1]*yf[2*i+1];
	    xyf[2*i+1] = xf[2*i+1]*yf[2*i] - xf[2*i]*yf[2*i+1];
	}
    float N_temp=recipsp((float)N);
	for (i = 0; i<N*2; i++)
	{
		xyfsum[i] = xyf[i]*N_temp;//为什么要除以N
	}
}
