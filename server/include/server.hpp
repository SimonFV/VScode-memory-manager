#ifndef SERVER
#define SERVER

#include <VSPtr.hpp>
/**
 * Start the socket server
 * The server will wati requests from the client and will send back the response.
 * 
 * @return Result of the operation as response.
 */
int run_server();

/**
 * Process the information received.
 * 
 * @param info string send by the client.
 * @return response to the client.
 */
string process(string info);

/**
 * Instantiates the value on the server based on the information received.
 * 
 * @param ID VSPtr new ID.
 * @param type VSPtr new type.
 * @param value VSPtr new value.
 * @param key operation to the VSPtr.
 */
string add_info(string ID, string type, string value, string key);

/**
 * Saves the user info in a JSON file.
 * @param user_name
 * @param user_pass
 */
void save_user(string user_name, string user_pass);

string check_user(string user_name, string user_pass);

#endif