#include "../includes/utils.h"


int getSocket(){
    return socket(AF_INET, SOCK_STREAM, 0); // SOCK_RAW
}

int createAddr(int socketFD, const string &ip, int port, sockaddr_in &address){
    address.sin_port = htons(port);
    address.sin_family = AF_INET;

    if (ip.size() == 0){ // for server
        address.sin_addr.s_addr = INADDR_ANY;
        return bind(socketFD, (sockaddr*)&address, sizeof(address));
    }
    else{ // for client
        inet_pton(AF_INET, ip.c_str(), &address.sin_addr.s_addr);
        return connect(socketFD, (sockaddr*)&address, sizeof(address));
    }
}

bool check_args(int argc, char* argv[], char *envp[], int count){
    if (argc != count){
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
        std::string correct_form;
        switch (count){
        case 3:
            correct_form = "Correct is: " + short_name + " <ip> <port>\n";
            break;
        case 2:
            correct_form = "Correct is: " + short_name + " <port>\n";
        default:
            break;
        }

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