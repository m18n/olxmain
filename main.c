
#include"olxmain.h"

// variable test not forget condition variable
int main(){
   
    cl_InitClient(&cl_servdb);
    cl_InitREQPack(&cl_servdb);
    cl_ClientConnect(&cl_servdb,"192.168.0.105",9998);
    RES_db_auth_t authdb;
    CreateRES_db_auth(&authdb);
    strcpy(&authdb.authcode,"niger");
    cl_SendPack(&cl_servdb,&authdb,NULL,NULL);

    sv_server_t serv;
    sv_ServerInit(&serv,9999,10);
    InitREQPack(&serv);
    sv_ServerStart(&serv,sizeof(olxclient_t),CreateOlxClient,ClearOlxClient);
    
    return 0;
}