/*                                              creator by iPlugin ©
 █████╗ ██╗     ██╗███████╗███╗  ██╗████████╗     ██████╗██╗██████╗ ███████╗
██╔══██╗██║     ██║██╔════╝████╗ ██║╚══██╔══╝    ██╔════╝██║██╔══██╗██╔════╝
██║  ╚═╝██║     ██║█████╗  ██╔██╗██║   ██║       ╚█████╗ ██║██║  ██║█████╗
██║  ██╗██║     ██║██╔══╝  ██║╚████║   ██║        ╚═══██╗██║██║  ██║██╔══╝
╚█████╔╝███████╗██║███████╗██║ ╚███║   ██║       ██████╔╝██║██████╔╝███████╗
 ╚════╝ ╚══════╝╚═╝╚══════╝╚═╝  ╚══╝   ╚═╝       ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/client.h"


int main(int argc, char* argv[], char *envp[]){
    srand(time(NULL));
    // checking for correctness
    if (!(check_args(argc, argv, envp, 4)))
        return 1;

    // CLIENT
    Client client("logs/logClient.log");
    if (!(client.startClient(argv)))
        return 1;
    
// ----------------------------------------------------
    if (!(client.send_packet())) // відправляємо filename
        return 1;
    
    if (!(client.recv_packet()))
        return 1;
    

    cout << "The end" << endl;
    return 0;
}