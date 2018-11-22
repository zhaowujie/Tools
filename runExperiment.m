clear;clc;close all;

% ImgPath = 'E:\InfradeSimulate\data_inf\';
% ImgPath = 'G:\dataset\������Ƶ��new_WhGuide\������Ƶ��_WhGuide\СĿ����Ƶ1\';
% ImgPath = 'G:\dataset\������Ƶ��new_WhGuide\������Ƶ��_WhGuide\��Ŀ����Ƶ\';
ImgPath = 'E:\dsp\Tracking_bag\Benchmark\';
dirF = dir(ImgPath);
PNum = size (dirF,1);
CCSResult = 'E:\workspace1\fdst_Big\Debug\';
SeqName = 'CarScale';
groundtruth_rect = load(strcat(ImgPath,SeqName,'\groundtruth_rect.txt'));
% groundtruth_rect = load(strcat(ImgPath,'7[224_229]jpg','\groundtruth_rect.txt'));

resPath = 'D:\��ҵ��Ʋ���\����\fdst�������\СĿ��\';
for i = 3 : 3

%     dirI = dir(strcat(ImgPath,SeqName,'\img\*.png')); //�������
%     dirI = dir(strcat(ImgPath,SeqName,'\imgs\*.jpg')); //�ߵº���
      dirI = dir(strcat(ImgPath,SeqName,'\img\*.jpg'));
%     dirI = dir(strcat(ImgPath,'7[224_229]jpg','\imgs\*.jpg'));
    INum = size (dirI,1);
    boxes = cell(INum,1);
    %% ���ٽ��
    ccs_rect = load(strcat(CCSResult,SeqName,'_fdst_Big.txt'));
%     ccs_rect = load(strcat(CCSResult,'9_14','_fdst_radix_small.txt'));

    color = [1 0 0];
    linewidth=1;
    figure
    for j = 2: INum
        Img = imread(strcat(ImgPath,SeqName,'\img\',dirI(j).name));
%         Img = imread(strcat(ImgPath,'7[224_229]jpg','\imgs\',dirI(j).name));        
        boxes{j} = [ccs_rect(j-1,2:3),groundtruth_rect(1,3),groundtruth_rect(1,4)];  
%         boxes{j} = [groundtruth_rect(1,1:2),groundtruth_rect(1,3),groundtruth_rect(1,4)];  

        imshow(Img)
        set(gca,'position',[0 0 1 1]);
        axis  normal
        hold on;
        rectangle('Position',boxes{j},'EdgeColor',color,'Linewidth',linewidth);
        drawnow;
        if ~exist([resPath,'\',SeqName])
            mkdir([resPath,'\',SeqName])
        end
%         imwrite(frame2im(getframe(gcf)),[resPath,'\',SeqName,'\',num2str(j),'_fdst.png'],'png');
    end
end

    

