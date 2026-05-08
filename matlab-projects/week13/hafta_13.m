clear all
clc

g=9.81;
d=0.063;
m=0.05;
rho=1.29;
h=1;
v0=25;
theta=pi/180*15;



x_init=[0; h; v0*cos(theta); v0*sin(theta)];
tmax=(x_init (4)+sqrt(x_init (4)^2+2*g*x_init (2)))/g;



[t_i, x_i] = ode45(@n_vacumm, [0 tmax],x_init);
[t0, x0] = ode45(@without_spin, [0 tmax],x_init);
[t1, x1] = ode45(@top_spin, [0 tmax], x_init);
[t2, x2] = ode45(@back_spin, [0 tmax], x_init);


N = max(x_i(:,1));
x=0:N/100:N;
axis([0,max(x_i(:,1)), 0, max(x_i(:,2))])
hold on;
plot(x, spline(x_i(:,1), x_i(:, 2),x), '--black');
plot(x, spline(x0(:,1), x0(:,2), x), '-r');
plot(x, spline(x1(:,1), x1(:,2), x), '-g');
 
plot(x, spline(x2(:,1), x2(:,2), x), '-b');
legend('in vacuum','without spin','top spin','back spin')
hold off;




function x_return= n_vacumm (t,x,flag)
x_return = [x(3); x(4); 0; -9.81]
end


function x_return = without_spin (t,x)
v=sqrt(x(3)^2+x(4)^2);
x_return = [x(3); x(4); -0.040212464505766*0.508*x(3)*v; -9.81-0.040212464505766*0.508*x(4)*v]
end

function x_return = top_spin (t,x)
v=sqrt(x(3)^2+x(4)^2);
Cd=(0.508+1/(22.503+4.196*(v/20)^0.4))*0.040212464505766*v;
Cm=1*20/(2.022*20+0.981*v)*0.040212464505766*v
x_return =[x(3); x(4); -Cd*x(3)+Cm*x(4); -9.81-Cd*x(4)-Cm*x(3)]
end


function x_return = back_spin (t,x)
v=sqrt(x(3)^2+x(4)^2);
Cd=(0.508+1/(22.503+4.196*(v/20)^0.4))*0.040212464505766*v;
Cm=1*20/(2.022*20+0.981*v)*0.040212464505766*v
x_return =[x(3); x(4); +Cd*x(3)+Cm*x(4); -9.81+Cd*x(4)-Cm*x(3)]
end


