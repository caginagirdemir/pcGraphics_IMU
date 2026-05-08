RGB = imread('C:\\nesneler_1.jpg');
I = rgb2gray(RGB);
threshold = graythresh(I);
BW = im2bw(I,threshold);
BW = bwareaopen(BW,50);
BW = bwareafilt(BW,[70 200]);
[centers, radii, metric] = imfindcircles(BW,[1 30]);
imshow(BW);
hold on
plot(centers(:,1),centers(:,2),'r+')
