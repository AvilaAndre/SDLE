#include "headers/zhelpers.h"

int main(void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");
    assert(rc == 0);

    while (1)
    {
        char *buffer;
        buffer = s_recv(responder);
        printf("Received %s \n", buffer);
        sleep(1); //  Do some 'work'
        s_send(responder, "World");
    }
    return 0;
}