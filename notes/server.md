************************************* instructions *********************************************
---> create a socket by socket();
---> set up its struct infos ;
---> bind it with a specific ip that part of that struct and a specific port;
---> let the socket in listening mode with a specific num of socket queue to get the incoming connections ;
---> call poll() and initialized the listening socket and the array of fds;
---> accept if there is a new connection and create a socket to the new client and assign its fd to the array ;
---> otherwise do whatever the revent socket tells us what we should do with that socket ;
---> close socket in case of client disconnected 