for i=10:22
string = sprintf('C:\\nesneler_%d.jpg', i);
RGB = imread(string);
I = rgb2gray(RGB);
threshold = graythresh(I);
bw = im2bw(I,threshold);
bw = bwareaopen(bw,50);
bw = bwareafilt(bw,[70 200]);
[B,L]=bwboundaries(bw,'noholes');
LRGB=label2rgb(L, @jet, [.5 .5 .5]);
figure,imshow(LRGB)
hold on
ratioLow = 0.85;
ratioUp = 1.15;
for k = 1:length(B)
boundary = B{k};
stats = regionprops(L,'Area','Centroid','Perimeter');
perimeter = stats(k).Perimeter;
area = stats(k).Area;
ratio = 4*pi*area / perimeter^2;
ratio_string = sprintf('%2.2f', ratio);
if (ratio >= ratioLow) && (ratio <= ratioUp)
centroid = stats(k).Centroid;
 plot(centroid(1), centroid(2),'ko');
 text(centroid(1) - 15, centroid(2) + 5,ratio_string,'Color','y','FontSize',14,'FontWeight','bold');
end
end
end
