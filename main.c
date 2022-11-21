
#include"olxmain.h"
// void Send(){
//     pthread_mutex_lock(&mutex);
//     printf("START SEND %d\n",a);
//     a=20;
//     sleep(5);
//     printf("END SEND %d\n",a);
//     pthread_mutex_unlock(&mutex);
// }
// void test(){
//     pthread_t thread;
//     pthread_create(&thread, NULL, Send, NULL);
//     pthread_create(&thread, NULL, Send, NULL);
//     a=30;
//     printf("\n%d\n",a);
//     sleep(20);
// }
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