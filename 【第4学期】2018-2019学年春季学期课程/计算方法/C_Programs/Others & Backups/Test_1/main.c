#include <stdio.h>
#include <stdlib.h>

#define n 16

int main()
{
    int t[21],i,j,nn,k,m;
    double sum1,sum2,sum3,sum4;
    //题设数据导入
    double y0[21]={0,4.00,6.40,8.00,8.80,9.22,9.50,9.70,9.86,
                   10.00,10.20,10.32,10.42,10.50,10.55,10.58,10.60};
    double xx[21]={0},yy[21]={0},b[5]={0};
    double a[5][5],u[5][5],l[5][5],x[5]={0},y[5]={0};
    //条件初始化
    for (i=0;i<5;i++)
        for (j=0;j<5;j++)
        {
            a[i][j]=0;
            u[i][j]=0;
            l[i][j]=0;
        }
    //双曲线拟合数据预处理
    for (i=1;i<=n;i++) t[i]=i;
    for (i=1;i<=n;i++) xx[i]=1.0/t[i];
    for (i=1;i<=n;i++) yy[i]=1.0/y0[i];
    a[1][1]=n;
    for (i=1;i<=n;i++)
    {
        a[1][2]+=xx[i];
        a[2][2]+=(xx[i]*xx[i]);
    }
    a[2][1]=a[1][2];
    for (i=1;i<=n;i++)
    {
        b[1]+=yy[i];
        b[2]+=(yy[i]*xx[i]);
    }
    b[1]*=1000;
    b[2]*=1000;
    //采用Doolittle三角分解法求解矩阵方程
    //三角分解
    nn=2;
    for (j=1;j<=nn;j++) u[1][j]=a[1][j];
    for (i=2;i<=nn;i++) l[i][1]=(1.0*a[i][1])/(u[1][1]);
    for (k=2;k<=nn;k++)
    {
        sum1=0;
        sum2=0;
        for (j=k;j<=nn;j++)
        {
            for (m=1;m<=k-1;m++) sum1+=(l[k][m]*u[m][j]);
            u[k][j]=a[k][j]-sum1;
        }
        for (i=k+1;i<=nn;i++)
        {
            for (m=1;m<=k-1;m++) sum2+=(l[i][m]*u[m][k]);
            l[i][k]=a[i][k]-sum2;
        }
    }
    for (k=1;k<=nn;k++) l[k][k]=1;
    //由回带公式求解
    y[1]=(1.0*b[1])/l[1][1];
    for (k=2;k<=nn;k++)
    {
        sum3=0;
        for (j=1;j<=k-1;j++) sum3+=(l[k][j]*y[j]);
        y[k]=(1.0*(b[k]-sum3))/l[k][k];
    }
    x[nn]=(1.0*y[nn])/u[nn][nn];
    for (k=nn-1;k>=1;k--)
    {
        sum4=0;
        for (j=k+1;j<=n;j++) sum4+=(u[k][j]*x[j]);
        x[k]=(1.0*(y[k]-sum4))/u[k][k];
    }
    printf("双曲线函数拟合曲线方程为：y=t/(%.4ft+%.4f)\n",x[1],x[2]);
    return 0;
}


