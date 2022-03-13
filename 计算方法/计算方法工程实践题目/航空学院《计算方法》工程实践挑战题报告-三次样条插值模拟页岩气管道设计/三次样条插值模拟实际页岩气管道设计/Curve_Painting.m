%% ����������ֵ����ҳ�����ܵ�����MATLAB��ͼ
%% ���ݳ�ʼ��
clear all
clf
clc
A=load('data_intro.DAT');
C=load('Original_Coefficient_Data.DAT');
D=load('Range.DAT');
M=load('Curvature_Max_Coordinates.DAT');
[m,n]=size(C);
gap=0.01;

%% ��������
% ��ȡ����ԭʼ������
A1=A(1,:);
A2=A(2,:);
% ��ȡ����ԭʼϵ��
C1=C(:,1);
C2=C(:,2);
C3=C(:,3);
C4=C(:,4);
% ��ȡ����˵�ֵ
D1=D(:,1);
D2=D(:,2);
Max_x_min=min(D1);
Max_x_max=max(D2);
% ��ȡ���������������ֵ
M1=M(:,1);
M2=M(:,2);
temp=(max(M2)-min(M2))/2;
Max_y_max=max(M2)+temp;
Max_y_min=min(M2)-temp;
% ����ÿ�β�ֵ���ߺ���ͼ��
plot(A1,A2,'.','MarkerSize',16,'Color',[220/255,20/255,60/255]);
% ��k���������
hold on
for k=1:m
    xx=D1(k):gap:D2(k);
    Ds=ones(1,length(xx))*D1(k);
    Dt=ones(1,length(xx))*D2(k);
    yy=C1(k)*((Dt-xx).^3)+C3(k)*((xx-Ds).^3)+C2(k)*(Dt-xx)+C4(k)*(xx-Ds);
    plot(xx,yy,'-','LineWidth',2.4,'Color',[1,182/255,193/255]);
    plot(M1,M2,'.','MarkerSize',16,'Color',[0,0,1]);
end
legend('��ֵ���ƽڵ�','����������ֵ����','�ֶ�������������');
xlabel('������/\itm');ylabel('����ƫ��/\itm');
title('����������ֵ����ҳ�����ܵ�����ͼ��');
axis([Max_x_min,Max_x_max,Max_y_min,Max_y_max]);
grid on
box on
