% ������Ƶд����
outputVideo = VideoWriter( fullfile( 'E:\data\longmen2_result\', 'longmen2_result.avi' ) );
% ����д�����Ĳ���
outputVideo.FrameRate = 10;
outputVideo.Quality = 100
% ����д����
open( outputVideo )
% ׼��ͼ��
path=fullfile( 'E:\data\longmen2_result\longmen2_result', '*.jpg.png' )
imageNames = dir( path )
for ii = 2 : length( imageNames )
    img = imread(fullfile(  'E:\data\longmen2_result\longmen2_result\',  imageNames(ii).name ) );
    % imshow( img )
    writeVideo( outputVideo, img )  % д��
end
% �ر�д������ʹ��Ƶ��Ч
close(outputVideo)