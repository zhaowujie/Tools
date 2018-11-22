#ifndef PARA_H
#define PARA_H
#include "Myfft.h"
#include <ti/mathlib/mathlib.h>
#include <ti/dsplib/dsplib.h>
// small value, used to avoid division by zero
#define eps0 0.00001

#define N_im  768  //放图像的宽或高
#define MOSSE  0   //1 是MOSSE，0是CSK

#define Interval  2   //模板更新频率，每interval更新一次，工程需要

#define Mpatch 512  //放图像块的宽或高

#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)>(b)?(b):(a))

typedef unsigned char uint8;

typedef struct tracker_para
{
		float padding;
		float lambda;
		float output_sigma_factor;
		float interp_factor;
		float sigma ;

}tracker_para;

typedef struct target_para{
	int width;
	int height;
	int dim;
	float init_rect[4];
	float target_sz[2];
	float pos[2];
	int startframe;
	int endframe;
}target_para;

int readdata(char *fname, uint8 *im, int height, int width);
void para_init(tracker_para* initpara);
void target_para_init(target_para* initpara);

#endif
