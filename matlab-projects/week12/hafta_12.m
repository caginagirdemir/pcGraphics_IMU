clear all
clc
m = 0.5; % kg
g = 9.8; % m/sˆ2
h0 = 4.0; % m
L = 1.0; % m
time = 10.0; % s
dt = 0.001; % s
k = 1000.0; % N/m
v0 = 2.0; % m/s
I = (1.0/12.0)*m*L^2;
n = ceil(time/dt);
r = zeros(n,3);
v = zeros(n,3);
theta = zeros(n,1);
omega = zeros(n,1);
velocity = zeros(n,1);
t = zeros(n,1);
r(1,:) = [0 h0 0];
v(1,:) = [v0 0 0];
theta(1) = 2*pi*rand(1);
for i = 1:n-1

fnet = [0 0 0];
tnet = 0.0;
u = [cos(theta(i)) sin(theta(i)) 0];
rr = r(i,:) + 0.5*L*u;
% Collision with bottom wall
dr = rr(2);
f = -k*dr*(dr<0.0)*[0 1 0];
fnet = fnet + f;
torque = cross((rr-r(i,:)),f);
tnet = tnet + torque;
% Position of edge B
rr = r(i,:) - 0.5*L*u;
% Collision with bottom wall
dr = rr(2);
f = -k*dr*(dr<0.0)*[0 1 0];
fnet = fnet + f;
torque = cross((rr-r(i,:)),f);
tnet = tnet + torque;
% Add gravity
fnet = fnet - m*g*[0 1 0];
a = fnet/m;
v(i+1,:) = v(i,:) + a*dt;
r(i+1,:) = r(i,:) + v(i+1,:)*dt;
knet(i+1,:) = 0.5*m*(v(i,:).^2);
PE(i+1,:)=0.5*k*((dr*(dr<0.0)*[1 1 0]).^2);

alphaz = tnet(3)/I;
omega(i+1) = omega(i) + alphaz*dt;
theta(i+1) = theta(i) + omega(i+1)*dt;

t(i+1) = t(i) + dt;


if (mod(i,20)==0)
r1 = r(i,:) + 0.5*L*u;
r2 = r(i,:) - 0.5*L*u;
xl = [r1(1) r2(1)];
yl = [r1(2) r2(2)];
figure(1);
plot(r(1:i,1),r(1:i,2),':',xl,yl,'-');

xlabel('x [m]');
ylabel('y [m]');
axis equal
axis([0 time*v0 0 h0]);

drawnow
end
end

figure(2);
%Kinetic Energy due to angular movement
axis([0 10000 0 20]);
plot(omega);

figure(3);
%Kinetic Energy due to linear movement
axis([0 10000 0 20]);
plot(knet(:,2));

figure(4);
%Potential Energy due to gravity
axis([0 10000 0 20]);
plot(r(:,2));

figure(5);
%Potential Energy due to spring force
axis([0 10000 0 20]);
plot(PE(:,2));
