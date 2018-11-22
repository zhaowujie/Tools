#ifndef TRACKER_H
#define TRACKER_H
#include "para.h"

void trackerInit(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara); // 第一帧训练跟踪滤波器
void tracker(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara); // 两帧之间的跟踪
void trackerUpdate(uint8 *im, float *alphaf, float *zf, target_para  *targetpara, tracker_para *trackerpara);  // 更新模板

#endif
