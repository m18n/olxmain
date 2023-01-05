#pragma once
#include"../client/include/client.h"
extern cl_client_t cl_managerdb;
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
