/////生成公钥,g,p,y
void creatKey();

/////解密
void decode();

/////发布公钥
void sendPK(int sockfd);

/////取得密文
void getmsg(int sockfd);

long long p,g,y;///公钥p,g,y;

long long a;///密钥a


