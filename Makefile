MAKEFLAGS += --no-print-directory

CC     = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

BLUE   = \033[34m
GREEN  = \033[32m
CYAN   = \033[36m
YELLOW = \033[33m
RESET  = \033[0m

NAME = libftprintf.a

SRC = ft_printf.c       \
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

ifneq ($(wildcard ../42_libft/libft.a),)
	LIBFT_DIR = ../42_libft
	LIBFT     = $(LIBFT_DIR)/libft.a
	USE_LOCAL_LIBFT = 1
else
	LIBFT_DIR = ./libft
	LIBFT     = libft.a
	USE_LOCAL_LIBFT = 0
endif

all: $(NAME)

ifeq ($(USE_LOCAL_LIBFT),0)
$(LIBFT):
	@echo "Cloning libft..."
	git clone https://github.com/mike-k-git/42_libft $(LIBFT_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/$(LIBFT) .
	@mv $(LIBFT_DIR)/libft.h .
	@rm -rf $(LIBFT_DIR)
endif

bonus: all

$(NAME): $(LIBFT) $(OBJ)
	@echo "Creating library $(BLUE)$@$(RESET)"
	@ar rcs $@ $(OBJ)

${OBJ_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $(CYAN)$<$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(LIBFT_DIR) $< -o $@

clean:
	@echo "$(YELLOW)Cleaning $(NAME) object files$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing the $(NAME) library$(RESET)"
	@rm -f $(NAME)
	@rm -f libft.a libft.h

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
