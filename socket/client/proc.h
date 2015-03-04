//加密
void encode(int m);

///取得公钥
void getPK(int socketfd);

///发送消息
void sendmsgg(int socketfd);

long long y,p,g;/////公钥

long long c1,c2;///////密文c1,c2
