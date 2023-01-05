#include"olxmain.h"

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
    if(status->code==102){
        olxclient_t* olxcl=info->user;
        olxcl->auth=true;
    }
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
    cl_SendPack(&cl_managerdb,&check,R_CheckAuthClient,info);
}


void InitREQPack(sv_server_t* serv){
    sv_serv_adduserpacks(serv,CreateREQ_sv_auth,sizeof(REQ_sv_auth_t),1);
}
void ConnectManagerDb(){
    cl_InitClient(&cl_managerdb);
    cl_InitREQPack(&cl_managerdb);
    cl_ClientConnect(&cl_managerdb,"192.168.0.105",9998);
    RES_db_auth_t authdb;
    CreateRES_db_auth(&authdb);
    strcpy(&authdb.authcode,"niger");
    cl_SendPack(&cl_managerdb,&authdb,NULL,NULL);
}