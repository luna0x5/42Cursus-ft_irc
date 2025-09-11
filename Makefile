NAME	= ircserv

HEADER	=	./Inc/Server.hpp        \
			./Inc/Client.hpp  \
			./Inc/Channel.hpp \
			./Inc/numericalReplies.hpp \

files	=	main.cpp \
			server/Server.cpp \
			server/Server_helper.cpp\
			client/Client.cpp \
			channel/Channel.cpp\
			commands/Join.cpp \
 			commands/Pass.cpp \
			commands/Nick.cpp \
			commands/User.cpp \
			Inc/numericalReplies.cpp \
			commands/mode/mode.cpp\
			commands/mode/utils.cpp\

obj		:= $(files:.cpp=.o)

Cpp		= c++

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
