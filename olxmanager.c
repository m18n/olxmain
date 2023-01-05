#include"olxmanager.h"
cl_client_t cl_managerdb;
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