clc, clear;
vidObj = VideoReader('C:\Users\Cagin\salto.avi');
k=0;

d = 0;

while hasFrame(vidObj)
k=k+1;
max = 7;

RGB = readFrame(vidObj);
I = rgb2gray(RGB);
[level EM] = graythresh(I);
bw = im2bw(I,EM);
figure; imshow(bw)
hold on
cg = regionprops(bw, 'centroid');
cg_centroids = cat(1, cg.Centroid);
cg_centroids= sortrows(cg_centroids,2);

marker_num = size(cg_centroids);

if marker_num < 7 %lost marker tracking control
centroids_data(1,1,k) = cg_centroids(1,1);
centroids_data(1,2,k) = cg_centroids(1,2);
centroids_data(2,1,k) = cg_centroids(2,1);
centroids_data(2,2,k) = cg_centroids(2,2);
centroids_data(3,1,k) = cg_centroids(3,1);
centroids_data(3,2,k) = cg_centroids(3,2);
centroids_data(4,1,k) = cg_centroids(4,1);
centroids_data(4,2,k) = cg_centroids(4,2);
centroids_data(5,1,k) = cg_centroids(5,1);
centroids_data(5,2,k) = cg_centroids(5,2);
centroids_data(6,1,k) = cg_centroids(6,1);
centroids_data(6,2,k) = cg_centroids(6,2);
centroids_data(7,1,k) = 0;
centroids_data(7,2,k) = 0;
max=6;
else
centroids_data(:,1,k) = cg_centroids(:,1);
centroids_data(:,2,k) = cg_centroids(:,2);
end



if marker_num < 7
for j=1:5
         x = [centroids_data(j,1,k) centroids_data(j,2,k)];
         y = [centroids_data(j+1,1,k) centroids_data(j+1,2,k)];
         tddistances(k,j) = norm(x-y);
end

for p=1:5
        if tddistances(k,p) < tddistances(k-1,p) + tddistances(k-1,p+1) + 10 && tddistances(k,p) > tddistances(k-1,p) + tddistances(k-1,p+1) - 10 
        disp(k);
        disp (p);
        disp (p+1);
        end
end
else
for i=1:6
         x = [centroids_data(i,1,k) centroids_data(i,2,k)];
         y = [centroids_data(i+1,1,k) centroids_data(i+1,2,k)];
         tddistances(k,i) = norm(x-y);
end 
end

close

end

