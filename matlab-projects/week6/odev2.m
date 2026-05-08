% James Adams 3/4/14
% =========================================================================
function LotkaVolterra_JA
clear  % Clears command window
clc    % Clears command history
clf    % Removes anything in the figure window before simulation. 
% =============== Set choice to 1 or 2 ==================================== 
choice = 2;  
countdown = 5;  % Countdown time length before simulation runs. 
iterations = 1;  % Sets initial interation count to 1;
pausetime = 0.1;  % Shows solutions at each time step. 
runtime = 0.0005;    % Duration time of simulation.
% =============== Initial conditions for x and y ==========================
initialx = 10000;
initialy = 5000;


deq1=@(t,x) [x(1)*(2 - 12/10*x(2)); -x(2)*(1-12/10*x(1))];
[t,sol] = ode45(deq1,[0 runtime],[initialx initialy]);
arraysize = size(t);  % Sets time array size for the for loop.

for i = 1 : max(arraysize) 
    subplot(2,1,1)
    plot(sol(iterations,1),sol(iterations,2),'.','color',[rand; rand; rand],'markersize',14,'MarkerFaceColor','b');                               
    hold on
    title(['Lotka-Volterra Equations       t = ' num2str(t(iterations))],'fontsize',12)
    xlabel('x','fontsize',12)
    ylabel('y','fontsize',12)
    axis([min(sol(:,1)) max(sol(:,1)) min(sol(:,2)) max(sol(:,2))])
    
    subplot(2,1,2)
    text(0.1,0.5,'Time Series graph will be shown at the end of the simulation')
    
    iterations = iterations + 1;   % Adds 1 to the iteration count. 
    pause(pausetime)
end
% ==== Plots time series of x or y graph depending on choice ============== 
subplot(2,1,2)
    plot(t(:,1),sol(:,1),'b-','markersize',10,'MarkerFaceColor','b')
    title(['Lotka-Volterra time series for x        run time = ' num2str(max(t)) ' seconds '],'fontsize',12)
    xlabel('t')
    ylabel('x')
    axis([min(t(:,1)) max(t(:,1)) min(sol(:,1)) max(sol(:,1))])
    hold on
    title(['Lotka-Volterra time series for y        run time = ' num2str(max(t)) ' seconds '],'fontsize',12)
    subplot(2,1,2)
    plot(t(:,1),sol(:,2),'r-','markersize',10,'MarkerFaceColor','b')
    title(['Lotka-Volterra time series for y        run time = ' num2str(max(t)) ' seconds '],'fontsize',12)
    xlabel('t')
    ylabel('x')
    axis([min(t(:,1)) max(t(:,1)) min(sol(:,2)) max(sol(:,2))])
