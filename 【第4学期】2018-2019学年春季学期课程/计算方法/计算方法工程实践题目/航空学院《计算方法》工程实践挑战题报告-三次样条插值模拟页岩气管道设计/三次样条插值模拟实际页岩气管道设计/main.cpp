#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// 全局变量定义：允许输入的最大节点数，可修改
const int MAX = 5000;
int N;

ofstream cout1("Interpolation_Result.DAT"); // "Interpolation_Result.DAT"中保存最终插值曲线构造结果
ofstream cout2("Coefficient_Data.DAT");// "Coefficient_Data.DAT"中保存规范化后的各段三次函数系数
ofstream cout3("Range.DAT");// "Range.DAT"中保存各区间端点值
ofstream cout4("Original_Coefficient_Data.DAT");// "Original_Coefficient_Data.DAT"中保存原始各段三次函数系数
ofstream cout5("Curvature_Max_Coordinates.DAT");// "Curvature_Max_Coordinates.DAT"中保存各区间曲线最大曲率的坐标值

double x[MAX]={0},y[MAX]={0}; // x为各点横坐标；y为各点纵坐标；
double h[MAX]={0}; // h为步长
double c[MAX]={0},a[MAX]={0},fxym[MAX]={0};
double q_max[MAX]={0},x_max[MAX]={0},y_max[MAX]={0}; // 每个分段区间的最大曲率及其坐标

// 函数提前声明

void menu();
void data_intro();
void data_random();
void spline_construction(); // 各段三次样条差值曲线构造
double f(int x1,int x2,int x3); // 求差分函数(含三个参数)
void cal_m(int n); // 用追赶法求解出弯矩向量M
void cal_curvature(double a,double b,double c,double d,double x1,double x2,int m); //输入三次函数系数，区间端点，区间编号
void data_output_console(int n);
void data_output_file(int n);

int main() //主程序实现
{
    int choice,i;
    char ch;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
        case 1: // 手动输入各个节点值
            printf("请输入平面差值节点个数:\n");
            scanf("%d",&N);
            printf("请输入各坐标点x坐标:\n");
            for (i=0;i<N;i++) scanf("%lf",&x[i]);
            printf("请输入各坐标点y坐标:\n");
            for (i=0;i<N;i++) scanf("%lf",&y[i]);
            break;
        case 2: // 自动导入文件数据
            data_intro(); // 文件数据导入与预处理
            break;
        case 3: // 退出程序
            exit(0);
        }
        spline_construction(); // 构造三次样条曲线
        cout<<"\n您是否需要再进行一次试验？y/n：\n";
        cout<<"\n请输入您的选择：";
        cin>>ch;
    }
    while(ch=='y'||ch=='Y');
    cout1.close(); // 关闭输出文件
    cout2.close();
    cout3.close();
    cout4.close();
    cout5.close();
    cout<<"\n感谢您使用本程序！\n";
    return 0;
}

void menu()
{
    //设置菜单界面
    printf("*-------------------------------------------*\n");
    printf("|           【工程实践挑战题目】            |\n");
    printf("*-------------------------------------------*\n");
    printf("|   利用三次样条插值构造页岩气管道曲线程序  |\n");
    printf("|                                           |\n");
    printf("|          西北工业大学  航空学院           |\n");
    printf("|            冯铮浩 卢佐 单湘淋             |\n");
    printf("|           姜丽升 秦嘉琛 戴世城            |\n");
    printf("|                                           |\n");
    printf("*-----------------功能说明------------------*\n");
    printf("|                                           |\n");
    printf("|     本程序可根据手动输入或文件导入的      |\n");
    printf("|     平面岩层数据点坐标，利用三次样条      |\n");
    printf("|     插值方法构造连续光滑的曲线，模拟      |\n");
    printf("|     并设计优良的页岩气管道形态，计算      |\n");
    printf("|     得到各段区间上样条曲线的最大曲率      |\n");
    printf("|     及其坐标，为实际工程中需考虑的管      |\n");
    printf("|     道所受力与弯矩情况提供数据支持，      |\n");
    printf("|     最后利用MATLAB软件作出曲线图像。      |\n");
    printf("|                                           |\n");
    printf("*-------------使用说明：步骤一--------------*\n");
    printf("|                                           |\n");
    printf("|          1. 手动输入平面坐标点            |\n");
    printf("|          2. 自动导入坐标数据文件          |\n");
    printf("|          3. 退出程序                      |\n");
    printf("|                                           |\n");
    printf("*----------完成程序日期--2019.04.27---------*\n");
    printf("\n");
    cout<<"请输入你的选则编号，然后按enter:";
}

