clear all;
mex('CXXFLAGS=\$CXXFLAGS -std=c++11 -Wall','-largeArrayDims',...  
    'private/gasonMex.cpp','../common/gason.cpp',...  
     '-I../common/','-outdir','private');  
%  在cocoapi/matlabAPI下运行，matlabAPI/cocoytils.m   line54加上文件的名字,检查哪个xml文件出问题
% 在matlabAPI/cocoytils.m    line47   修改图像文件的扩展名
% 在VOCcode/VOCinit.m   line 81 修改类别的名字
 CocoUtils.convertPascalGt( 'E:/data/jinju', '2007', 'val', 'E:/data/jinju/pascal_val2007.json')  
 CocoUtils.convertPascalGt( 'E:/data/jinju', '2007', 'trainval', 'E:/data/jinju/pascal_train2007.json') 