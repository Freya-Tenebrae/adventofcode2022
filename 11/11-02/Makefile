NAME=11-2.out

SRCS=main.cpp Monkey.cpp Item.cpp
OBJS=$(SRCS:.cpp=.o)
INCS=Monkey.hpp Item.hpp

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