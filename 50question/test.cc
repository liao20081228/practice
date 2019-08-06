#include <stdio.h>
int main()
{
   int n,k;
   printf("please input the number:\n");
   scanf("%d",&n);
   for(k=2;k<n;k++)
   {
       while(k!=n)
     {
       if(n%k==0)
       {
           printf("%d\n",k);
           n=n/k;
       }
       else break;         //跳出while使k+1                
     }
   }
   printf("%d\n",n);       //打印最后一个质因数，即k等于n是的那个
    return 0;
}
