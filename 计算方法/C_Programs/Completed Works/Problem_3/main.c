/*问题3：用直接三角分解法求解方程组，并写出
         Doolittle分解的单位下三角矩阵L和上三角矩阵U的形式*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 8

int main()
{
    int n,m,nn,i,j,k;
    double sum1,sum2,sum3,sum4;
    double a[MAX][MAX],u[MAX][MAX],l[MAX][MAX],x[MAX],y[MAX],b[MAX];
    // 数据初始化
    for (i=0;i<MAX;i++)
        for (j=0;j<MAX;j++)
        {
            a[i][j]=0;
            u[i][j]=0;
            l[i][j]=0;
        }
    for (i=0;i<MAX;i++)
    {
        b[i]=0;
        x[i]=0;
        y[i]=0;
    }
    //通用数据导入
    printf("问题3：用直接三角分解法求解方程组，\n");
    printf("并写出Doolittle分解的单位下三角矩阵L和上三角矩阵U的形式\n");
    printf("\n");
    printf("请输入矩阵的行数：");
    scanf("%d",&n);
    printf("请输入矩阵的列数：");
    scanf("%d",&m);
    printf("请输入%d*%d的系数矩阵：\n",n,m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%lf",&a[i][j]);
    printf("请输入1*%d的常数矩阵：\n",n);
    for (i=1;i<=n;i++) scanf("%lf",&b[i]);
    // 采用Doolittle三角分解法求解矩阵方程
    // 三角分解
    nn=n;
    for (j=1;j<=nn;j++) u[1][j]=a[1][j];
    for (i=2;i<=nn;i++) l[i][1]=(1.0*a[i][1])/(u[1][1]);
    for (k=2;k<=nn;k++)
    {
        for (j=k;j<=nn;j++)
        {
            sum1=0; //需注意累加变量初始化位置
            for (m=1;m<=k-1;m++) sum1+=(l[k][m]*u[m][j]);
            u[k][j]=a[k][j]-sum1;
        }
        for (i=k+1;i<=nn;i++)
        {
            sum2=0;
            for (m=1;m<=k-1;m++) sum2+=(l[i][m]*u[m][k]);
            l[i][k]=(1.0*(a[i][k]-sum2))/u[k][k];
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
    // 结果输出
    printf("\n");
    printf("方程组的解为：\n");
    for (i=1;i<=n;i++) printf("x%d=%.2f ",i,x[i]);
    printf("\n");
    printf("\n");
    printf("Doolittle三角分解结果如下：\n");
    printf("\n");
    printf("单位下三角矩阵L为：\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) printf("%6.2f",l[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("上三角矩阵U为：\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) printf("%6.2f",u[i][j]);
        printf("\n");
    }
    return 0;
}
