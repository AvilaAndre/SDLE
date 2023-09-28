//  Weather update client
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode

#include "headers/zhelpers.h"

int main(int argc, char *argv[])
{
    //  Socket to talk to server
    printf("Collecting updates from weather server...\n");
    void *context = zmq_ctx_new();
    void *subscriberUSA = zmq_socket(context, ZMQ_SUB);
    void *subscriberPT = zmq_socket(context, ZMQ_SUB);

    int rcUSA = zmq_connect(subscriberUSA, "tcp://localhost:5556");
    assert(rcUSA == 0);
    int rcPT = zmq_connect(subscriberPT, "tcp://localhost:5557");
    assert(rcPT == 0);

    //  Subscribe to zipcode, default is NYC, 10001
    const char *filterUSA = (argc > 1) ? argv[1] : "10001 ";
    rcUSA = zmq_setsockopt(subscriberUSA, ZMQ_SUBSCRIBE, filterUSA, strlen(filterUSA));
    assert(rcUSA == 0);

    //  Subscribe to PT zipcode, default is NYC, 10001
    const char *filterPT = (argc > 1) ? argv[1] : "4200 ";
    rcPT = zmq_setsockopt(subscriberPT, ZMQ_SUBSCRIBE, filterPT, strlen(filterPT));
    assert(rcPT == 0);

    long total_tempUSA = 0;
    long total_tempPT = 0;

    int update_nbrUSA = 0;
    int update_nbrPT = 0;

    while (update_nbrUSA < 100 || update_nbrPT < 100) {
        zmq_pollitem_t items [] = {
            { subscriberUSA, 0, ZMQ_POLLIN, 0 },
            { subscriberPT, 0, ZMQ_POLLIN, 0 }
        };
        zmq_poll (items, 2, -1);
        if (items [0].revents & ZMQ_POLLIN) {
            char *string = s_recv(subscriberUSA);

            int zipcode, temperature, relhumidity;
            sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
            if (update_nbrUSA < 100) total_tempUSA += temperature;
            free(string);
            printf("%d %d \n", zipcode, temperature);
            update_nbrUSA++;
        }
        if (items [1].revents & ZMQ_POLLIN) {
            char *string = s_recv(subscriberPT);

            int zipcode, temperature, relhumidity;
            sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
            if (update_nbrPT < 100) total_tempPT += temperature;
            free(string);
            printf("%d %d \n", zipcode, temperature);
            update_nbrPT++;
        }
    }

    printf ("Average temperature for zipcode '%s' was %dF\n", filterUSA, (int) (total_tempUSA / update_nbrUSA));
    printf ("Average temperature for zipcode '%s' was %dF\n", filterPT, (int) (total_tempPT / update_nbrPT));

    //  Process 100 updates
    int update_nbr;
    zmq_close(subscriberUSA);
    zmq_close(subscriberPT);
    zmq_ctx_destroy(context);
    return 0;
}