NAME	=	ircserv

HEADER	=	./Inc/Server.hpp        \
			./Inc/Client.hpp  \
			./Inc/Channel.hpp \
			./Inc/numericalReplies.hpp \

files	=	main.cpp \
			mandatory/server/Server.cpp \
			mandatory/server/Server_helper.cpp\
			mandatory/client/Client.cpp \
			mandatory/channel/Channel.cpp\
			mandatory/commands/Join.cpp \
 			mandatory/commands/Pass.cpp \
			mandatory/commands/Nick.cpp \
			mandatory/commands/User.cpp \
			mandatory/commands/Kick.cpp \
			mandatory/commands/Invite.cpp \
			mandatory/commands/Privmsg.cpp \
			mandatory/commands/Topic.cpp \
			mandatory/commands/mode/mode.cpp\
			mandatory/commands/mode/utils.cpp\
			bonus/bot/bot.cpp

obj		:= $(files:.cpp=.o)

Cpp		=	c++

FLAGS	=  -Wall -Wextra -Werror -std=c++98  -I./Inc

all : $(NAME)


$(NAME) : $(obj)
	@$(Cpp) $(FLAGS) $(obj) $(LIBRARY) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(Cpp) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(obj)

fclean: clean
		rm -rf $(NAME)

re: fclean all

commit: fclean
		git add .
		git commit -m "$(filter-out $@, $(MAKECMDGOALS))"  

push: fclean
		git add .
		git status
		git commit -m "$(filter-out $@, $(MAKECMDGOALS))"
		git push
