%marker siralama
clc, clear;
vidObj = VideoReader('C:\Users\Cagin\salto.avi');
k=1;
aviobj = VideoWriter('jump.avi', 'Uncompressed AVI');
aviobj.FrameRate = 25;
open(aviobj);
d = 0;
missing_marker_flag = 0;
while hasFrame(vidObj)
k=k+1;
max = 7;

RGB = readFrame(vidObj);
if k>3 %degerleri 3.frameden sonra kontrol etmektedir.
I = rgb2gray(RGB);
[level EM] = graythresh(I);
bw = im2bw(I,EM);
figure; imshow(bw)
hold on
cg = regionprops(bw, 'centroid');
cg_centroids = cat(1, cg.Centroid);
cg_centroids= sortrows(cg_centroids,2);
marker_num = size(cg_centroids);
if marker_num < 7
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



if k>=2
for j=1:7
    for p=1:7
         x = [centroids_data(j,1,k-1) centroids_data(j,2,k-1)];
         y = [centroids_data(p,1,k) centroids_data(p,2,k)];
         distances(j,p,k-1) = norm(x-y);
         d = diag(distances(:,:,k-1));
    end
end
if marker_num(1) >= 7
if missing_marker_flag == 0
for n=1:max
    if d(n) > 20
        for t=1:max
         if distances(t,n,k-1) < d(n)
             flow_X = cg_centroids(n,1);
             flow_Y = cg_centroids(n,2);
             cg_centroids(n,1) = cg_centroids(t,1);
             cg_centroids(n,2) = cg_centroids(t,2);
             cg_centroids(t,1) = flow_X;
             cg_centroids(t,2) = flow_Y;
centroids_data(:,1,k) = cg_centroids(:,1);
centroids_data(:,2,k) = cg_centroids(:,2);

for j=1:7
    for p=1:7
         x = [centroids_data(j,1,k-1) centroids_data(j,2,k-1)];
         y = [centroids_data(p,1,k) centroids_data(p,2,k)];
         distances(j,p,k-1) = norm(x-y);
         d = diag(distances(:,:,k-1));
    end
end
         end
         end  
       end
end 
renk = 'ygbmcrw';
for i = 1 : max
 text(cg_centroids(i,1) + 50, ...
 cg_centroids(i,2), ...
 sprintf('%3.3f,%3.3f', ...
 cg_centroids(i,1), ...
 cg_centroids(i,2)), ...
 'Color', renk(i), 'FontSize',12);
end
else
missing_marker_flag = 0; 
end
else
missing_marker_flag = 1;
end



end
if k==31 %breakpoint koyarak frame yakalamak için if
end
close
close(aviobj);
end
end

