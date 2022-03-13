%% 绘制拟合函数曲线
clear all
clf
clc
load Problem_1_data.txt;
t=Problem_1_data(1,:);
x=Problem_1_data(2,:);
n=length(t);

% 拟合函数数据计算
gap=0.02;
cnt=0;
for i=0:gap:18
    cnt=cnt+1;
    xx(cnt)=i;
    yy(cnt)=11.3253*exp(-1.0567/i);
end

% 绘制原始数据点
plot(t,x,'r.','MarkerSize',16);

% 绘制拟合曲线
hold on
plot(xx,yy,'b-','LineWidth',2);
xlabel('时间/（分）');
ylabel('生物浓度y（10^{-3}）');
legend('原始数据点','指数函数拟合曲线');
axis([0,18,2,12]);
grid on;
box on;



