/*
    ██████╗ ██████╗  █████╗ ██╗  ██╗██╗   ██╗   ██████╗██╗██████╗ ███████╗
    ██╔══██╗██╔══██╗██╔══██╗╚██╗██╔╝╚██╗ ██╔╝  ██╔════╝██║██╔══██╗██╔════╝
    ██████╔╝██████╔╝██║  ██║ ╚███╔╝  ╚████╔╝   ╚█████╗ ██║██║  ██║█████╗
    ██╔═══╝ ██╔══██╗██║  ██║ ██╔██╗   ╚██╔╝     ╚═══██╗██║██║  ██║██╔══╝
    ██║     ██║  ██║╚█████╔╝██╔╝╚██╗   ██║     ██████╔╝██║██████╔╝███████╗
    ╚═╝     ╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝   ╚═╝     ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/proxy.h"


int main(int argc, char* argv[], char *envp[]){
    // checking for correctness
    if (!(check_args(argc, argv, envp, 3)))
        return 1;

    // proxy
    Proxy proxy("logs/logProxy.log");
    if (!(proxy.startProxy(argc, argv)))
        return 1;
    else
        // proxy.msg_send("Hello world");
    

    cout << "The end" << endl;
    return 0;
}