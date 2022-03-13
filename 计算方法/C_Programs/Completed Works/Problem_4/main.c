// 问题4：使用古典显示格式求解边值问题的数值解
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    // 节点最大层数
#define MAX 100

int main()
{
    int n,m,i,j;
    double h,l,u[MAX][MAX];
    // 数值导入与初始化
    for (i=0;i<MAX;i++)
        for (j=0;j<MAX;j++) u[i][j]=0;
    printf("问题4：使用古典显示格式求解边值问题的数值解\n");
    printf("\n");
    printf("请输入x方向的步长h：");
    scanf("%lf",&h);
    m=(int)(1.0/h);
    printf("请输入网比Lambda：");
    scanf("%lf",&l);
    printf("请输入求解层数n：");
    scanf("%d",&n);
    // 边界条件初始化1
    // 计算第0层上的值
    for (i=0;i<=m;i++) u[i][0]=(4*h*i)*(1-(h*i));
    // 边界条件初始化2
    for (j=0;j<=n;j++) u[0][j]=0;
    // 递推求解0~n层上各单元节点的值
    for (j=0;j<=n;j++)
    {
        for (i=1;i<=m;i++)
            u[i][j+1]=(l*u[i+1][j])+((1-2*l)*u[i][j])+(l*u[i-1][j]);
    }
    // 计算结果输出
    printf("\n");
    printf("0~%d层各层单元节点的值列表如下：\n",n);
    printf("\n");
    for (j=0;j<=n;j++)
    {
        for (i=0;i<=m+1;i++) printf("%-8.6f ",u[i][j]);
        printf("\n");
    }
    return 0;
}


