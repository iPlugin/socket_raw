/*
     ██████╗███████╗██████╗ ██╗   ██╗███████╗██████╗    ██████╗██╗██████╗ ███████╗
    ██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗  ██╔════╝██║██╔══██╗██╔════╝
    ╚█████╗ █████╗  ██████╔╝╚██╗ ██╔╝█████╗  ██████╔╝  ╚█████╗ ██║██║  ██║█████╗  
     ╚═══██╗██╔══╝  ██╔══██╗ ╚████╔╝ ██╔══╝  ██╔══██╗   ╚═══██╗██║██║  ██║██╔══╝  
    ██████╔╝███████╗██║  ██║  ╚██╔╝  ███████╗██║  ██║  ██████╔╝██║██████╔╝███████╗
    ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝  ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/server.h"


int main(int argc, char* argv[], char *envp[]){
    // checking for correctness
    if (!(check_args(argc, argv, envp, 3)))
        return 1;
    
    // server
    Server server("logs/logServer.log");
    if (!(server.startServer(argv)))
        return 1;
    
    if (!(server.recv_packet()))
        return 1;
    
    if (!(server.send_packet("Hello client")))
        return 1;

    cout << "The end" << endl;
    return 0;
}