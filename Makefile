##
## EPITECH PROJECT, 2022
## minishell1
## File description:
## Makefile
##

SRC				:=	src/main.c \

RELEASE_OUT		:= 	mysh
DEBUG_OUT		:= 	mysh_debug

BUILD_DIR		:=  build
RELEASE_DIR 	:= 	build/release
DEBUG_DIR		:= 	build/debug

CC				:=	gcc
CFLAGS			:=	-I./include/ -MMD -MP
LDFLAGS			:=

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o))
RELEASE_FLAGS	:=	-O1

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o))
DEBUG_FLAGS		:=	-g3 -Wall -Wextra -Wpedantic \
					-fsanitize=address -fsanitize=undefined

reset			:=  \033[0m
bold			:= 	\033[1m
underline		:= 	\033[4m
green			:=  \033[32m
blue			:= 	\033[34m
grey 			:= 	\033[90m

all: release

-include $(addprefix $(RELEASE_DIR)/,$(SRC:.c=.d))
-include $(addprefix $(DEBUG_DIR)/,$(SRC:.c=.d))

## BUILD ##

release: $(RELEASE_OUT)
	@printf "$(bold)$(green)$(RELEASE_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)release$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(RELEASE_OUT)$(reset)\n"

debug: $(DEBUG_OUT)
	@printf "$(bold)$(green)$(DEBUG_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)debug$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(DEBUG_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): $(RELEASE_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): $(DEBUG_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

## OBJECTS ##

$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

## RUN ##

run: release
	@printf "$(bold)$(blue)running $(RELEASE_OUT) ...$(reset)\n"
	./$(RELEASE_OUT)

run_debug: debug
	@printf "$(bold)$(blue)running $(DEBUG_OUT) ...$(reset)\n"
	./$(DEBUG_OUT)

## CLEANING ##

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(RELEASE_OUT) $(DEBUG_OUT)

re: fclean all

.PHONY: all release debug run run_debug clean fclean re
