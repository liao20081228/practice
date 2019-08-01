#include<stdio.h>

int main(void)
{
	struct st{int a,b,c;};
	struct st a;
	struct st b={1,2,3};
	struct st c={1};
	struct st d={1,};
	struct st e={1,2,3,};
	struct st f={};
	struct st g={.a=1,.b=2,g.c=3};
	struct st h={a:1,.b=2,c:3};

	printf("%d,%d,%d\n",a.a,a.b,a.c);
	printf("%d,%d,%d\n",b.a,b.b,b.c);
	printf("%d,%d,%d\n",c.a,c.b,c.c);
	printf("%d,%d,%d\n",d.a,d.b,d.c);
	printf("%d,%d,%d\n",e.a,e.b,e.c);
	printf("%d,%d,%d\n",f.a,f.b,f.c);
	printf("%d,%d,%d\n",g.a,g.b,g.c);
	printf("%d,%d,%d\n",h.a,h.b,h.c);
	return 0;
}
