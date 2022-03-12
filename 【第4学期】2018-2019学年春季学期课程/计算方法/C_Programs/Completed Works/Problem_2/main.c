// ����2������Seidel��������ⷽ����
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
    // ���ݳ�ʼ��
    for (i=0;i<MAX1;i++)
        for (j=0;j<MAX1;j++)
    {
        a[i][j]=0;
        c[i][j]=0;
    }
    for (i=0;i<MAX1;i++) b[i]=0;
    for (i=0;i<MAX2;i++)
        for (j=0;j<MAX1;j++) x[i][j]=0;
    //ͨ�����ݵ���
    printf("����2������Seidel��������ⷽ����\n");
    printf("\n");
    printf("����������������\n");
    scanf("%d",&n);
    printf("����������������\n");
    scanf("%d",&m);
    printf("������%d*%d��ϵ������\n",n,m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%lf",&a[i][j]);
    printf("\n");
    printf("������1*%d�ĳ�������\n",n);
    for (i=1;i<=n;i++) scanf("%lf",&b[i]);
    // �����������
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
    // ���ó�ʼ����
    x[0][1]=0;x[0][2]=0;x[0][3]=0;
    // ������ʽ����
    det=1;
    k=0; //����������
    // ��det<=1e-3ʱ����������
    while (det>0.001)
    {
        //һ����������
        for (t=1;t<=n;t++)
        {
            for (i=1;i<=m;i++) x[k+1][t]+=(c[t][i]*x[k][i]);
            x[k+1][t]+=c[t][m+1];
        }
        //�������
        for (i=1;i<=n;i++)
            if ((x[k+1][i]-x[k][i])<det) det=x[k+1][i]-x[k][i];
        k++;
    }
    // ������
    printf("\n");
    printf("�����󷽳̽�����£�\n");
    printf("\n");
    printf("����������k=%dʱ����\n",k);
    for (i=1;i<=n;i++) printf("x%d=%.5f ",i,x[k][i]);
    printf("\n");
    return 0;
}


