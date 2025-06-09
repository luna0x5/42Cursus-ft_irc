#include "Server.hpp"

int Server::server_socket(){
    Socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int flag = fcntl(Socket_fd, F_GETFL, 0);
    fcntl(Socket_fd, F_SETFL, flag | O_NONBLOCK);

    sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(6667); //check if this port is available
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    if (bind(Socket_fd, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) == -1){
        // perror("bind failed")
        close(Socket_fd);
        exit(1); // replace all exit() by break or continue depends on situation
    }

    if (listen(Socket_fd, 15) == -1){
        // perror("listen failed")
        close(Socket_fd);
        exit(1);
    }
    //add the listening socket to the pollfd vector
    pollfd listen_fd;
    listen_fd.fd = Socket_fd;
    listen_fd.events = POLLIN;
    poll_fds.push_back(listen_fd);

    while(true){
        int monitor = poll(poll_fds.data(), poll_fds.size(), -1);
        if (monitor < 0){
            return(1);
        }
        for (size_t i=0 ; i < poll_fds.size() ; i++){
            if (poll_fds[i].revents & POLLIN){
                if (poll_fds[i].fd == Socket_fd){
                    sockaddr_in clientAdress;
                    socklen_t len = sizeof(clientAdress);
                    int new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);
                    int flags = fcntl(new_socket, F_GETFL, 0);
                    fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
                    pollfd new_fd;
                    new_fd.fd = new_socket;
                    new_fd.events = POLLIN;
                    poll_fds.push_back(new_fd);
                    client[new_fd.fd] = Client(); //create a new object of client and add it to the map by its fd as a key
                }
                else{
                    char buffer[1048];
                    memset(buffer, 0, sizeof(buffer));
                    int bytes = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytes <= 0){
                        close(poll_fds[i].fd); //client deconnecte
                        std::cout<<"client : "<<poll_fds[i].fd<<" deconnecte"<<std::endl;
                        //erase the specific client  client[poll_fds[i].fd]
                        poll_fds.erase(poll_fds.begin() + i);
                    }
                    else{
                        buffer[bytes] = '\0';
                        client[poll_fds[i].fd].AddBuffer(buffer);
                        client[poll_fds[i].fd].extract_cmds();
                        handle_client_data(poll_fds[i].fd);
                        // std::cout<< "Received : "<<client[poll_fds[i].fd].getBuffer()<< " from :" <<poll_fds[i].fd<< "size : "<< client[poll_fds[i].fd].getBuffer().size() <<std::endl;
                    }
                }
            }
        }
    }
}

//i will split this code into small functions later

void Server::handle_client_data(int fd){
    std::vector<std::string>& cmd = client[fd].getCmds();
    for(size_t i=0; i< cmd.size(); i++){
        //parse cmd
        //if else statement or switch with enums cmds to execute each cmd
        //each command executed must erase from cmd
        std::cout<<"cmd"<<i<<" : "<<cmd[i]<<std::endl;
    }
}

void Server::parse_cmd(std::string cmd){

    std::vector<std::string> line; // i will use the line from class attrbutes
    std::string message = "";
    std::string prefix = "";
    std::string command = "";
    std::string target = "";
    size_t pos = cmd.find(" :");
    if (pos != std::string::npos){
        message = cmd.substr(pos + 2);
        cmd.erase(pos);
    }
    std::stringstream bf(cmd);
    if (cmd[0] == ':'){
        bf>>prefix;
        prefix.erase(0,1);
    }
    bf>>command;
    bf>>target;
    if (!command.empty()){
        line.push_back(command);
    }
    if (!target.empty()){
        line.push_back(target);
    }
    if (!message.empty()){
        line.push_back(message);
    }
    if (!prefix.empty()){
        line.push_back(prefix);
    }

    for(size_t i=0; i < line.size(); i++){
        std::cout<< i << " : "<< line[i]<<std::endl;
    }
    commands_handler(line);
    //call another function that will send the cammand to its specific handler


    //extract the last param " :" if it exist and store it as a message and erase it
    //if ':' the first character then we will store it as a prefix and erase it
    //push the next string (command) to be the first string
    //push the target if it exist
    //and then push the message (params) if they exist
    //push the prefix variable if it's not empty
}


void Server::commands_handler(std::vector<std::string> line){
    if (line[0] == "JOIN"){
        std::cout<<"join"<<std::endl;
    }
}
