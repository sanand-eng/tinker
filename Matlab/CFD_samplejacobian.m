%authored by sathya anand 
clear all; close all; clc;

%Define iteration criteria, step sizes, beta parameter
max_iterations = 5000; % maximum number of iterations
length_x = 2; % length of plate in x direction
length_y = 1; % length of plate in y direction
delta_x = 0.05; % spacing of grid points in the x direction
delta_y = 0.05; % spacing of grid points in the y direction
Nx = length_x/delta_x + 1% number of grid points in the x direction
Nxx = length_x/delta_x
Ny = length_y/delta_y + 1; % number of grid points in the y direction
beta = delta_x/delta_y; % ratio of x and y grid spacing
error_max = 0.01; % maximum cumulative error

%Generate grid vectors in x and y directions
x = linspace(0,2,Nx);
y = linspace(0,1,Ny);

%Assign initial conditions (zero degrees C at all interior points)
tempK = zeros(Nx,Ny);

%Assign boundary conditions
% at y=0, T1=10C and at y=H, T3=0C
for i=2:(Nx-1)
tempK(i,1)=10;
tempK(i,Ny)=0;
end
% at x=0, T2=20C and at x=L, T4=0C
for j=1:Ny
tempK(1,j)=20;
tempK(Nx,j)=0;
end

%Perform numerical computation until solution has converged
%or max iterations reached
for k=1:max_iterations
error=0.0;
for j=2:(Ny-1)
for i=2:(Nx-1)
% Jacobian method
tempKP1(i,j)= 0.5/(1.0+beta^2)*(tempK(i+1,j)+tempK(i-1,j) ...
+ beta^2*(tempK(i,j+1) + tempK(i,j-1)));
% calculate cumulative iterative error
error = error + abs(tempKP1(i,j)-tempK(i,j));
end
end
tempK(2:Nx-1,2:Ny-1)=tempKP1(2:Nx-1,2:Ny-1);
if error < error_max
break;
end
end

%Contour plot of converged temperature distribution (Fig. 1)
contourf(tempK',140);
title('Contour Plot of Temperature along a Flat Plate');
xlabel('x direction nodes');
ylabel('y direction nodes');
colorbar;