/*����3����ֱ�����Ƿֽⷨ��ⷽ���飬��д��
         Doolittle�ֽ�ĵ�λ�����Ǿ���L�������Ǿ���U����ʽ*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 8

int main()
{
    int n,m,nn,i,j,k;
    double sum1,sum2,sum3,sum4;
    double a[MAX][MAX],u[MAX][MAX],l[MAX][MAX],x[MAX],y[MAX],b[MAX];
    // ���ݳ�ʼ��
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
    //ͨ�����ݵ���
    printf("����3����ֱ�����Ƿֽⷨ��ⷽ���飬\n");
    printf("��д��Doolittle�ֽ�ĵ�λ�����Ǿ���L�������Ǿ���U����ʽ\n");
    printf("\n");
    printf("����������������");
    scanf("%d",&n);
    printf("����������������");
    scanf("%d",&m);
    printf("������%d*%d��ϵ������\n",n,m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%lf",&a[i][j]);
    printf("������1*%d�ĳ�������\n",n);
    for (i=1;i<=n;i++) scanf("%lf",&b[i]);
    // ����Doolittle���Ƿֽⷨ�����󷽳�
    // ���Ƿֽ�
    nn=n;
    for (j=1;j<=nn;j++) u[1][j]=a[1][j];
    for (i=2;i<=nn;i++) l[i][1]=(1.0*a[i][1])/(u[1][1]);
    for (k=2;k<=nn;k++)
    {
        for (j=k;j<=nn;j++)
        {
            sum1=0; //��ע���ۼӱ�����ʼ��λ��
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
    // �ɻش���ʽ���δ֪����
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
    // ������
    printf("\n");
    printf("������Ľ�Ϊ��\n");
    for (i=1;i<=n;i++) printf("x%d=%.2f ",i,x[i]);
    printf("\n");
    printf("\n");
    printf("Doolittle���Ƿֽ������£�\n");
    printf("\n");
    printf("��λ�����Ǿ���LΪ��\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) printf("%6.2f",l[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("�����Ǿ���UΪ��\n");
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) printf("%6.2f",u[i][j]);
        printf("\n");
    }
    return 0;
}
