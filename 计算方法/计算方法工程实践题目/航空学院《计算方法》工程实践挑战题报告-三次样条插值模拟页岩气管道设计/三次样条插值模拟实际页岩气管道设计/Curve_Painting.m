%% 三次样条插值构造页岩气管道曲线MATLAB作图
%% 数据初始化
clear all
clf
clc
A=load('data_intro.DAT');
C=load('Original_Coefficient_Data.DAT');
D=load('Range.DAT');
M=load('Curvature_Max_Coordinates.DAT');
[m,n]=size(C);
gap=0.01;

%% 绘制曲线
% 提取各个原始点坐标
A1=A(1,:);
A2=A(2,:);
% 提取各个原始系数
C1=C(:,1);
C2=C(:,2);
C3=C(:,3);
C4=C(:,4);
% 提取区间端点值
D1=D(:,1);
D2=D(:,2);
Max_x_min=min(D1);
Max_x_max=max(D2);
% 提取区间最大曲率坐标值
M1=M(:,1);
M2=M(:,2);
temp=(max(M2)-min(M2))/2;
Max_y_max=max(M2)+temp;
Max_y_min=min(M2)-temp;
% 作出每段插值曲线函数图像
plot(A1,A2,'.','MarkerSize',16,'Color',[220/255,20/255,60/255]);
% 第k段区间绘制
hold on
for k=1:m
    xx=D1(k):gap:D2(k);
    Ds=ones(1,length(xx))*D1(k);
    Dt=ones(1,length(xx))*D2(k);
    yy=C1(k)*((Dt-xx).^3)+C3(k)*((xx-Ds).^3)+C2(k)*(Dt-xx)+C4(k)*(xx-Ds);
    plot(xx,yy,'-','LineWidth',2.4,'Color',[1,182/255,193/255]);
    plot(M1,M2,'.','MarkerSize',16,'Color',[0,0,1]);
end
legend('插值控制节点','三次样条插值曲线','分段曲率最大坐标点');
xlabel('掘进深度/\itm');ylabel('纵向偏移/\itm');
title('三次样条插值构造页岩气管道曲线图像');
axis([Max_x_min,Max_x_max,Max_y_min,Max_y_max]);
grid on
box on
