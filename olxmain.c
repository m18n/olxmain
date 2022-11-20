#include"olxmain.h"
cl_client_t cl_servdb;
void CreateREQ_db_status(REQ_db_status_t* status){
    cl_CreatePackReq(&status->pack);
    status->pack.JsonToObject=REQ_db_status_jsontoobject;
    status->pack.ProcessPack=REQ_db_status_process;
    status->code=-1;
}
bool REQ_db_status_jsontoobject(REQ_db_status_t* status,json_value* values){
    json_object_entry* jcode=cl_GetNameKey(values,"code");
    if(jcode!=NULL&&jcode->value->type==json_integer){
        status->code=jcode->value->u.integer;
        return true;
    }
    return false;
}
void REQ_db_status_process(REQ_db_status_t* status){
    printf("STATUS: %d\n",status->code);
}
void CreateRES_db_auth(RES_db_auth_t* auth){
    cl_CreatePackRes(&auth->pack);
    auth->pack.GetJsonPack=RES_db_auth_getjson;
    auth->pack.idpack=1;
}
cl_json_construct_t RES_db_auth_getjson(RES_db_auth_t* auth){
    cl_json_construct_t json;
    cl_CreateJson_Construct(&json);
    cl_json_item_t authcode;
    cl_CreateJson_Item(&authcode);
    cl_json_item_setname(&authcode,"authcode");
    cl_json_item_setstrvalue(&authcode,auth->authcode);
    cl_json_construct_addelement(&json,authcode);
    return json;
}

void CreateRES_db_authclient(RES_db_authclient_t* auth){
    cl_CreatePackRes(&auth->pack);
    auth->pack.GetJsonPack=RES_db_authclient_getjson;
    auth->pack.idpack=3;
}
cl_json_construct_t RES_db_authclient_getjson(RES_db_authclient_t* auth){
    cl_json_construct_t json;
    cl_CreateJson_Construct(&json);
    cl_json_item_t name;
    cl_CreateJson_Item(&name);
    cl_json_item_setname(&name,"name");
    cl_json_item_setstrvalue(&name,auth->name);
    cl_json_construct_addelement(&json,name);
    cl_json_item_t password;
    cl_CreateJson_Item(&password);
    cl_json_item_setname(&password,"password");
    cl_json_item_setstrvalue(&password,auth->password);
    cl_json_construct_addelement(&json,password);
    return json;
}
void cl_InitREQPack(cl_client_t* cl){
    cl_client_adduserpacks(cl,CreateREQ_db_status,sizeof(REQ_db_status_t),2);
}
void CreateOlxClient(olxclient_t* client){
    sv_CreateUser(&client->client);
    client->auth=false;
}
void ClearOlxClient(olxclient_t* client){

}

void CreateRES_sv_status(RES_sv_status_t* status){
    sv_CreatePackRes(&status->pack);
    status->pack.idpack=2;
    status->code=0;
    status->pack.GetJsonPack=RES_sv_status_getjson;
}
sv_json_construct_t RES_sv_status_getjson(RES_sv_status_t* pk){
    sv_json_construct_t json;
    sv_CreateJson_Construct(&json);
    sv_json_item_t code;
    sv_CreateJson_Item(&code);
    sv_json_item_setname(&code,"code");
    sv_json_item_setintvalue(&code,pk->code);
    sv_json_construct_addelement(&json,code);
    return json;
}
void CreateREQ_sv_auth(REQ_sv_auth_t* auth){
    sv_CreatePackReq(&auth->pack);
    auth->pack.JsonToObject=REQ_sv_auth_jsontoobject;
    auth->pack.ProcessPack=REQ_sv_auth_process;
}
bool REQ_sv_auth_jsontoobject(REQ_sv_auth_t* auth,json_value* values){
    json_object_entry* jname=sv_GetNameKey(values,"name");
    json_object_entry* jpassword=sv_GetNameKey(values,"password");
    if(jname!=NULL&&jname->value->type==json_string&&jpassword!=NULL&&jpassword->value->type==json_string){
        strcpy(auth->name,jname->value->u.string.ptr);
        strcpy(auth->password,jpassword->value->u.string.ptr);
        return true;
    }
    return false;
}
void R_CheckAuthClient(REQ_db_status_t* status,void* data){
    infosend_t* info=data;
    //printf("\nAUTH CODE:%d %d %d\n",status->code,info->user->pollptr->fd,info->indexpack);
    RES_sv_status_t sv_status;
    CreateRES_sv_status(&sv_status);
    sv_status.code=status->code;
    sv_SendPackResIndex(info->user,&sv_status,info->indexpack);
    
    free(data);
}
void REQ_sv_auth_process(REQ_sv_auth_t* auth,sv_user_t* user){
    olxclient_t* olxcl=(olxclient_t*)user;
    RES_db_authclient_t check;
    CreateRES_db_authclient(&check);
    strcpy(check.name,auth->name);
    strcpy(check.password,auth->password);
    infosend_t* info=malloc(sizeof(infosend_t));
    info->indexpack=auth->pack.indexpack;
    info->user=user;
    cl_SendPack(&cl_servdb,&check,R_CheckAuthClient,info);
}


void InitREQPack(sv_server_t* serv){
    sv_serv_adduserpacks(serv,CreateREQ_sv_auth,sizeof(REQ_sv_auth_t),1);
}