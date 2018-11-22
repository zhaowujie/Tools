#ifndef TRACKER_H
#define TRACKER_H
#include "para.h"

void trackerInit(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara); // ��һ֡ѵ�������˲���
void tracker(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara); // ��֮֡��ĸ���
void trackerUpdate(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara);  // ����ģ��

#endif
