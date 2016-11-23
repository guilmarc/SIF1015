#include "receptioncontroller.h"

ReceptionController::ReceptionController() {}

ReceptionController::ReceptionController(MessagableInterface* context) : BaseController(context)
{
    this->pushMessageToContext("Reception initialized");
}


void ReceptionController::readMessages()
{

}

void ReceptionController::initRead()
{
    /*int clientFifoFd;
    Info_FIFO_Transaction transaction;
    char clientFifo[256];

    transaction.pid_client = getpid();
    sprintf(clientFifo, CLIENT_FIFO_NAME, my_data.client_pid);
    if (mkfifo(clientFifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
        exit(EXIT_FAILURE);
    }

// For each of the five loops, the client data is sent to the server.
// Then the client FIFO is opened (read-only, blocking mode) and the data read back.
// Finally, the server FIFO is closed and the client FIFO removed from memory.

    for (times_to_send = 0; times_to_send < 5; times_to_send++) {
        sprintf(my_data.some_data, "Hello from %d", my_data.client_pid);
        printf("%d sent %s, ", my_data.client_pid, my_data.some_data);
        write(server_fifo_fd, &my_data, sizeof(my_data));
        clientFifoFd = open(clientFifo, O_RDONLY);
        if (clientFifo_fd != -1) {
            if (read(clientFifoFd, &my_data, sizeof(my_data)) > 0) {
                printf("received: %s\n", my_data.some_data);
            }
            close(clientFifoFd);
        }
    }
    unlink(clientFifo);
    exit(EXIT_SUCCESS);*/
}

void ReceptionController::pushMessageToContext(QString message)
{
    this->getContext()->pushReceptionResponse(message);
}
