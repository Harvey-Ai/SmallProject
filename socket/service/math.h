#define MINk 1e1//////最小k值
#define checktime 10////检测次数
#define MINp 1e1////最小p值
#define MINa 1e1/////最小a值
///////大数模
long long mod(long long a,long long p,long long n);

/////检测是否是素数
int checkprime(long long n);

/////生成随机素数P，大于MINp
int createp();

//////欧几里德算法，求逆
void extgcd(long long a,long long b,long long *d,long long *x,long long *y);

////求公约数
long long gcd(long long x, long long y);
