/*                                                creator by iPlugin ©
 █████╗ ██╗     ██╗███████╗███╗  ██╗████████╗     ██████╗██╗██████╗ ███████╗
██╔══██╗██║     ██║██╔════╝████╗ ██║╚══██╔══╝    ██╔════╝██║██╔══██╗██╔════╝
██║  ╚═╝██║     ██║█████╗  ██╔██╗██║   ██║       ╚█████╗ ██║██║  ██║█████╗
██║  ██╗██║     ██║██╔══╝  ██║╚████║   ██║        ╚═══██╗██║██║  ██║██╔══╝
╚█████╔╝███████╗██║███████╗██║ ╚███║   ██║       ██████╔╝██║██████╔╝███████╗
 ╚════╝ ╚══════╝╚═╝╚══════╝╚═╝  ╚══╝   ╚═╝       ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/client.h"


int main(int argc, char* argv[], char *envp[]) {
    srand(time(NULL));- // use random_device instead
    // checking for correctness
    // if argc != 4 { printWorngArgMessage() }
    if (!(check_args(argc, argv, envp, 4)))
        return 1;

    // CLIENT
    Client client("logs/logClient.log");
    // client.run()
    if (!(client.startClient(argv)))
        return 1;
    
    // Not clear which packet is about to be sent
    if (!(client.sendPacket())) // відправляємо filename
        return 1;
    
    if (!(client.recvPacket()))
        return 1;
    
    return 0;
}