clc
clear
Data=importdata('Dropxy.dat');


a = 0.6/30;
time = a;
for i=2:30
    time(i)=time(i-1)+a;
end
[population2,gof] = fit(time(:),Data(:,2),'poly2');
plot(population2,time(:),Data(:,2));

for p=2:29
Data(p,3)=(Data(p+1,2)-Data(p-1,2))/(0.6/30);
end
figure(2);
population3 = fit(time(:),Data(:,3),'exp1');
plot(population3,time(1:29),Data(1:29,3));


for k=3:28
Data(k,4)=(Data(k+1,2)-2*Data(k,2)+Data(k-1,2))/(0.6/30)^2;
end
figure(3);
[population2,gof] = fit(time(:),Data(:,4),'poly2');
plot(population2,time(3:28),Data(3:28,4),'residuals');