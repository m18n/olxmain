#pragma once
#include"../client/include/client.h"
#include"../server/include/server.h"
extern cl_client_t cl_servdb;

typedef struct RES_db_auth{
    cl_packres_t pack;
    char authcode[200];
}RES_db_auth_t;
void CreateRES_db_auth(RES_db_auth_t* auth);
cl_json_construct_t RES_db_auth_getjson(RES_db_auth_t* auth);
typedef struct olxclient{
    sv_user_t client;
    bool auth;
}olxclient_t;
void CreateOlxClient(olxclient_t* client);
void ClearOlxClient(olxclient_t* client);
typedef struct RES_cl_status{
    sv_packres_t pack;
    int code;
}RES_cl_status_t;
void CreateRES_cl_status(RES_cl_status_t* status);
sv_json_construct_t RES_cl_status_getjson(RES_cl_status_t* pk);
typedef struct REQ_cl_auth{
    sv_packreq_t pack;
    char name[100];
    char password[20];
}REQ_cl_auth_t;
void CreateREQ_cl_auth(REQ_cl_auth_t* auth);
bool REQ_cl_auth_jsontoobject(REQ_cl_auth_t* auth,json_value* values);
void REQ_cl_auth_process(REQ_cl_auth_t* auth,sv_user_t* user);

void InitREQPack(sv_server_t* serv);

