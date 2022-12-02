NAME=02-2.out

SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)
INCS=

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