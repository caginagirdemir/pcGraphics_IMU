clc,clear
syms  y x 


m=1; %e?im 1
x1=0:0.1:1;
y1=m*x1;
y2=1*x1.^2;
plot(x1,y1);
hold on
plot(x1,y2);


m=int((x-x^2),x,0,1);
disp(m);

mx=int(((x)^2-(x^2)^2),x,0,1)*0.5;
disp(mx);

my=int(x*((x)-(x^2)),x,0,1);
disp(my);

xC=my/m;
yC=mx/m;

plot(xC,yC,'o','MarkerSize',11,'MarkerEdgeColor','k','MarkerFaceColor','r');
text(xC,yC,'  C','FontSize',20);


