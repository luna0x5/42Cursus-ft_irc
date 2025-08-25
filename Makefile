NAME	= ircserv

HEADER	=	server/Server.hpp\
			client/Client.hpp \
			channel/Channel.hpp \
			./Inc/numericalReplies.hpp\

files	=	main.cpp \
			server/Server.cpp \
			client/Client.cpp \
			server/Server_helper.cpp\
			commands/Join.cpp \
			channel/Channel.cpp\
 			commands/Pass.cpp \
			commands/Nick.cpp \
			commands/User.cpp \
			commands/mode/mode.cpp\

obj		:= $(files:.cpp=.o)

Cpp		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98 -I./Inc

all : $(NAME)

$(NAME) : $(obj)
		$(Cpp) $(FLAGS) -o $@ $^

%.o:%.cpp $(HEADER)
		$(Cpp) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(obj)

fclean: clean
		rm -rf $(NAME)

re: fclean all4

commit:
	git add .
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"  

push:
	git add .
	git status
	git commit -m "$(filter-out $@, $(MAKECMDGOALS))"
	git push
