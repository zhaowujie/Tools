framesPath = 'E:\data\longmen2_result\longmen2_result\';%ͼ����������·����ͬʱҪ��֤ͼ���С��ͬ  
videoName = 'E:\data\longmen2_result\longmen_result.avi';%��ʾ��Ҫ��������Ƶ�ļ�������  
fps = 30; %֡��  
startFrame = 1; %����һ֡��ʼ  
endFrame = 970; %��һ֡����  
  
if(exist('videoName','file'))  
    delete videoName.avi  
end  
  
%������Ƶ�Ĳ����趨  
aviobj=VideoWriter(videoName);  %����һ��avi��Ƶ�ļ����󣬿�ʼʱ��Ϊ��  
aviobj.FrameRate=fps;  
  
open(aviobj);%Open file for writing video data  
%����ͼƬ  
for i=startFrame:endFrame  
%     fileName=sprintf('%03d',i);    %�����ļ������� �������ļ�����0001.jpg 0002.jpg ..
    fileName=strcat(num2str(i));
        frames=imread([framesPath,fileName,'.png']);  
    writeVideo(aviobj,frames);  
end  
close(aviobj);% �رմ�����Ƶ 