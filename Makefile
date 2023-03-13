##
## EPITECH PROJECT, 2022
## shell
## File description:
## Makefile
##

SRC				:=	src/main.c \
                    src/prompt.c \
                    src/env/parse.c \
                    src/env/update.c \
                    src/command/parse.c \
                    src/command/resolver.c \
                    src/command/execute.c \
                    src/builtin/exec.c \
                    src/builtin/env.c \
                    src/builtin/cd.c \
                    src/builtin/exit.c \
                    src/util/mem.c \
                    src/util/string.c \
                    src/util/string_parse.c \
                    src/util/string_split.c \
                    src/util/path.c \
                    src/util/error.c \

RELEASE_OUT		:= 	mysh
DEBUG_OUT		:= 	mysh_debug

BUILD_DIR		:=  build
RELEASE_DIR 	:= 	build/release
DEBUG_DIR		:= 	build/debug

CC				:=	gcc
CFLAGS			+=	-I./include/ -MMD -MP
LDFLAGS			:=

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o))
RELEASE_FLAGS	:=	-O1

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o))
SANITIZERS		:=	-fsanitize=address -fsanitize=undefined
DEBUG_FLAGS		:=	-Og -g3 -Wall -Wextra -Wpedantic -Wshadow
DEBUG_FLAGS     +=	$(if $(NO_SANITIZE),, $(SANITIZERS))

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
	@printf "$(grey)sanitizers:$(reset)$(underline)$(grey)"
	@printf "$(if $(NO_SANITIZE),disabled,enabled)$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(DEBUG_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): $(RELEASE_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): $(DEBUG_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

## OBJECTS ##

$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(grey)compiling %-50s$(reset)" $<
	@$(CC) -o $@ -c $< $(CFLAGS)
	@printf "$(green)done$(reset)\n"

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(grey)compiling %-50s$(reset)" $<
	@$(CC) -o $@ -c $< $(CFLAGS)
	@printf "$(green)done$(reset)\n"

## RUN ##

run: release
	@printf "$(blue)running $(RELEASE_OUT)$(reset)\n"
	@./$(RELEASE_OUT)

run_debug: debug
	@printf "$(blue)running $(DEBUG_OUT)$(reset)\n"
	@./$(DEBUG_OUT)

## CLEANING ##

clean:
	@printf "$(blue)cleaning build$(reset)\n"
	@$(RM) -r $(BUILD_DIR)

fclean: clean
	@printf "$(blue)cleaning binaries$(reset)\n"
	@$(RM) $(RELEASE_OUT) $(DEBUG_OUT)

re: fclean all

## HELP ##

help:
	@printf "$(bold)$(green)TARGETS$(reset)\n"

	@printf "make $(bold)release$(reset)\toptimize for performance "
	@printf "\t\t$(grey)output: $(underline)$(RELEASE_OUT)$(reset)\n"
	@printf "make $(bold)debug$(reset)\tdebug infos and sanitizers enabled "
	@printf "\t$(grey)output: $(underline)$(DEBUG_OUT)$(reset)\n"

	@printf "\n$(bold)$(green)VARIABLES$(reset)\n"
	@printf "$(bold)CFLAGS$(reset)\t\tadditional compiler flags\n"
	@printf "$(bold)NO_SANITIZE$(reset)\tdisable sanitizers\n"

.PHONY: all release debug run run_debug clean fclean re help
