clc,clear
syms  y x 
k=1;
b=10; %dikeyde
a=4; %yatayda
x1=-a:0.1:a;
y1=b;
y2=k*abs(x1).^3;
x3 = [-3 3];
y3 = [10 10];
line(x3,y3)
hold on
plot(x1,y2);
m=2*int((b-k*x.^3),x,0,a);
disp(m);
mx=2*int((((a+b)/3)*(b-k*x.^3)),x,0,a);
disp(mx);
yC=mx/m;
disp(yC);
plot(0,yC,'o','MarkerSize',11,'MarkerEdgeColor','k','MarkerFaceColor','r');
text(0,yC,'  C','FontSize',20);
