************************************* instructions *********************************************
---> create a socket by socket() ;
---> set up its struct infos ;
---> bind it with a specific ip that part of that struct and a specific port ;
---> let the socket in listening mode with a specific num of socket queue to get the incoming connections ;
---> call poll() and initialized the listening socket and the array of fds;
---> accept if there is a new connection and create a socket to the new client and assign its fd to the array ;
---> otherwise do whatever the revent socket tells us what we should do with that socket ;
---> close socket in case of client disconnected ;

================== JOIN Pseudo-code ==================
              
******** Channel exist

----> Password exist
(
--> Key matches password
-> Join channel

--> Key doesn't match password
-> REP Error
)

----> Password doesn't exist
(
--> Join channel
)

******** Channel doesn't exist

----> Create Channel
----> Join channel
----> set as operator


(am i should check if that client is registered or not in each command or somewhere else that handle all other commands)




========split========
std::string jj
stringstream buffer(line)
std::getline(buffer, jj, ',');
push jj to the vector of channels || keys depends on ...

