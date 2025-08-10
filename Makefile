NAME = ircserv
HEADER=server/Server.hpp client/Client.hpp channel/Channel.hpp
files = main.cpp server/Server.cpp client/Client.cpp server/Server_helper.cpp server/Join.cpp channel/Channel.cpp
obj := $(files:.cpp=.o)
Cpp = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
all: $(NAME)

$(NAME) : $(obj)
		$(Cpp) $(FLAGS) -o $@ $^

%.o:%.cpp $(HEADER)
		$(Cpp) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(obj)

fclean: clean
		rm -rf $(NAME)

re: fclean all4

M =  AUTO_PUSH

push:
	git add .
	git status
	git commit -m "$(M)"
	git push