clc, clear;
%kalibre fonksiyonu
S = [ 0 80; % 1.
 0 109; % 2.
 103 72; % 3.
 103 111]; % 4.

load calib_im.txt;
I = calib_im;
x = calculate_conformal(I, S, 1);

vidObj = VideoReader('C:\ballDrop1.avi');

k=0;
while hasFrame(vidObj)
    k=k+1;
    RGB = readFrame(vidObj);
    I = rgb2gray(RGB);
bw = im2bw(I, 0.60);
bw= medfilt2(bw,[3 3]);
bw = bwareaopen(bw, 15);
imshow(bw);
    [B,L] = bwboundaries(bw,'noholes');
    stats = regionprops(L, I, 'Area', ...
'WeightedCentroid', ...
'Centroid', 'Perimeter');
        y = stats(1).Centroid;%kütle merkezi
        centroid_Data(k,1) = y(1);
        centroid_Data(k,2) = y(2);
        z = stats(1).WeightedCentroid;%agirlikli kütle merkezi  
       WeightedCentroid_Data(k,1) = z(1);
       WeightedCentroid_Data(k,2) = z(2);



end
for j=k:-1:14
    buffer = WeightedCentroid_Data(31-j,2); 
    WeightedCentroid_Data(31-j,2) = WeightedCentroid_Data(j,2); 
      WeightedCentroid_Data(j,2) = buffer;


end

for j=k:-1:14
    buffer = centroid_Data(31-j,2); 
     centroid_Data(31-j,2) = centroid_Data(j,2); 
      centroid_Data(j,2) = buffer;

end

fid = fopen('ball_drop_W_Centroid.txt', 'wt');
if fid < 0
warning('ball_drop_W_Centroid.txt dosyasi acilmadi!');
return;
end

for n=1:k
fprintf(fid, '%3.3f,%3.3f\n',  WeightedCentroid_Data(n,1),  WeightedCentroid_Data(n,2));
end
fclose(fid);0,

fid = fopen('ball_drop_Centroid.txt', 'wt');
if fid < 0
warning('ball_drop_W_Centroid.txt dosyasi acilmadi!');
return;
end

for n=1:k
fprintf(fid, '%3.3f,%3.3f\n', centroid_Data(n,1), centroid_Data(n,2));
end
fclose(fid);

load ball_drop_W_Centroid2.txt;
H = calculate_reconformal(x, ball_drop_W_Centroid2);
figure(1), plot(H(:,1),H(:,2), 'ro');axis([0 100 0 160]);axis equal;grid on;


for p=1:length(H)
if p <= 28
H(p+1,3)=(H(p+2,2)-H(p,2))/(2/30);
end
end
figure(2), plot(H(:,3),'rx');grid on;

for p=3:length(H)
if p <= 28
H(p,4)=(H(p+1,2)-2*H(p,2)+H(p-1,2))/(2/30)^2;
end
end
figure(3), plot(H(:,4),'rx');axis([0 30 -1200 200]);grid on;
