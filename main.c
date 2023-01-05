
#include"olxmain.h"
int main(){

    ConnectManagerDb();
    sv_server_t serv;
    sv_ServerInit(&serv,9999,10);
    InitREQPack(&serv);
    sv_ServerStart(&serv,sizeof(olxclient_t),CreateOlxClient,ClearOlxClient);
    
    return 0;
}