void data_intro()
{
    int i,t;
    char c;
    FILE *fp;
    cout<<"\n请输入数据导入方式\n 1: 导入已有数据文件";
    cout<<"（请将文件命名为"<<"\"data_intro.DAT\""<<"，并保存在项目目录文件夹下）\n";
    cout<<" 2：随机生成一组测试数据（供验证程序参考使用） \n\n";
    cout<<"请输入您的选择编号：";
    cin>>t;
    switch (t)
    {
        case 1:
            fp=fopen("data_intro.DAT","r");
            // 计算坐标点个数
            N=0;
            for (i=0;i<MAX;i++)
            {
                N++;
                fscanf(fp,"%lf%c",&x[i],&c);
                if (c=='\n') break;
            }
            for (i=0;i<N;i++) fscanf(fp,"%lf",&y[i]);
            break;
        case 2:
            data_random();
            fp=fopen("data_intro.DAT","r");
            // 计算坐标点个数
            N=0;
            for (i=0;i<MAX;i++)
            {
                N++;
                fscanf(fp,"%lf%c",&x[i],&c);
                if (c=='\n') break;
            }
            for (i=0;i<N;i++) fscanf(fp,"%lf",&y[i]);
            break;
    }
}

void data_random()
{
    int i,dn;
    double x[MAX],b[MAX],c[MAX],y[MAX];
    FILE *fp;
    dn=100; // 随机生成区间段数
    if ((fp=fopen("data_intro.DAT","w"))==NULL)
    {
        printf("文件不能打开！\n");
        exit(0);
    }
    x[0]=0;
    for(i=0;i<dn+1;i++) x[i+1]=x[i]+30;
    srand((unsigned)time(NULL)); //用当前系统时间设置种子
    for(i=0;i<dn+1;i++)
    {
        b[i]=rand()%6001;    //用rand函数生成0-6000的随机数，并赋值给数组b[i]
        c[i]=b[i]/100;
        y[i]=c[i]-30;    //生成-30~+30的随机数，并赋值给数组y[i]
    }
    for(i=0;i<dn;i++) fprintf(fp,"%.2f ",x[i]);
    fprintf(fp,"%.2f",x[dn]);
    fprintf(fp,"\n");
    for(i=0;i<dn+1;i++)
        fprintf(fp,"%.2f ",y[i]);
    fclose(fp);
    // getchar();
    printf("\n随机数据已存储在文件data_intro.dat中\n");
}

void spline_construction() // 各段三次样条差值曲线构造
{
    int n,i,t;
    char flag;
    double f0,f1;
    n=N-1;
    for(i=0;i<n;i++) h[i]=x[i+1]-x[i]; //求步长；其数组值较之坐标点个数少1
    cout<<"\n步骤二："<<endl;
    cout<<"请输入边界条件\n 1: 已知两端的一阶导数\n 2：两端的二阶导数已知\n 3：默认:自然边界条件\n\n";
    cout<<"请输入您的选择编号：";
    cin>>t;
    cout<<"\n步骤三："<<endl;
    switch(t)
    {
        case 1:
            cout<<"请输入断点的一阶导数值："<<"Y0\'与Y"<<n<<"\'\n";//显示数据为Y0'至Yn'，即断点的一阶导数
            cout<<"Y0\'="; cin>>f0;
            cout<<"Y"<<n<<"\'="; cin>>f1;
            c[0]=1;
            a[n]=1;
            fxym[0]=6*((y[1]-y[0])/(x[1]-x[0])-f0)/h[0];
            fxym[n]=6*(f1-(y[n]-y[n-1])/(x[n]-x[n-1]))/h[n-1];
            break;
        case 2:
            cout<<"请输入断点的二阶导数："<<"Y0\"与Y"<<n<<"\"\n";//显示数据为Y0'至Yn'，即断点的一阶导数
            cout<<"Y0\"="; cin>>f0;
            cout<<"Y"<<n<<"\"="; cin>>f1;
            c[0]=a[n]=0;
            fxym[0]=2*f0;
            fxym[n]=2*f1;
            break;
        default:
            cout<<"采用自然边界条件\n";//待定
    };
    for (i=1;i<n;i++)
        fxym[i]=6*f(i-1,i,i+1);//调用差分函数(only!)
    for (i=1;i<n;i++)
    {
        a[i]=h[i-1]/(h[i]+h[i-1]);
        c[i]=1-a[i];
    }
    a[n]=h[n-1]/(h[n-1]+h[n]);
    cal_m(n); // 调用弯矩函数
    cout<<"\n步骤四："<<endl;
    cout<<"是否需要将结果写入文件中查看？y/n\n";
    cout<<"\n请输入您的选择：";
    cin>>flag;
    if (flag=='y') data_output_file(n);
    else data_output_console(n);
}

