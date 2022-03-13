#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// ȫ�ֱ������壺������������ڵ��������޸�
const int MAX = 5000;
int N;

ofstream cout1("Interpolation_Result.DAT"); // "Interpolation_Result.DAT"�б������ղ�ֵ���߹�����
ofstream cout2("Coefficient_Data.DAT");// "Coefficient_Data.DAT"�б���淶����ĸ������κ���ϵ��
ofstream cout3("Range.DAT");// "Range.DAT"�б��������˵�ֵ
ofstream cout4("Original_Coefficient_Data.DAT");// "Original_Coefficient_Data.DAT"�б���ԭʼ�������κ���ϵ��
ofstream cout5("Curvature_Max_Coordinates.DAT");// "Curvature_Max_Coordinates.DAT"�б������������������ʵ�����ֵ

double x[MAX]={0},y[MAX]={0}; // xΪ��������ꣻyΪ���������ꣻ
double h[MAX]={0}; // hΪ����
double c[MAX]={0},a[MAX]={0},fxym[MAX]={0};
double q_max[MAX]={0},x_max[MAX]={0},y_max[MAX]={0}; // ÿ���ֶ������������ʼ�������

// ������ǰ����

void menu();
void data_intro();
void data_random();
void spline_construction(); // ��������������ֵ���߹���
double f(int x1,int x2,int x3); // ���ֺ���(����������)
void cal_m(int n); // ��׷�Ϸ������������M
void cal_curvature(double a,double b,double c,double d,double x1,double x2,int m); //�������κ���ϵ��������˵㣬������
void data_output_console(int n);
void data_output_file(int n);

int main() //������ʵ��
{
    int choice,i;
    char ch;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
        case 1: // �ֶ���������ڵ�ֵ
            printf("������ƽ���ֵ�ڵ����:\n");
            scanf("%d",&N);
            printf("������������x����:\n");
            for (i=0;i<N;i++) scanf("%lf",&x[i]);
            printf("������������y����:\n");
            for (i=0;i<N;i++) scanf("%lf",&y[i]);
            break;
        case 2: // �Զ������ļ�����
            data_intro(); // �ļ����ݵ�����Ԥ����
            break;
        case 3: // �˳�����
            exit(0);
        }
        spline_construction(); // ����������������
        cout<<"\n���Ƿ���Ҫ�ٽ���һ�����飿y/n��\n";
        cout<<"\n����������ѡ��";
        cin>>ch;
    }
    while(ch=='y'||ch=='Y');
    cout1.close(); // �ر�����ļ�
    cout2.close();
    cout3.close();
    cout4.close();
    cout5.close();
    cout<<"\n��л��ʹ�ñ�����\n";
    return 0;
}

void menu()
{
    //���ò˵�����
    printf("*-------------------------------------------*\n");
    printf("|           ������ʵ����ս��Ŀ��            |\n");
    printf("*-------------------------------------------*\n");
    printf("|   ��������������ֵ����ҳ�����ܵ����߳���  |\n");
    printf("|                                           |\n");
    printf("|          ������ҵ��ѧ  ����ѧԺ           |\n");
    printf("|            ��� ¬�� ������             |\n");
    printf("|           ������ �ؼ�� ������            |\n");
    printf("|                                           |\n");
    printf("*-----------------����˵��------------------*\n");
    printf("|                                           |\n");
    printf("|     ������ɸ����ֶ�������ļ������      |\n");
    printf("|     ƽ���Ҳ����ݵ����꣬������������      |\n");
    printf("|     ��ֵ�������������⻬�����ߣ�ģ��      |\n");
    printf("|     �����������ҳ�����ܵ���̬������      |\n");
    printf("|     �õ������������������ߵ��������      |\n");
    printf("|     �������꣬Ϊʵ�ʹ������迼�ǵĹ�      |\n");
    printf("|     �����������������ṩ����֧�֣�      |\n");
    printf("|     �������MATLAB�����������ͼ��      |\n");
    printf("|                                           |\n");
    printf("*-------------ʹ��˵��������һ--------------*\n");
    printf("|                                           |\n");
    printf("|          1. �ֶ�����ƽ�������            |\n");
    printf("|          2. �Զ��������������ļ�          |\n");
    printf("|          3. �˳�����                      |\n");
    printf("|                                           |\n");
    printf("*----------��ɳ�������--2019.04.27---------*\n");
    printf("\n");
    cout<<"���������ѡ���ţ�Ȼ��enter:";
}

