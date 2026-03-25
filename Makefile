CC     = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

BLUE   = \033[34m
GREEN  = \033[32m
CYAN   = \033[36m
YELLOW = \033[33m
RESET  = \033[0m

NAME = libftprintf.a

SRC = ft_printf.c       \
	  ft_itoa.c         \
	  parser.c          \
	  utils.c           \
	  process_percent.c \
	  process_char.c    \
	  process_string.c  \
	  process_pointer.c \
	  process_int.c     \
	  process_uint.c    \
	  process_hex.c

OBJ_DIR = obj

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

OBJ_BONUS = $(SRC_BONUS:%.c=${OBJ_DIR}/%.o)
DEP_BONUS = $(OBJ_BONUS:.o=.d)

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@echo "Creating library $(BLUE)$@$(RESET)"
	@ar rcs $@ $^

${OBJ_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $(CYAN)$<$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "$(YELLOW)Cleaning $(NAME) object files$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing the $(NAME) library$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
