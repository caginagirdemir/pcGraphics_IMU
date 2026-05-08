clc 
clear all

tank1(1,1)=80; %water litres
tank1(1,2)=0;%salt litres
tank1(1,3)=0;%salt rate
tank1(1,4)=1;%water rate

t=1;
tank1_in_fluid  = 8/t;
tank1_out_fluid = 12/t;




 for i= 2:13

tank1(i,1) = tank1(i-1,1) + tank1_in_fluid*0.5 - tank1_out_fluid*tank1(i-1,4);
tank1(i,2) = (tank1(i-1,2) + tank1_in_fluid*0.5 - tank1_out_fluid*tank1(i-1,3));

tank1(i,3) = tank1(i,2) / (tank1(i,1)+tank1(i,2)); %salt rate
tank1(i,4) = tank1(i,1) / (tank1(i,1)+tank1(i,2)); %water rate

disp(tank1);
pause(1);
end





