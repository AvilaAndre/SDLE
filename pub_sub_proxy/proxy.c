//  Simple request-reply broker

#include "headers/zhelpers.h"

int main(void)
{
    //  Prepare our context and sockets
    void *context = zmq_ctx_new();
    void *frontend = zmq_socket(context, ZMQ_XSUB);
    int rc = zmq_bind(frontend, "tcp://*:5555");
    assert(rc==0);

    void *backend = zmq_socket(context, ZMQ_XPUB);
    rc = zmq_bind(backend, "tcp://*:5556");
    assert(rc==0);

    zmq_proxy(frontend, backend, NULL);

    //  We never get here, but clean up anyhow
    zmq_close(frontend);
    zmq_close(backend);
    zmq_ctx_destroy(context);
    return 0;
}