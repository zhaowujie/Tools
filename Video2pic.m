mov=VideoReader('H:\Acer\cum4k.18.11.13.lily.rader.creamed.by.my.stepbro.mp4');
numberframes=mov.NumberOfFrames;
result_path = 'H:\Acer\cum4k.18.11.13.lily.rader\';
if ~exist(result_path,'dir')
        mkdir(result_path);
end
for i = 1 : 999   %i��1��145
      Img=read(mov,i);    %��ȡ��i֡      
      Img=imresize(Img,2.25,'bilinear');
      imwrite(Img,[result_path, 'img_',sprintf('%05d',i),'.jpg'])   %����i֡д�뵽��"img_000i.png"ͼƬ��
      i = i + 5
end  %����