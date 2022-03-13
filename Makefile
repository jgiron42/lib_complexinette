NAME = libcomplexinette.a

SRCS = complexinette.cpp aprox.cpp complexities_functions.cpp perf_wrapper.cpp

OBJS = $(SRCS:.cpp=.o)

CC = clang++

FLAGS = -g3

.cpp.o :
		$(CC) $(FLAGS) -c $< -o ${<:.cpp=.o}

all : $(NAME)

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re