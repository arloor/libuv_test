//
// Created by arloor on 2020/3/26.
//



#ifndef LIBUV_TEST_CLOSE_CALLBACK_H
#define LIBUV_TEST_CLOSE_CALLBACK_H

void free_client(uv_stream_t *client){
    if(client->data!=NULL){
        free(client->connect_req);
        free(client->data);
        client->data=NULL;
    }
    free(client);
}
#endif //LIBUV_TEST_CLOSE_CALLBACK_H
