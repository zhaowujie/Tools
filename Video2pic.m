mov=VideoReader('H:\Acer\stepbro.mp4');
numberframes=mov.NumberOfFrames;
result_path = 'H:\Acer\rader\';
if ~exist(result_path,'dir')
        mkdir(result_path);
end
for i = 1 : 999   %i从1到145
      Img=read(mov,i);    %读取第i帧      
      Img=imresize(Img,2.25,'bilinear');
      imwrite(Img,[result_path, 'img_',sprintf('%05d',i),'.jpg'])   %将第i帧写入到，"img_000i.png"图片。
      i = i + 5
end  %结束
