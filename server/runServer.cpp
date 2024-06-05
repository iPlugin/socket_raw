/*
     ██████╗███████╗██████╗ ██╗   ██╗███████╗██████╗    ██████╗██╗██████╗ ███████╗
    ██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗  ██╔════╝██║██╔══██╗██╔════╝
    ╚█████╗ █████╗  ██████╔╝╚██╗ ██╔╝█████╗  ██████╔╝  ╚█████╗ ██║██║  ██║█████╗  
     ╚═══██╗██╔══╝  ██╔══██╗ ╚████╔╝ ██╔══╝  ██╔══██╗   ╚═══██╗██║██║  ██║██╔══╝  
    ██████╔╝███████╗██║  ██║  ╚██╔╝  ███████╗██║  ██║  ██████╔╝██║██████╔╝███████╗
    ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝  ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/server.h"
#include "../includes/utils.h"


int main(int argc, char* argv[], char *envp[]){
    // checking for correctness
    if (!(check_args(argc, argv, envp, 2)))
        return 1;
    
    // server
    Server server("logs/logServer.log");
    if (!(server.startServer(argc, argv)))
        return 1;
    
    // string message = "Hello world!";
    // server.send_pkg(message);
    // // clinet.recv_pkg();



    cout << "The end" << endl;
    return 0;
}