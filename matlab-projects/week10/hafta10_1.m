clc,clear
syms t 
a=2; k=1;
x=a*exp(k*t)*cos(t);
y=a*exp(k*t)*sin(t);
z=a*exp(k*t);

dx=diff(x,t);
dy=diff(y,t);
dz=diff(z,t);
result=(dx^2+dy^2+dz^2)^0.5;

length=int(result,0,3);
X=int(x*result,t,0,3)/length;
Y=int(y*result,t,0,3)/length;
Z=int(z*result,t,0,3)/length;

time=0:pi/100:3;
x1=a*exp(k*time).*cos(time);
y1=a*exp(k*time).*sin(time);
z1=a*exp(k*time);
plot3(x1,y1,z1);
hold on
plot3(X,Y,Z,'o','MarkerSize',11,'MarkerEdgeColor','k','MarkerFaceColor','r')
text(X,Y,Z,'   C','FontSize',20)

axis square


