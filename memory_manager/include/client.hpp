#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

/**
 * Function that creates the client socket and connects it to the server.
 * @return Server confirmation
 */
string run_client();

/**
 * Sends a message to the server.
 * @param msg message.
 * @return Server response.
 */
string send_msg(string msg);

/**
 * Close the client socket.
 */
void close_sock();