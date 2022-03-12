%%  ������-�����ٵ���������CFD��
%    MacCormark����

clc
clear

%% ��ʼ����

x=0:0.1:3;
n=length(x);
dx=0.1;
A=1+2.2*(x-1.5).^2;
gamma = 1.4;                       % Cp/Cv 
C=0.5;

Den=1-0.3146*x;          %ʵ��ÿ��������������
Tem=1-0.2314*x;
Vel=(0.1+1.09*x).*Tem.^0.5;


Den_1=zeros(1,n);        %ÿ���������ڣ�ʱ������dt���Ԥ����
Vel_1=zeros(1,n);
Tem_1=zeros(1,n);

dDen_dt=zeros(1,n);    %ʱ�䵼��������ǰ��
dVel_dt=zeros(1,n);
dTem_dt=zeros(1,n);

dDen_dt_1=zeros(1,n);   %ʱ�䵼����Ԥ�ⲽ��
dVel_dt_1=zeros(1,n);
dTem_dt_1=zeros(1,n);

dDen_dt_av=zeros(1,n);   %ʱ�䵼����ȡƽ����
dVel_dt_av=zeros(1,n);
dTem_dt_av=zeros(1,n);


%% ʱ���ƽ�
for k=1:1400
    
    a=Tem.^0.5;
    dt=min(C*dx./(a+Vel));
    
    for i=2:n-1      %Ԥ�ⲽ
        
        dDen_dt(i)=-Den(i)*(Vel(i+1)-Vel(i))/dx-Den(i)*Vel(i)*(log(A(i+1))-log(A(i)))/dx-Vel(i)*(Den(i+1)-Den(i))/dx;
        dVel_dt(i)=-Vel(i)*(Vel(i+1)-Vel(i))/dx-((Tem(i+1)-Tem(i))/dx+Tem(i)/Den(i)*(Den(i+1)-Den(i))/dx)/gamma;
        dTem_dt(i)=-Vel(i)*(Tem(i+1)-Tem(i))/dx-(gamma-1)*Tem(i)*((Vel(i+1)-Vel(i))/dx+Vel(i)*(log(A(i+1))-log(A(i)))/dx);
        
        Den_1(i)=Den(i)+dDen_dt(i)*dt;
        Vel_1(i)=Vel(i)+dVel_dt(i)*dt;
        Tem_1(i)=Tem(i)+dTem_dt(i)*dt;
        
    end
    
      Den_1(1)=1;
      Vel_1(1)=2*Vel_1(2)-Vel_1(3);
      Tem_1(1)=1;
      
      % Vel_1(1)=Vel(1);
    
    
    for i=2:n-1       %������
       
        dDen_dt_1(i)=-Den_1(i)*(Vel_1(i)-Vel_1(i-1))/dx-Den_1(i)*Vel_1(i)*(log(A(i))-log(A(i-1)))/dx-Vel_1(i)*(Den_1(i)-Den_1(i-1))/dx;
        dVel_dt_1(i)=-Vel_1(i)*(Vel_1(i)-Vel_1(i-1))/dx-((Tem_1(i)-Tem_1(i-1))/dx+Tem_1(i)/Den_1(i)*(Den_1(i)-Den_1(i-1))/dx)/gamma;
        dTem_dt_1(i)=-Vel_1(i)*(Tem_1(i)-Tem_1(i-1))/dx-(gamma-1)*Tem_1(i)*((Vel_1(i)-Vel_1(i-1))/dx+Vel_1(i)*(log(A(i))-log(A(i-1)))/dx);
        
        dDen_dt_av(i)=(dDen_dt(i)+dDen_dt_1(i))/2;
        dVel_dt_av(i)=(dVel_dt(i)+dVel_dt_1(i))/2;
        dTem_dt_av(i)=(dTem_dt(i)+dTem_dt_1(i))/2;
        
        Den(i)=Den(i)+dDen_dt_av(i)*dt;
        Vel(i)=Vel(i)+dVel_dt_av(i)*dt;
        Tem(i)=Tem(i)+dTem_dt_av(i)*dt;
    end

      %  �߽�ֵ
      Den(1)=1;
      Vel(1)=2*Vel(2)-Vel(3);
      Tem(1)=1;
      Den(n)=2*Den(n-1)-Den(n-2);
      Vel(n)=2*Vel(n-1)-Vel(n-2);
      Tem(n)=2*Tem(n-1)-Tem(n-2);
end
    
    
    
    
    
    
    
    
