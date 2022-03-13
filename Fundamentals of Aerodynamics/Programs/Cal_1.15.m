%% Raw Data Initiation
W=2950; % the airplane weight
rou=0.002377;
S=174;

%% Calculation
for v=70:10:250
    CL=W/(0.5*rou*v*v*S);
    CD=0.025+0.054*CL*CL;
    R=CL/CD;
end