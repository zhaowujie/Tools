#include "para.h"
void target_para_init(target_para* initpara)
{
	//david2
#if 1
	(*initpara).width = 320;
	(*initpara).height = 240;
	(*initpara).init_rect[0] = 141;
	(*initpara).init_rect[1] = 73;
	(*initpara).init_rect[2] = 27;
	(*initpara).init_rect[3] = 34;
	(*initpara).startframe = 1;
	(*initpara).endframe =30;//569;
#endif
//Deer
#if 0
	(*initpara).width = 704;
	(*initpara).height = 400;
	(*initpara).init_rect[0] = 306;
	(*initpara).init_rect[1] = 5;
	(*initpara).init_rect[2] = 95;
	(*initpara).init_rect[3] = 65;
	(*initpara).startframe = 1;
	(*initpara).endframe = 71;//
#endif

	(*initpara).target_sz[0] = (*initpara).init_rect[3];
	(*initpara).target_sz[1] = (*initpara).init_rect[2];

	(*initpara).pos[0] = (*initpara).init_rect[1] + floor((float)(*initpara).target_sz[0] / 2);
	(*initpara).pos[1] = (*initpara).init_rect[0] + floor((float)(*initpara).target_sz[1] / 2);
}

void para_init(tracker_para* initpara)//灰度的参数特征
{
	(*initpara).padding = 1;  //extra area surrounding the target
	(*initpara).lambda = 1e-2; //regularization
	(*initpara).output_sigma_factor =1.0/16.0;  //spatial bandwidth (proportional to target)//1.0/16.0取倒数
	(*initpara).interp_factor = 0.075;
	(*initpara).sigma = 0.2;//1/0.2
}

int readdata(char *fname, uint8 *im, int height, int width)
{

	FILE *fp;

	fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("can't open the bin imgae.\n ");
	}
	else
	{
		fread(im, 1, height * width, fp);
	}
	fclose(fp);
	return 0;
}
