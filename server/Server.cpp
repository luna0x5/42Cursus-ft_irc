#include "Server.hpp"

int Server::server_socket(){
    Socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(8080); //check if this port is available
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    if (bind(Socket_fd, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) == -1){
        // perror("bind failed")
        close(Socket_fd);
        exit(1);
    }
    if (listen(Socket_fd, 15) == -1){
        // perror("listen failed")
        close(Socket_fd);
        exit(1);
    }

    sockaddr_in clientAdress;
    socklen_t len = sizeof(clientAdress);
    while(true){
    int new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);

    char buffer[1000];
    int bytes = recv(new_socket, buffer, sizeof(buffer), 0);
    if(bytes <= 0){
        // perror("recv data");
        close(new_socket);
    }
    std::cout<<"recieved data : "<<buffer<<std::endl;
    // instead of default 0 we can use MSG_DONTWAIT to non-blocking (return immediately if no data)
    }
//poll() for non-blocking
}
