%% ������Ϻ�������
clear all
clf
clc
load Problem_1_data.txt;
t=Problem_1_data(1,:);
x=Problem_1_data(2,:);
n=length(t);

% ��Ϻ������ݼ���
gap=0.02;
cnt=0;
for i=0:gap:18
    cnt=cnt+1;
    xx(cnt)=i;
    yy(cnt)=11.3253*exp(-1.0567/i);
end

% ����ԭʼ���ݵ�
plot(t,x,'r.','MarkerSize',16);

% �����������
hold on
plot(xx,yy,'b-','LineWidth',2);
xlabel('ʱ��/���֣�');
ylabel('����Ũ��y��10^{-3}��');
legend('ԭʼ���ݵ�','ָ�������������');
axis([0,18,2,12]);
grid on;
box on;



