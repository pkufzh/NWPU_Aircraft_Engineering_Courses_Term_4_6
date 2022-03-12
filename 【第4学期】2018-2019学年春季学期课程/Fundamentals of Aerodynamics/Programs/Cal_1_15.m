%% Raw Data Initiation
W=2950; % the airplane weight
rou=0.002377;
S=174;
A=zeros(1,100);
B=zeros(1,100);
C=zeros(1,100);
D=zeros(1,100);
E=zeros(4,100);

%% Calculation
cnt=0;
for v=70:10:250
    cnt=cnt+1;
    CL=W/(0.5*rou*v*v*S);
    CD=0.025+0.054*CL*CL;
    R=CL/CD;
    A(cnt)=v;
    B(cnt)=CL;
    C(cnt)=CD;
    D(cnt)=R;
    E(1,cnt)=v;
    E(2,cnt)=CL;
    E(3,cnt)=CD;
    E(4,cnt)=R;
end
hold on;
plot(A,B);
plot(A,C);
plot(A,D);
axis([70,250,0,13.5]);
grid on;
box on;



