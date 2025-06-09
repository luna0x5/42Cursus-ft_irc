#include "server/Server.hpp"

int main(){
    Server test;
    test.parse_cmd(":nick!user@host JOIN #channel :Hello everyone!");
    test.server_socket();
}