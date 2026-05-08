clc,clear
syms  y x 
x1=0:0.01:1;
y1=x1.^(1/2);
y2=x1.^2;

plot(x1,y1);
hold on
plot(x1,y2);

m=int((x^(1/2)-x^2),x,0,1);
disp(m);

mx=int(((x^(1/2))^2-(x^2)^2),x,0,1)*0.5;
disp(mx);

my=int(x*((x^(1/2))-(x^2)),x,0,1);
disp(my);

xC=my/m;
yC=mx/m;

plot(xC,yC,'o','MarkerSize',11,'MarkerEdgeColor','k','MarkerFaceColor','r');
text(xC,yC,'  C','FontSize',20);
