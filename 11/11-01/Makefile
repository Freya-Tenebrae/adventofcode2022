NAME=11-1.out

SRCS=main.cpp Monkey.cpp
OBJS=$(SRCS:.cpp=.o)
INCS=Monkey.hpp

CC=clang++
CFLAGS=-Wall -Wextra -Werror -g3
INCLUDES=$(addprefix -I , $(INCS))

RM=rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean 
	make all