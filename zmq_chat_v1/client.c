//  Weather update server
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates

#include "headers/zhelpers.h"

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        return 0;
    }
    char* receiverPort = argv[1];
    char* senderPort = argv[2];
    char receiverAddress[100] = "tcp://*:";
    char senderAddress[100] = "tcp://localhost:";

    strcat(receiverAddress, receiverPort);
    strcat(senderAddress, senderPort);

    printf("receiver address %s\n", receiverAddress);
    printf("sender address %s\n", senderAddress);

    //  Prepare our context and publisher
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_REP);

    int rc1 = zmq_bind(receiver, receiverAddress);

    assert(rc1 == 0);

    void *sender = zmq_socket(context, ZMQ_REQ);
    int rc2 = zmq_connect(sender, senderAddress);

    assert(rc2 == 0);

    int listening = receiverPort[3] == '5';

    int times = 0;

    while (1) {

        times += 1;
        if (times > 4) break;


        if (listening) {
            char* buffer;
            buffer = s_recv(receiver);
            printf ("<< Received %s\n", buffer);
            free(buffer);

            s_send(receiver, "ACK");  // REP needs to send a response

            listening = !listening;
        } else {
            printf (">> Sending Hello…\n");
            char msg2send[20];
            sprintf(msg2send, "Hello");
            s_send(sender, msg2send);

            s_recv(sender);  // REQ needs to receive a response

            listening = !listening;
        }

    }


    zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}