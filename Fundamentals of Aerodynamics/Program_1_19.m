%% Data Introduction
clear all
clc
angle=[-3:6];
norm=[0.242,0.286,0.332,0.381,0.434,0.489,0.546,0.600,0.650,0.696];
tang=[0.043,0.037,0.031,0.024,0.016,0.008,0.000,-0.007,-0.014,-0.021];
F=100;
V=50;
S_c=0.0033;
n=length(angle);
L=zeros(1,n);
D=zeros(1,n);
RL=zeros(1,n);

%% Calculation
N=S_c*F*V*V*norm;
T=S_c*F*V*V*tang;
for i=1:n
    L(i)=N(i)*cos(angle(i)*pi/180)-T(i)*sin(angle(i)*pi/180);
    D(i)=N(i)*sin(angle(i)*pi/180)+T(i)*cos(angle(i)*pi/180);
    RL(i)=L(i)/D(i);
end
