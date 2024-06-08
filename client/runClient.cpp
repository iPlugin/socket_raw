/*
     █████╗ ██╗     ██╗███████╗███╗  ██╗████████╗     ██████╗██╗██████╗ ███████╗
    ██╔══██╗██║     ██║██╔════╝████╗ ██║╚══██╔══╝    ██╔════╝██║██╔══██╗██╔════╝
    ██║  ╚═╝██║     ██║█████╗  ██╔██╗██║   ██║       ╚█████╗ ██║██║  ██║█████╗
    ██║  ██╗██║     ██║██╔══╝  ██║╚████║   ██║        ╚═══██╗██║██║  ██║██╔══╝
    ╚█████╔╝███████╗██║███████╗██║ ╚███║   ██║       ██████╔╝██║██████╔╝███████╗
     ╚════╝ ╚══════╝╚═╝╚══════╝╚═╝  ╚══╝   ╚═╝       ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/client.h"
#include "../includes/utils.h"


int main(int argc, char* argv[], char *envp[]){
    // checking for correctness
    if (!(check_args(argc, argv, envp, 3)))
        return 1;
    
    // client
    Client client("logs/logClient.log");
    if (!(client.startClient(argc, argv)))
        return 1;
    else{
        // client.msg_send("Hello world");
    }
    

    cout << "The end" << endl;
    return 0;
}