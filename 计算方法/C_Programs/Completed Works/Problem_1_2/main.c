// 问题1_2：求浓度y与时间t的拟合曲线（指数函数拟合）
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
    // MAX代表数组下标最大值，n代表实际坐标个数
#define MAX 21
#define n 16

int main()
{
    int t[MAX],i,j,nn,k,m;
    double sum1,sum2,sum3,sum4,temp,ma,sumt;
    // 题设数据导入
    double y0[MAX]={0,4.00,6.40,8.00,8.80,9.22,9.50,9.70,9.86,
                   10.00,10.20,10.32,10.42,10.50,10.55,10.58,10.60};
    double xx[MAX],yy[MAX],det[MAX],res[MAX];
    double a[5][5],u[5][5],l[5][5],x[5],y[5],b[5];
    // 条件初始化
    printf("问题1_2：求浓度y与时间t的拟合曲线（指数函数拟合）\n");
    printf("\n");
    for (i=1;i<=n;i++) y0[i]*=0.001;
    for (i=0;i<5;i++)
    {
        x[i]=0;y[i]=0;b[i]=0;
        for (j=0;j<5;j++)
        {
            a[i][j]=0;
            u[i][j]=0;
            l[i][j]=0;
        }
    }
    for (i=0;i<MAX;i++)
    {
        xx[i]=0;
        yy[i]=0;
        det[i]=0;
    }
    // 指数函数拟合数据预处理
    for (i=1;i<=n;i++) t[i]=i;
    for (i=1;i<=n;i++) xx[i]=1.0/t[i];
    for (i=1;i<=n;i++) yy[i]=log(y0[i]);
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
    // 采用Doolittle三角分解法求解矩阵方程
    // 三角分解
    nn=2;
    for (j=1;j<=nn;j++) u[1][j]=a[1][j];
    for (i=2;i<=nn;i++) l[i][1]=(1.0*a[i][1])/(u[1][1]);
    for (k=2;k<=nn;k++)
    {
        for (j=k;j<=nn;j++)
        {
            sum1=0;
            for (m=1;m<=k-1;m++) sum1+=(l[k][m]*u[m][j]);
            u[k][j]=a[k][j]-sum1;
        }
        for (i=k+1;i<=nn;i++)
        {
            sum2=0;
            for (m=1;m<=k-1;m++) sum2+=(l[i][m]*u[m][k]);
            l[i][k]=a[i][k]-sum2;
        }
    }
    for (k=1;k<=nn;k++) l[k][k]=1;
    // 由回带公式求解未知参数
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
        for (j=k+1;j<=nn;j++) sum4+=(u[k][j]*x[j]);
        x[k]=(1.0*(y[k]-sum4))/u[k][k];
    }
    // 误差计算
    ma=0;sumt=0;
    for (i=1;i<=n;i++)
    {
        temp=exp(x[1])*exp(x[2]/t[i]);
        res[i]=temp;
        det[i]=fabs(y0[i]-temp);
        sumt+=(det[i]*det[i]);
        if (det[i]>ma) ma=det[i];
    }
    // 结果输出
    printf("情形二：\n");
    printf("\n");
    printf("指数函数拟合曲线方程为：y=%.6f*exp(%.6f/t);\n",exp(x[1]),x[2]);
    printf("\n");
    printf("指数函数拟合方式最大偏差为：det=%.8f;\n",ma);
    printf("\n");
    printf("指数函数拟合方式均方误差为：det_mean=%.8f;\n",sqrt(sumt));
    printf("\n");
    printf("指数函数拟合结果如下：\n");
    printf("\n");
    printf("时间t： ");
    for (i=1;i<=n;i++) printf("%-5d ",t[i]);
    printf("\n");
    printf("浓度y：");
    for (i=1;i<=n;i++) printf("%-5.2f ",res[i]*1000);
    printf("\n");
    return 0;
}
