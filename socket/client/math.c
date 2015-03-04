#include </home/hunk/桌面/client/math.h>
#include <stdio.h>

///////大数模
long long mod(long long a,long long p,long long n)
{
	long long res=1;
	a%=n;
	while(p)
	{
		if(p&1)
		{
			res*=a;
			res%=n;
		}
		p>>=1;
		a*=a;
		a%=n;
	}
	if(n!=1)
	return res;
		else
	return 0;
}

////求公约数
long long gcd(long long x, long long y)
{
	if (!x || !y) return x>y?x:y;//存在0，则返回较大数
	long long t;
	for(;t=x%y; x=y, y=t);
	return y;
}

/////检测是否是素数
int checkprime(long long n)
{
	int i;
    long long a;
    for(i=0;i<checktime;i++)
    {
    	a=rand();
        a%=n;
        if(!a)
        	continue;
        if(mod(a,n-1,n)!=1)
        	break;
	}
	if(i<checktime)
		return 0;
	else
		return 1;
}

/////生成随机素数P，大于MINp
int createp()
{
	long long a=rand()+MINp;
	if((!a&0x01))   a++;
	while(checkprime(a)==0)
		a+=2; 
	return a;
}

//////欧几里德算法，就逆
void extgcd(long long a,long long b,long long *d,long long *x,long long *y)
{
	if(!b)
	{
		*d=a;	*x=1;	*y=0;
	}
	else
	{
		extgcd(b,a%b,d,y,x);
		*y-=*x*(a/b);
	}
}
