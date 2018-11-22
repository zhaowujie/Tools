% 声明视频写入器
outputVideo = VideoWriter( fullfile( 'E:\data\longmen2_result\', 'longmen2_result.avi' ) );
% 设置写入器的参数
outputVideo.FrameRate = 10;
outputVideo.Quality = 100
% 启动写入器
open( outputVideo )
% 准备图像
path=fullfile( 'E:\data\longmen2_result\longmen2_result', '*.jpg.png' )
imageNames = dir( path )
for ii = 2 : length( imageNames )
    img = imread(fullfile(  'E:\data\longmen2_result\longmen2_result\',  imageNames(ii).name ) );
    % imshow( img )
    writeVideo( outputVideo, img )  % 写入
end
% 关闭写入器，使视频生效
close(outputVideo)