// ����4��ʹ�ùŵ���ʾ��ʽ����ֵ�������ֵ��
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    // �ڵ�������
#define MAX 100

int main()
{
    int n,m,i,j;
    double h,l,u[MAX][MAX];
    // ��ֵ�������ʼ��
    for (i=0;i<MAX;i++)
        for (j=0;j<MAX;j++) u[i][j]=0;
    printf("����4��ʹ�ùŵ���ʾ��ʽ����ֵ�������ֵ��\n");
    printf("\n");
    printf("������x����Ĳ���h��");
    scanf("%lf",&h);
    m=(int)(1.0/h);
    printf("����������Lambda��");
    scanf("%lf",&l);
    printf("������������n��");
    scanf("%d",&n);
    // �߽�������ʼ��1
    // �����0���ϵ�ֵ
    for (i=0;i<=m;i++) u[i][0]=(4*h*i)*(1-(h*i));
    // �߽�������ʼ��2
    for (j=0;j<=n;j++) u[0][j]=0;
    // �������0~n���ϸ���Ԫ�ڵ��ֵ
    for (j=0;j<=n;j++)
    {
        for (i=1;i<=m;i++)
            u[i][j+1]=(l*u[i+1][j])+((1-2*l)*u[i][j])+(l*u[i-1][j]);
    }
    // ���������
    printf("\n");
    printf("0~%d����㵥Ԫ�ڵ��ֵ�б����£�\n",n);
    printf("\n");
    for (j=0;j<=n;j++)
    {
        for (i=0;i<=m+1;i++) printf("%-8.6f ",u[i][j]);
        printf("\n");
    }
    return 0;
}


