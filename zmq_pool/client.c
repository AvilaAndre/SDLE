#include "headers/zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();

    void *subscriberUS = zmq_socket(context, ZMQ_SUB);
    int rcUS = zmq_connect(subscriberUS, "tcp://localhost:5556");
    assert(rcUS == 0);

    //  Subscribe to US zipcode, default is NYC, 10001
    const char *filterUS = "10001 ";
    rcUS = zmq_setsockopt(subscriberUS, ZMQ_SUBSCRIBE, filterUS, strlen(filterUS));
    assert(rcUS == 0);

    void *subscriberPT = zmq_socket(context, ZMQ_SUB);
    int rcPT = zmq_connect(subscriberPT, "tcp://localhost:5557");
    assert(rcPT == 0);

    //  Subscribe to PT zipcode
    const char *filterPT = "1001 ";
    rcPT = zmq_setsockopt(subscriberPT, ZMQ_SUBSCRIBE, filterPT, strlen(filterPT));
    assert(rcPT == 0);

    zmq_pollitem_t items[] = {
        {subscriberUS, 0, ZMQ_POLLIN, 0},
        {subscriberPT, 0, ZMQ_POLLIN, 0}};

    //  Process 100 updates
    int update_nbr_US;
    long total_temp_US = 0;
    int update_nbr_PT;
    long total_temp_PT = 0;

    //  Process messages from both sockets
    while (update_nbr_PT < 100 || update_nbr_US < 100)
    {
        char msg[256];

        zmq_poll(items, 2, -1);
        if (items[0].revents & ZMQ_POLLIN)
        {
            char *string = s_recv(subscriberUS);

            int zipcode, temperature, relhumidity;
            sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
            total_temp_US += temperature;
            update_nbr_US++;

            printf ("Received US temp %d\n", temperature);

            free(string);
        }
        if (items[1].revents & ZMQ_POLLIN)
        {
            char *string = s_recv(subscriberPT);

            int zipcode, temperature, relhumidity;
            sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
            total_temp_PT += temperature;
            update_nbr_PT++;
            printf ("Received PT temp %d\n", temperature);


            free(string);
        }
    }

    printf("Average temperature for US zipcode '%s' was %dF\n", filterUS, (int)(total_temp_US / update_nbr_US));
    printf("Average temperature for PT zipcode '%s' was %dF\n", filterPT, (int)(total_temp_PT / update_nbr_PT));

    zmq_close(subscriberUS);
    zmq_close(subscriberPT);
    zmq_ctx_destroy(context);
    return 0;
}