double f(int x1,int x2,int x3) // 求差分函数(含三个参数)
{
    double a=(y[x3]-y[x2])/(x[x3]-x[x2]);
    double b=(y[x2]-y[x1])/(x[x2]-x[x1]);
    return (a-b)/(x[x3]-x[x1]);
}

void cal_m(int n) // 用追赶法求解出弯矩向量M
{
    int i;
    double B[MAX];
    B[0]=c[0]/2;
    for (i=1;i<n;i++)
        B[i]=c[i]/(2-a[i]*B[i-1]);
    fxym[0]=fxym[0]/2;
    for (i=1;i<=n;i++)
        fxym[i]=(fxym[i]-a[i]*fxym[i-1])/(2-a[i]*B[i-1]);
    for (i=n-1;i>=0;i--)
        fxym[i]=fxym[i]-B[i]*fxym[i+1];
}

void cal_curvature(double a,double b,double c,double d,double x1,double x2,int m)  //输入三次函数系数，区间端点，区间编号
{
    int i,n;
    double h=0.01;  //求最大曲率时的扫描步长
    double q1=0,x,t,y_1,y_2;
    if (x1>x2)
    {
        t=x1;    //若输入的x1小于x2，两数结果交换
        x1=x2;
        x2=t;
    }
    n=int((x2-x1)/h);  //扫描次数
    q_max[m]=0;
    for (i=0;i<=n;i++)
    {
        x=x1+i*h;
        y_1=-3*a*(x2-x)*(x2-x)-b+3*c*(x-x1)*(x-x1)+d; //一阶导数
        y_2=6*a*(x2-x)+6*c*(x-x1);       //二阶导数
        q1=y_2/pow(1+y_1*y_1,3.0/2);   //计算曲率
        q1=fabs(q1);
        if (q1>q_max[m])
        {
            q_max[m]=q1;
            x_max[m]=x;
            y_max[m]=a*(x2-x)*(x2-x)*(x2-x)+b*(x2-x)+c*(x-x1)*(x-x1)*(x-x1)+d*(x-x1);
        }
    }
}

void data_output_file(int n)// 输出各段三次样条插值结果（因已知断点个数而异）
{
    int i;
    double a0,b0,c0,d0,a1,b1,c1,d1;
    cout<<"\n曲线构造结果已保存在文件Interpolation_Result.DAT中：\n";
    cout1<<"三次样条函数构造结果如下："<<endl<<endl;
    cout1<<setprecision(6);//通过操作器setprecision()设置有效位数；其为头文件<iomanip.h>所包含；括号内为参数。
    for(i=0;i<n;i++) //所输出函数个数由所设断点个数而定
    {
        // 计算原形式三次多项式系数
        a0=(fxym[i])/(6*h[i]); // a0
        b0=(y[i]-(fxym[i]*h[i]*h[i])/6)/h[i]; // b0
        c0=fxym[i+1]/(6*h[i]); // c0
        d0=(y[i+1]-(fxym[i+1]*h[i]*h[i]/6))/h[i]; // d0
        // 计算规范三次多项式系数
        a1=(a0+c0);
        b1=(-3*a0*x[i+1]-3*c0*x[i]);
        c1=((3*a0*x[i+1]*x[i+1])+b0+(3*c0*x[i]*x[i])+d0);
        d1=((-1*a0*x[i+1]*x[i+1]*x[i+1])-(b0*x[i+1])-(c0*x[i]*x[i]*x[i])-(d0*x[i]));
        // 计算该段曲线上的最大曲率
        cal_curvature(a0,b0,c0,d0,x[i],x[i+1],i+1);
        // 输出各段三次样条曲线方程
        cout1<<"第"<<i+1<<"段区间"<<"：["<<x[i]<<","<<x[i+1]<<"]\n"<<"\t";
        cout1<<"S(x)= ";

            cout1<<a0<<"*("<<x[i+1]<<" - x)^3";

        if (c0>0)
            cout1<<" + "<<c0<<"*(x - "<<x[i]<<")^3";
        else
            cout1<<" - "<<-c0<<"*(x - "<<x[i]<<")^3";

        if (b0>0)
            cout1<<" + "<<b0<<"*("<<x[i+1]<<" - x)";
        else
            cout1<<" - "<<-b0<<"*("<<x[i+1]<<" - x)";

        if (d0>0)
            cout1<<" + "<<d0<<"*(x - "<<x[i]<<")";
        else
            cout1<<" - "<<-d0<<"*(x - "<<x[i]<<")";
        cout1<<endl;
        //输出该段曲线最大曲率及其坐标
        cout1<<"此段曲线最大曲率为："<<q_max[i+1]<<endl;
        cout1<<"最大曲率发生坐标为："<<"("<<x_max[i+1]<<","<<y_max[i+1]<<")"<<endl;
        cout1<<endl;
                // 输出系数数据
        cout2<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<"\n"<<endl;
		cout3<<x[i]<<" "<<x[i+1]<<"\n"<<endl;
		cout4<<a0<<" "<<b0<<" "<<c0<<" "<<d0<<"\n"<<endl;
        cout5<<x_max[i+1]<<" "<<y_max[i+1]<<"\n"<<endl;
    }
    cout<<endl;
}

