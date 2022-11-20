#pragma once
#include"../client/include/client.h"
#include"../server/include/server.h"
extern cl_client_t cl_servdb;

typedef struct infosend{
    sv_user_t* user;
    int indexpack;
}infosend_t;
typedef struct REQ_db_status{   
    cl_packreq_t pack;
    int code;
}REQ_db_status_t;
void CreateREQ_db_status(REQ_db_status_t* status);
bool REQ_db_status_jsontoobject(REQ_db_status_t* status,json_value* values);
void REQ_db_status_process(REQ_db_status_t* status);

typedef struct RES_db_auth{
    cl_packres_t pack;
    char authcode[200];
}RES_db_auth_t;
void CreateRES_db_auth(RES_db_auth_t* auth);
cl_json_construct_t RES_db_auth_getjson(RES_db_auth_t* auth);
void R_CheckAuthClient(REQ_db_status_t* status,void* data);
typedef struct RES_db_authclient{
    cl_packres_t pack;
    char name[100];
    char password[20];
}RES_db_authclient_t;
void CreateRES_db_authclient(RES_db_authclient_t* auth);
cl_json_construct_t RES_db_authclient_getjson(RES_db_authclient_t* auth);
void cl_InitREQPack(cl_client_t* cl);


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

