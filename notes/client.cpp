#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr int SERVER_PORT = 6667;
constexpr int BUFFER_SIZE = 1024;

void send_line(int sockfd, const std::string& msg) {
    std::string with_crlf = msg + "\r\n";
    send(sockfd, with_crlf.c_str(), with_crlf.size(), 0);
}

void receive_from_server(int sockfd) {
    char buffer[BUFFER_SIZE];
    while (true) {
        ssize_t bytes = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) {
            std::cout << "Server disconnected.\n";
            break;
        }
        buffer[bytes] = '\0';
        std::cout << "Server: " << buffer;
    }
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }

    std::cout << "Connected to server.\n";

    std::thread receiver(receive_from_server, sockfd);

    std::string input;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;

        if (input == "/quit") break;

        send_line(sockfd, input);
    }

    close(sockfd);
    receiver.join();
    return 0;
}

