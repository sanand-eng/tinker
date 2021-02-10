%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%             INFO             %
%  Scripted By: Sathya Anand   %
%   Exponential Moving Avg     %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc
clear
close ALL
load('INPUT_DATA.mat')
x = Signal_DATA(1:200000); % assign data to x [0 1 2 3 4 5 6 7 8 9 10] ;
T = 2048; % size of 1 window
N_x = length(x); %total length of vector or samples

%calculate EMA Right 
for t=1:(N_x-T)
    EMA_right(t) = 0;
    for n=0:(T-1), 
        EMA_r(n+1) =  1/T .*(1-1/T)^n .* x(t+n).^2;
        EMA_right(t) =  EMA_right(t) + EMA_r(n+1);
    end 
end
%calculate EMA Left 
for j=0:(N_x-2*T)
    t=(N_x-T)-j;
    EMA_left(t) = 0;
    for n=0:(T-1), 
        EMA_l(n+1) = 1/T .*(1-1/T)^(n-1) .*x(t-n).^2;
        EMA_left(t) =  EMA_left(t) + EMA_l(n+1);
    end 
end

EMA_total = EMA_left+EMA_right; %EMA Total

%calculate mean of EMA 
sum_total = 0;
for i=1:length(EMA_total), 
    sum_total = sum_total + EMA_total(i); 
end
EMA_mean = sum_total/length(EMA_total);

%Threshold Calculation
threshold= EMA_mean + 0.5*std(EMA_total);

%remove values below threashold
for i=1:length(EMA_total), 
    if EMA_total(i)<threshold
        EMA_total(i)=threshold;
    else 
        EMA_total(i)=EMA_total(i);
    end
end 

%plot data 
figure
plot(EMA_left+EMA_right)
xlabel('Sample Time');
ylabel('Amplitude');
title('EMA Unfiltered');

figure
plot(EMA_total)
xlabel('Sample Time');
ylabel('Amplitude');
title('EMA Filtered');
