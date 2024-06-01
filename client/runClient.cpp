/*
     █████╗ ██╗     ██╗███████╗███╗  ██╗████████╗     ██████╗██╗██████╗ ███████╗
    ██╔══██╗██║     ██║██╔════╝████╗ ██║╚══██╔══╝    ██╔════╝██║██╔══██╗██╔════╝
    ██║  ╚═╝██║     ██║█████╗  ██╔██╗██║   ██║       ╚█████╗ ██║██║  ██║█████╗
    ██║  ██╗██║     ██║██╔══╝  ██║╚████║   ██║        ╚═══██╗██║██║  ██║██╔══╝
    ╚█████╔╝███████╗██║███████╗██║ ╚███║   ██║       ██████╔╝██║██████╔╝███████╗
     ╚════╝ ╚══════╝╚═╝╚══════╝╚═╝  ╚══╝   ╚═╝       ╚═════╝ ╚═╝╚═════╝ ╚══════╝
*/

#include "../includes/client.h"


bool check_args(int argc, char* argv[], char *envp[]);

int main(int argc, char* argv[], char *envp[]){
    // checking for correctness
    if (!(check_args(argc, argv, envp))){
        return 1;
    }
    
    // create client
    Client client("logs/logClient.log");
    if (!(client.startClient(argc, argv)))
        return 1;
    
    
    // clinet.send_pkg();
    // clinet.recv_pkg();



    cout << "The end" << endl;
    return 0;
}


bool check_args(int argc, char* argv[], char *envp[]){
    if (argc != 3){
        const char *user_prefix = "USER=";
        const char *user_value = nullptr;

        // Search username
        for (int i = 0; envp[i] != nullptr; ++i){
            if (strncmp(envp[i], user_prefix, strlen(user_prefix)) == 0){
                user_value = envp[i] + strlen(user_prefix);
                break;
            }
        }

        std::string short_name(program_invocation_name);
        std::string correct_form = "Correct is: " + short_name + " <ip> <port>\n";

        // Print error
        if (user_value != nullptr){
            std::cerr << "Dear " << BOLDGREEN << user_value << RESET
                << ", you can not do this!\n" << correct_form;
        }
        else{
            std::cerr << "Dear user, you can not do this!\n" << correct_form;
        }
        return false;
    }
    return true;
}