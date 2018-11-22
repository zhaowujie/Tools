base_path = 'E:/Trackingbag/BenchmarkOTB/';
video ='Basketball';
video_path = [base_path video '/'];
suffix = '';
%try to load ground truth from text file (Benchmark's format)
filename = [video_path 'groundtruth_rect' suffix '.txt'];
f = fopen(filename);
assert(f ~= -1, ['No initial position or ground truth to load ("' filename '").'])

%the format is [x, y, width, height]
try
    ground_truth = textscan(f, '%f,%f,%f,%f', 'ReturnOnError',false);  
catch  %#ok, try different format (no commas)
    frewind(f);
    ground_truth = textscan(f, '%f %f %f %f');  
end
ground_truth = cat(2, ground_truth{:});
fclose(f);

%set initial position and size
target_sz = [ground_truth(:,4), ground_truth(:,3)];
pos = [ground_truth(:,2), ground_truth(:,1)] + floor(target_sz/2);