clear all;
mex('CXXFLAGS=\$CXXFLAGS -std=c++11 -Wall','-largeArrayDims',...  
    'private/gasonMex.cpp','../common/gason.cpp',...  
     '-I../common/','-outdir','private');  
%  ��cocoapi/matlabAPI�����У�matlabAPI/cocoytils.m   line54�����ļ�������,����ĸ�xml�ļ�������
% ��matlabAPI/cocoytils.m    line47   �޸�ͼ���ļ�����չ��
% ��VOCcode/VOCinit.m   line 81 �޸���������
 CocoUtils.convertPascalGt( 'E:/data/jinju', '2007', 'val', 'E:/data/jinju/pascal_val2007.json')  
 CocoUtils.convertPascalGt( 'E:/data/jinju', '2007', 'trainval', 'E:/data/jinju/pascal_train2007.json') 