void data_intro()
{
    int i,t;
    char c;
    FILE *fp;
    cout<<"\n���������ݵ��뷽ʽ\n 1: �������������ļ�";
    cout<<"���뽫�ļ�����Ϊ"<<"\"data_intro.DAT\""<<"������������ĿĿ¼�ļ����£�\n";
    cout<<" 2���������һ��������ݣ�����֤����ο�ʹ�ã� \n\n";
    cout<<"����������ѡ���ţ�";
    cin>>t;
    switch (t)
    {
        case 1:
            fp=fopen("data_intro.DAT","r");
            // ������������
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
            // ������������
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
    dn=100; // ��������������
    if ((fp=fopen("data_intro.DAT","w"))==NULL)
    {
        printf("�ļ����ܴ򿪣�\n");
        exit(0);
    }
    x[0]=0;
    for(i=0;i<dn+1;i++) x[i+1]=x[i]+30;
    srand((unsigned)time(NULL)); //�õ�ǰϵͳʱ����������
    for(i=0;i<dn+1;i++)
    {
        b[i]=rand()%6001;    //��rand��������0-6000�������������ֵ������b[i]
        c[i]=b[i]/100;
        y[i]=c[i]-30;    //����-30~+30�������������ֵ������y[i]
    }
    for(i=0;i<dn;i++) fprintf(fp,"%.2f ",x[i]);
    fprintf(fp,"%.2f",x[dn]);
    fprintf(fp,"\n");
    for(i=0;i<dn+1;i++)
        fprintf(fp,"%.2f ",y[i]);
    fclose(fp);
    // getchar();
    printf("\n��������Ѵ洢���ļ�data_intro.dat��\n");
}

void spline_construction() // ��������������ֵ���߹���
{
    int n,i,t;
    char flag;
    double f0,f1;
    n=N-1;
    for(i=0;i<n;i++) h[i]=x[i+1]-x[i]; //�󲽳���������ֵ��֮����������1
    cout<<"\n�������"<<endl;
    cout<<"������߽�����\n 1: ��֪���˵�һ�׵���\n 2�����˵Ķ��׵�����֪\n 3��Ĭ��:��Ȼ�߽�����\n\n";
    cout<<"����������ѡ���ţ�";
    cin>>t;
    cout<<"\n��������"<<endl;
    switch(t)
    {
        case 1:
            cout<<"������ϵ��һ�׵���ֵ��"<<"Y0\'��Y"<<n<<"\'\n";//��ʾ����ΪY0'��Yn'�����ϵ��һ�׵���
            cout<<"Y0\'="; cin>>f0;
            cout<<"Y"<<n<<"\'="; cin>>f1;
            c[0]=1;
            a[n]=1;
            fxym[0]=6*((y[1]-y[0])/(x[1]-x[0])-f0)/h[0];
            fxym[n]=6*(f1-(y[n]-y[n-1])/(x[n]-x[n-1]))/h[n-1];
            break;
        case 2:
            cout<<"������ϵ�Ķ��׵�����"<<"Y0\"��Y"<<n<<"\"\n";//��ʾ����ΪY0'��Yn'�����ϵ��һ�׵���
            cout<<"Y0\"="; cin>>f0;
            cout<<"Y"<<n<<"\"="; cin>>f1;
            c[0]=a[n]=0;
            fxym[0]=2*f0;
            fxym[n]=2*f1;
            break;
        default:
            cout<<"������Ȼ�߽�����\n";//����
    };
    for (i=1;i<n;i++)
        fxym[i]=6*f(i-1,i,i+1);//���ò�ֺ���(only!)
    for (i=1;i<n;i++)
    {
        a[i]=h[i-1]/(h[i]+h[i-1]);
        c[i]=1-a[i];
    }
    a[n]=h[n-1]/(h[n-1]+h[n]);
    cal_m(n); // ������غ���
    cout<<"\n�����ģ�"<<endl;
    cout<<"�Ƿ���Ҫ�����д���ļ��в鿴��y/n\n";
    cout<<"\n����������ѡ��";
    cin>>flag;
    if (flag=='y') data_output_file(n);
    else data_output_console(n);
}

double f(int x1,int x2,int x3) // ���ֺ���(����������)
{
    double a=(y[x3]-y[x2])/(x[x3]-x[x2]);
    double b=(y[x2]-y[x1])/(x[x2]-x[x1]);
    return (a-b)/(x[x3]-x[x1]);
}

void cal_m(int n) // ��׷�Ϸ������������M
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

void cal_curvature(double a,double b,double c,double d,double x1,double x2,int m)  //�������κ���ϵ��������˵㣬������
{
    int i,n;
    double h=0.01;  //���������ʱ��ɨ�貽��
    double q1=0,x,t,y_1,y_2;
    if (x1>x2)
    {
        t=x1;    //�������x1С��x2�������������
        x1=x2;
        x2=t;
    }
    n=int((x2-x1)/h);  //ɨ�����
    q_max[m]=0;
    for (i=0;i<=n;i++)
    {
        x=x1+i*h;
        y_1=-3*a*(x2-x)*(x2-x)-b+3*c*(x-x1)*(x-x1)+d; //һ�׵���
        y_2=6*a*(x2-x)+6*c*(x-x1);       //���׵���
        q1=y_2/pow(1+y_1*y_1,3.0/2);   //��������
        q1=fabs(q1);
        if (q1>q_max[m])
        {
            q_max[m]=q1;
            x_max[m]=x;
            y_max[m]=a*(x2-x)*(x2-x)*(x2-x)+b*(x2-x)+c*(x-x1)*(x-x1)*(x-x1)+d*(x-x1);
        }
    }
}

void data_output_file(int n)// �����������������ֵ���������֪�ϵ�������죩
{
    int i;
    double a0,b0,c0,d0,a1,b1,c1,d1;
    cout<<"\n���߹������ѱ������ļ�Interpolation_Result.DAT�У�\n";
    cout1<<"���������������������£�"<<endl<<endl;
    cout1<<setprecision(6);//ͨ��������setprecision()������Чλ������Ϊͷ�ļ�<iomanip.h>��������������Ϊ������
    for(i=0;i<n;i++) //�������������������ϵ��������
    {
        // ����ԭ��ʽ���ζ���ʽϵ��
        a0=(fxym[i])/(6*h[i]); // a0
        b0=(y[i]-(fxym[i]*h[i]*h[i])/6)/h[i]; // b0
        c0=fxym[i+1]/(6*h[i]); // c0
        d0=(y[i+1]-(fxym[i+1]*h[i]*h[i]/6))/h[i]; // d0
        // ����淶���ζ���ʽϵ��
        a1=(a0+c0);
        b1=(-3*a0*x[i+1]-3*c0*x[i]);
        c1=((3*a0*x[i+1]*x[i+1])+b0+(3*c0*x[i]*x[i])+d0);
        d1=((-1*a0*x[i+1]*x[i+1]*x[i+1])-(b0*x[i+1])-(c0*x[i]*x[i]*x[i])-(d0*x[i]));
        // ����ö������ϵ��������
        cal_curvature(a0,b0,c0,d0,x[i],x[i+1],i+1);
        // ������������������߷���
        cout1<<"��"<<i+1<<"������"<<"��["<<x[i]<<","<<x[i+1]<<"]\n"<<"\t";
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
        //����ö�����������ʼ�������
        cout1<<"�˶������������Ϊ��"<<q_max[i+1]<<endl;
        cout1<<"������ʷ�������Ϊ��"<<"("<<x_max[i+1]<<","<<y_max[i+1]<<")"<<endl;
        cout1<<endl;
                // ���ϵ������
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
    cout<<"\n��������·���Ļ��ʾ��\n";
    cout<<"\n���������������������£�"<<endl<<endl;
    cout<<setprecision(6);//ͨ��������setprecision()������Чλ������Ϊͷ�ļ�<iomanip.h>��������������Ϊ������
    for (i=0;i<n;i++) //�������������������ϵ��������
    {
        // ����ԭ��ʽ���ζ���ʽϵ��
        a0=(fxym[i])/(6*h[i]); // a0
        b0=(y[i]-(fxym[i]*h[i]*h[i])/6)/h[i]; // b0
        c0=fxym[i+1]/(6*h[i]); // c0
        d0=(y[i+1]-(fxym[i+1]*h[i]*h[i]/6))/h[i]; // d0
        // ����淶���ζ���ʽϵ��
        a1=(a0+c0);
        b1=(-3*a0*x[i+1]-3*c0*x[i]);
        c1=((3*a0*x[i+1]*x[i+1])+b0+(3*c0*x[i]*x[i])+d0);
        d1=((-1*a0*x[i+1]*x[i+1]*x[i+1])-(b0*x[i+1])-(c0*x[i]*x[i]*x[i])-(d0*x[i]));
        // ����ö������ϵ��������
        cal_curvature(a0,b0,c0,d0,x[i],x[i+1],i+1);

        // ������������������߷���
        cout<<"��"<<i+1<<"������"<<"��["<<x[i]<<","<<x[i+1]<<"]\n"<<"\t";
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
        //����ö�����������ʼ�������
        cout<<"�˶������������Ϊ��"<<q_max[i+1]<<endl;
        cout<<"������ʷ�������Ϊ��"<<"("<<x_max[i+1]<<","<<y_max[i+1]<<")"<<endl;
        cout<<endl;
        cout2<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<" "<<x_max[i+1]<<" "<<y_max[i+1]<<" "<<"\n"<<endl;
		cout3<<x[i]<<" "<<x[i+1]<<"\n"<<endl;
		cout4<<a0<<" "<<b0<<" "<<c0<<" "<<d0<<"\n"<<endl;
		cout5<<x_max[i+1]<<" "<<y_max[i+1]<<"\n"<<endl;
    }
    cout<<endl;
}
