//  Weather update server
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates

#include "headers/zhelpers.h"
#include <unistd.h>

#define BUFFER_SIZE 255

int main(int argc, char *argv[])
{

    int clientID;

    sscanf(argv[1], "%d", &clientID);

    // Prepare our context and publisher
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc1 = zmq_connect(publisher, "tcp://localhost:5555");
    assert(rc1 == 0);

    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc2 = zmq_connect(subscriber, "tcp://localhost:5556");
    assert(rc2 == 0);

    //  Subscribe to topic
    const char *filter = "group_msg ";
    rc2 = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    assert(rc2 == 0);

    zmq_pollitem_t items[] = {
        {subscriber, 0, ZMQ_POLLIN, 0},
        {NULL, STDIN_FILENO, ZMQ_POLLIN, 0}};

    printf("clientID %d \n", clientID);

    while (1)
    {
        zmq_poll(items, 2, -1);

        if (items[0].revents & ZMQ_POLLIN)
        {
            char *string = s_recv(subscriber);

            char *topic;
            int *id;
            char *msg;
            msg = malloc(BUFFER_SIZE * sizeof(char));

            memset(msg, 0, BUFFER_SIZE);
            sscanf(string, "%s %d %254c", &topic, &id, msg);

            
            // print only if not my own message
            if (id != clientID) printf(">> <%d> %s", id, msg);

            // there is a bug where it shows the last message, ex: 1 -> ja esta 2-> :)) the terminal shows 'sta'

            free(string);
            free(msg);
        }
        if (items[1].revents & ZMQ_POLLIN)
        {
            char* inBuffer[BUFFER_SIZE];

            int charsRead = read(STDIN_FILENO, inBuffer, BUFFER_SIZE);

            inBuffer[charsRead] = '\0';

            char* msg[BUFFER_SIZE + 20];

            sprintf(msg, "group_msg %d %s", clientID, inBuffer);
            s_send(publisher, msg);

            fflush(STDIN_FILENO);
        }
    }

    printf("switching to subscriber\n");

    zmq_close(subscriber);
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}