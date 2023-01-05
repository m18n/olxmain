#pragma once

#include"../server/include/server.h"
#include"olxmanager.h"
typedef struct infosend{
    sv_user_t* user;
    int indexpack;
}infosend_t;

typedef struct olxclient{
    sv_user_t client;
    bool auth;
}olxclient_t;
void CreateOlxClient(olxclient_t* client);
void ClearOlxClient(olxclient_t* client);
typedef struct RES_sv_status{
    sv_packres_t pack;
    int code;
}RES_sv_status_t;
void CreateRES_sv_status(RES_sv_status_t* status);
sv_json_construct_t RES_sv_status_getjson(RES_sv_status_t* pk);
typedef struct REQ_sv_auth{
    sv_packreq_t pack;
    char name[100];
    char password[20];
}REQ_sv_auth_t;
void CreateREQ_sv_auth(REQ_sv_auth_t* auth);
bool REQ_sv_auth_jsontoobject(REQ_sv_auth_t* auth,json_value* values);
void REQ_sv_auth_process(REQ_sv_auth_t* auth,sv_user_t* user);

void sv_InitREQPack(sv_server_t* serv);

void ConnectManagerDb();