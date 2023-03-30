##
## EPITECH PROJECT, 2022
## shell
## File description:
## Makefile
##

SRC				:=	src/builtin/cd.c \
					src/builtin/env.c \
					src/builtin/exec.c \
					src/builtin/exit.c \
					src/command_new/data.c \
					src/command_new/free.c \
					src/command_new/parse.c \
					src/command/execute.c \
					src/command/parse.c \
					src/command/resolver.c \
					src/env/parse.c \
					src/env/update.c \
					src/prompt.c \
					src/string/string_parse.c \
					src/string/string_split.c \
					src/string/string.c \
					src/tokenizer/token_syntax.c \
					src/tokenizer/token.c \
					src/tokenizer/tokenizer.c \
					src/util/error.c \
					src/util/mem.c \
					src/util/path.c \

MAIN_SRC		:=	src/main.c

TEST_SRC 		:= 	tests/tokenizer.c

RELEASE_OUT		:= 	mysh
DEBUG_OUT		:= 	mysh_debug
TEST_OUT		:= 	unit_tests

BUILD_DIR		:=  build
RELEASE_DIR 	:= 	build/release
DEBUG_DIR		:= 	build/debug
TEST_DIR		:= 	build/test

CC				:=	gcc
CFLAGS			+=	-I./include/ -MMD -MP
LDFLAGS			:=

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o) $(MAIN_SRC:.c=.o))
RELEASE_FLAGS	:=	-O2 -fno-optimize-strlen

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o) $(MAIN_SRC:.c=.o))
SANITIZERS		:=	-fsanitize=address -fsanitize=undefined
DEBUG_FLAGS		:=	-g3 -Wall -Wextra -Wpedantic -Wshadow
DEBUG_FLAGS     +=	$(if $(NO_SANITIZE),, $(SANITIZERS))

TEST_OBJ		:= 	$(addprefix $(TEST_DIR)/,$(SRC:.c=.o) $(TEST_SRC:.c=.o))
TEST_FLAGS		:=	--coverage
TEST_LIBS		:=	-lcriterion

reset			:=  \033[0m
bold			:= 	\033[1m
underline		:= 	\033[4m
green			:=  \033[32m
blue			:= 	\033[34m
grey 			:= 	\033[90m

all: release

-include $(RELEASE_OBJ:.o=.d)
-include $(DEBUG_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)

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

test: $(TEST_OUT)
	@printf "$(bold)$(green)$(TEST_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)test$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(TEST_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): $(RELEASE_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): $(DEBUG_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(TEST_OUT): CFLAGS += $(TEST_FLAGS)
$(TEST_OUT): LDLIBS += $(TEST_LIBS)
$(TEST_OUT): $(TEST_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

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

$(TEST_DIR)/%.o: %.c
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

tests_run: test
	@printf "$(blue)running $(TEST_OUT)$(reset)\n"
	./$(TEST_OUT)
	gcovr --exclude tests/ --exclude src/main.c
	gcovr --branches --exclude tests/ --exclude src/main.c

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
	@printf "make $(bold)test$(reset)\tcompile tests "
	@printf "\t\t\t\t$(grey)output: $(underline)$(TEST_OUT)$(reset)\n"

	@printf "\n$(bold)$(green)VARIABLES$(reset)\n"
	@printf "$(bold)CFLAGS$(reset)\t\tadditional compiler flags\n"
	@printf "$(bold)NO_SANITIZE$(reset)\tdisable sanitizers\n"

.PHONY: all release debug run run_debug clean fclean re help
