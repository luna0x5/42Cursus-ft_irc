NAME	=	ircserv

NAME_B	=	irc_bot

HEADER	=	./Inc/Server.hpp \
			./Inc/Client.hpp  \
			./Inc/Channel.hpp  \
			./Inc/numericalReplies.hpp \

B_HEADER =	bonus/bot/botClient.hpp \
			bonus/Inc/bot.hpp.hpp \

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


B_files	=	bonus/main.cpp \
			bonus/bot/botClient.cpp \
			bonus/bot/botActions.cpp \
			bonus/tools.cpp			  \

obj		:= $(files:.cpp=.o)

B_obj		:= $(B_files:.cpp=.o)

Cpp		=	c++

FLAGS	=  -Wall -Wextra -Werror -std=c++98  -I./Inc

all : $(NAME)

bonus: $(NAME_B)

$(NAME) : $(obj)
	@$(Cpp) $(FLAGS) $(obj) -o $(NAME)

$(NAME_B) : $(B_obj)
	@$(Cpp) $(FLAGS) $(B_obj) -o $(NAME_B)

%.o: %.cpp $(HEADER)
	$(Cpp) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(obj) $(B_obj)

fclean: clean
		rm -rf $(NAME) $(NAME_B)

re: fclean all

commit: fclean
		git add .
		git commit -m "$(filter-out $@, $(MAKECMDGOALS))"  

push: fclean
		git add .
		git status
		git commit -m "$(filter-out $@, $(MAKECMDGOALS))"
		git push
