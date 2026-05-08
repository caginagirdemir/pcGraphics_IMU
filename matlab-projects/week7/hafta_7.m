clear all
clc
h=0;
g=9.81;
rho_f=1.20;
rho_s=418;
d=67.0e-3;
v0=50;
vfx=0.0;
vfy=0.0;
CD=0.55;
CL=0.3;
T=4;
C = 3.0*rho_f/(4.0*rho_s*d);
theta=pi/180*20;

xin=[0; h; v0*cos(theta); v0*sin(theta)];

tmaxid=(xin(4)+sqrt(xin(4)^2+2*g*xin(2)))/g;
[t1, x1] = ode45(@tennis2p, [0 tmaxid], xin);
[t2, x2] = ode45(@tennis1p, [0 tmaxid], xin);
N = max(x1(:,1));
x=0:N/100:N;
axis([0,60, 0, 60])
hold on;
plot(x, spline(x1(:,1), x1(:,2), x), '-g');
plot(x, spline(x2(:,1), x2(:,2), x), '-r');
hold off;

function xdot=tennis1p(t,x)
vr=sqrt(x(3)^2+x(4)^2);
rho_f=1.20;
rho_s=418;
d=67.0e-3;
CD=0.55;
CL=0.3;
C = 3.0*rho_f/(4.0*rho_s*d);
xdot=[x(3); x(4); +C*vr*(CD*x(3)); C*vr*(-CD*x(4))-9.81]
end

function xdot=tennis2p(t,x)
vr=sqrt(x(3)^2+x(4)^2);
rho_f=1.20;
rho_s=418;
d=67.0e-3;
CD=0.55;
CL=0.3;
C = 3.0*rho_f/(4.0*rho_s*d);
xdot=[x(3); x(4); -C*vr*(CD*x(3)); C*vr*(-CD*x(4))-9.81]
end