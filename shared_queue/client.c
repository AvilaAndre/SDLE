#include "headers/zhelpers.h"

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char* buffer;
        printf ("Sending Hello %d…\n", request_nbr);
        char msg2send[20];
        sprintf(msg2send, "%s %d", "Hello", request_nbr);
        s_send(requester, msg2send);
        buffer = s_recv(requester);
        printf ("Received World %d\n", request_nbr);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}