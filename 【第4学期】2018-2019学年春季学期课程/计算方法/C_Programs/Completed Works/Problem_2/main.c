// 问题2：利用Seidel迭代法求解方程组
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX1 8
#define MAX2 100

int main()
{
    int n,m,i,j,k,t;
    double a[MAX1][MAX1],c[MAX1][MAX1],b[MAX1],x[MAX2][MAX1+1];
    double temp,det;
    // 数据初始化
    for (i=0;i<MAX1;i++)
        for (j=0;j<MAX1;j++)
    {
        a[i][j]=0;
        c[i][j]=0;
    }
    for (i=0;i<MAX1;i++) b[i]=0;
    for (i=0;i<MAX2;i++)
        for (j=0;j<MAX1;j++) x[i][j]=0;
    //通用数据导入
    printf("问题2：利用Seidel迭代法求解方程组\n");
    printf("\n");
    printf("请输入矩阵的行数：\n");
    scanf("%d",&n);
    printf("请输入矩阵的列数：\n");
    scanf("%d",&m);
    printf("请输入%d*%d的系数矩阵：\n",n,m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%lf",&a[i][j]);
    printf("\n");
    printf("请输入1*%d的常数矩阵：\n",n);
    for (i=1;i<=n;i++) scanf("%lf",&b[i]);
    // 迭代矩阵计算
    for (i=1;i<=n;i++)
    {
        temp=a[i][i];
        c[i][m+1]=(1.0*b[i])/temp;
        for (j=1;j<=m;j++)
        {
            if (j==i) c[i][j]=0;
            else c[i][j]=(-1.0*a[i][j])/temp;
        }
    }
    // 设置初始向量
    x[0][1]=0;x[0][2]=0;x[0][3]=0;
    // 迭代公式计算
    det=1;
    k=0; //计数器启动
    // 当det<=1e-3时，结束迭代
    while (det>0.001)
    {
        //一次完整迭代
        for (t=1;t<=n;t++)
        {
            for (i=1;i<=m;i++) x[k+1][t]+=(c[t][i]*x[k][i]);
            x[k+1][t]+=c[t][m+1];
        }
        //计算误差
        for (i=1;i<=n;i++)
            if ((x[k+1][i]-x[k][i])<det) det=x[k+1][i]-x[k][i];
        k++;
    }
    // 结果输出
    printf("\n");
    printf("求解矩阵方程结果如下：\n");
    printf("\n");
    printf("迭代过程在k=%d时结束\n",k);
    for (i=1;i<=n;i++) printf("x%d=%.5f ",i,x[k][i]);
    printf("\n");
    return 0;
}