void data_output_console(int n)
{
    int i;
    double a0,b0,c0,d0,a1,b1,c1,d1;
    cout<<"\n结果已在下方屏幕显示：\n";
    cout<<"\n三次样条函数构造结果如下："<<endl<<endl;
    cout<<setprecision(6);//通过操作器setprecision()设置有效位数；其为头文件<iomanip.h>所包含；括号内为参数。
    for (i=0;i<n;i++) //所输出函数个数由所设断点个数而定
    {
        // 计算原形式三次多项式系数
        a0=(fxym[i])/(6*h[i]); // a0
        b0=(y[i]-(fxym[i]*h[i]*h[i])/6)/h[i]; // b0
        c0=fxym[i+1]/(6*h[i]); // c0
        d0=(y[i+1]-(fxym[i+1]*h[i]*h[i]/6))/h[i]; // d0
        // 计算规范三次多项式系数
        a1=(a0+c0);
        b1=(-3*a0*x[i+1]-3*c0*x[i]);
        c1=((3*a0*x[i+1]*x[i+1])+b0+(3*c0*x[i]*x[i])+d0);
        d1=((-1*a0*x[i+1]*x[i+1]*x[i+1])-(b0*x[i+1])-(c0*x[i]*x[i]*x[i])-(d0*x[i]));
        // 计算该段曲线上的最大曲率
        cal_curvature(a0,b0,c0,d0,x[i],x[i+1],i+1);

        // 输出各段三次样条曲线方程
        cout<<"第"<<i+1<<"段区间"<<"：["<<x[i]<<","<<x[i+1]<<"]\n"<<"\t";
        cout<<"S(x)= ";

        if (a0>0)
            cout<<a0<<"*("<<x[i+1]<<" - x)^3";
        else
            cout<<-a0<<"*("<<x[i+1]<<" - x)^3";

        if (c0>0)
            cout<<" + "<<c0<<"*(x - "<<x[i]<<")^3";
        else
            cout<<" - "<<-c0<<"*(x - "<<x[i]<<")^3";

        if (b0>0)
            cout<<" + "<<b0<<"*("<<x[i+1]<<" - x)";
        else
            cout<<" - "<<-b0<<"*("<<x[i+1]<<" - x)";

        if (d0>0)
            cout<<" + "<<d0<<"*(x - "<<x[i]<<")";
        else
            cout<<" - "<<-d0<<"*(x - "<<x[i]<<")";
        cout<<endl;
        //输出该段曲线最大曲率及其坐标
        cout<<"此段曲线最大曲率为："<<q_max[i+1]<<endl;
        cout<<"最大曲率发生坐标为："<<"("<<x_max[i+1]<<","<<y_max[i+1]<<")"<<endl;
        cout<<endl;
        cout2<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<" "<<x_max[i+1]<<" "<<y_max[i+1]<<" "<<"\n"<<endl;
		cout3<<x[i]<<" "<<x[i+1]<<"\n"<<endl;
		cout4<<a0<<" "<<b0<<" "<<c0<<" "<<d0<<"\n"<<endl;
		cout5<<x_max[i+1]<<" "<<y_max[i+1]<<"\n"<<endl;
    }
    cout<<endl;
}
