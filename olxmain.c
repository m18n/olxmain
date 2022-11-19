#include"olxmain.h"
cl_client_t cl_servdb;
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
void CreateOlxClient(olxclient_t* client){
    sv_CreateUser(&client->client);
    client->auth=false;
}
void ClearOlxClient(olxclient_t* client){

}

void CreateRES_cl_status(RES_cl_status_t* status){
    sv_CreatePackRes(&status->pack);
    status->pack.idpack=2;
    status->code=0;
    status->pack.GetJsonPack=RES_cl_status_getjson;
}
sv_json_construct_t RES_cl_status_getjson(RES_cl_status_t* pk){
    sv_json_construct_t json;
    sv_CreateJson_Construct(&json);
    sv_json_item_t code;
    sv_CreateJson_Item(&code);
    sv_json_item_setname(&code,"code");
    sv_json_item_setintvalue(&code,pk->code);
    sv_json_construct_addelement(&json,code);
    return json;
}
void CreateREQ_cl_auth(REQ_cl_auth_t* auth){
    sv_CreatePackReq(&auth->pack);
    auth->pack.JsonToObject=REQ_cl_auth_jsontoobject;
    auth->pack.ProcessPack=REQ_cl_auth_process;
}
bool REQ_cl_auth_jsontoobject(REQ_cl_auth_t* auth,json_value* values){
    json_object_entry* jname=sv_GetNameKey(values,"name");
    json_object_entry* jpassword=sv_GetNameKey(values,"password");
    if(jname!=NULL&&jname->value->type==json_string&&jpassword!=NULL&&jpassword->value->type==json_string){
        strcpy(auth->name,jname->value->u.string.ptr);
        strcpy(auth->password,jpassword->value->u.string.ptr);
        return true;
    }
    return false;
}
void REQ_cl_auth_process(REQ_cl_auth_t* auth,sv_user_t* user){
    olxclient_t* olxcl=(olxclient_t*)user;
    printf("AUTH: %s,%s\n",auth->name,auth->password);
    RES_cl_status_t status;
    CreateRES_cl_status(&status);
    
    if(strcmp(auth->name,"misha")==0&&strcmp(auth->password,"123")==0){
        status.code=1;
    }else{
        status.code=0;
    }
    // RES_db_auth_t authdb;
    // CreateRES_db_auth(&authdb);
    // strcpy(authdb);
    // cl_SendPack(&servdb,);
    sv_SendPackRes(user,&status,auth);  
}


void InitREQPack(sv_server_t* serv){
    sv_serv_adduserpacks(serv,CreateREQ_cl_auth,sizeof(REQ_cl_auth_t),1);
}