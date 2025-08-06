NAME		=	libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
AR			=	ar rcs
MAKEFLAGS	+=	--no-print-directory

# OS Libft
UNAME_S		=	$(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	OS_DIR	=	./mac
else
	OS_DIR	=	./linux
endif

######################### Directories #########################
SRCS_DIR	=	./srcs
CTYPE_DIR	=	$(SRCS_DIR)/ctype
FREE_DIR	=	$(SRCS_DIR)/free
GNL_DIR		=	$(SRCS_DIR)/get_next_line
LIST_DIR	=	$(SRCS_DIR)/list
MATH_DIR	=	$(SRCS_DIR)/math
MEM_DIR		=	$(SRCS_DIR)/memory
STDIO_DIR	=	$(SRCS_DIR)/stdio
STDLIB_DIR	=	$(SRCS_DIR)/stdlib
STRING_DIR	=	$(SRCS_DIR)/string

# OS Libft
OS_SRCS_DIR	=	$(OS_DIR)/srcs
PRINTF_DIR	=	$(OS_SRCS_DIR)/ft_printf




######################### Sources #########################
PRINTF_SRCS	=	$(PRINTF_DIR)/ft_dprintf.c \
				$(PRINTF_DIR)/ft_fputc.c \
				$(PRINTF_DIR)/ft_fputi.c \
				$(PRINTF_DIR)/ft_fputp.c \
				$(PRINTF_DIR)/ft_fputs.c \
				$(PRINTF_DIR)/ft_fputu.c \
				$(PRINTF_DIR)/ft_fputx.c \
				$(PRINTF_DIR)/ft_printf.c \
				$(PRINTF_DIR)/ft_uitoa_base.c \
				$(PRINTF_DIR)/ft_ulltoa_base.c \
				$(PRINTF_DIR)/ft_vdprintf.c \
				$(PRINTF_DIR)/ft_vprintf.c

OS_SRCS		=	$(PRINTF_SRCS)

### Common
CTYPE_SRCS	=	$(CTYPE_DIR)/ft_isalnum.c \
				$(CTYPE_DIR)/ft_isalpha.c \
				$(CTYPE_DIR)/ft_isascii.c \
				$(CTYPE_DIR)/ft_isdigit.c \
				$(CTYPE_DIR)/ft_ishexdigit.c \
				$(CTYPE_DIR)/ft_isprint.c \
				$(CTYPE_DIR)/ft_isspace.c \
				$(CTYPE_DIR)/ft_tolower.c \
				$(CTYPE_DIR)/ft_toupper.c
FREE_SRCS	=	$(FREE_DIR)/ft_free_array2.c \
				$(FREE_DIR)/ft_free_array3.c
GNL_SRCS	=	$(GNL_DIR)/get_next_line.c
LIST_SRCS	=	$(LIST_DIR)/ft_lstadd_back.c \
				$(LIST_DIR)/ft_lstadd_front.c \
				$(LIST_DIR)/ft_lstclear.c \
				$(LIST_DIR)/ft_lstdelone.c \
				$(LIST_DIR)/ft_lstiter.c \
				$(LIST_DIR)/ft_lstlast.c \
				$(LIST_DIR)/ft_lstmap.c \
				$(LIST_DIR)/ft_lstnew.c \
				$(LIST_DIR)/ft_lstsize.c
MATH_SRCS	=	$(MATH_DIR)/ft_abs.c \
				$(MATH_DIR)/ft_max.c \
				$(MATH_DIR)/ft_min.c
MEM_SRCS	=	$(MEM_DIR)/ft_bzero.c \
				$(MEM_DIR)/ft_memchr.c \
				$(MEM_DIR)/ft_memcmp.c \
				$(MEM_DIR)/ft_memcpy.c \
				$(MEM_DIR)/ft_memmove.c \
				$(MEM_DIR)/ft_memset.c
STDIO_SRCS	=	$(STDIO_DIR)/ft_fopen.c \
				$(STDIO_DIR)/ft_isize.c \
				$(STDIO_DIR)/ft_putchar_fd.c \
				$(STDIO_DIR)/ft_putendl_fd.c \
				$(STDIO_DIR)/ft_putnbr_fd.c \
				$(STDIO_DIR)/ft_putstr_fd.c \
				$(STDIO_DIR)/ft_uisize.c
STDLIB_SRCS	=	$(STDLIB_DIR)/ft_atoi.c \
				$(STDLIB_DIR)/ft_atol.c \
				$(STDLIB_DIR)/ft_calloc.c \
				$(STDLIB_DIR)/ft_hextoi.c \
				$(STDLIB_DIR)/ft_itoa.c \
				$(STDLIB_DIR)/ft_mkstemp.c \
				$(STDLIB_DIR)/ft_mktemp.c \
				$(STDLIB_DIR)/ft_random.c \
				$(STDLIB_DIR)/ft_strtol.c \
				$(STDLIB_DIR)/ft_swap.c
STRING_SRCS	=	$(STRING_DIR)/ft_split.c \
				$(STRING_DIR)/ft_strchr.c \
				$(STRING_DIR)/ft_strcmp.c \
				$(STRING_DIR)/ft_strdup.c \
				$(STRING_DIR)/ft_striteri.c \
				$(STRING_DIR)/ft_strjoin.c \
				$(STRING_DIR)/ft_strlcat.c \
				$(STRING_DIR)/ft_strlcpy.c \
				$(STRING_DIR)/ft_strlen.c \
				$(STRING_DIR)/ft_strmapi.c \
				$(STRING_DIR)/ft_strncmp.c \
				$(STRING_DIR)/ft_strndup.c \
				$(STRING_DIR)/ft_strnstr.c \
				$(STRING_DIR)/ft_strrchr.c \
				$(STRING_DIR)/ft_strtrim.c \
				$(STRING_DIR)/ft_substr.c

SRCS		=	$(OS_SRCS) $(CTYPE_SRCS) $(FREE_SRCS) $(GNL_SRCS) $(LIST_SRCS) $(MATH_SRCS) $(MEM_SRCS) \
				$(STDIO_SRCS) $(STDLIB_SRCS) $(STRING_SRCS)



######################### Objects #########################
OBJS_DIR	=	./objs

# Convert both SRCS_DIR and OS_DIR paths to OBJS_DIR
OBJS		=	$(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(filter $(SRCS_DIR)/%.c,$(SRCS))) \
				$(patsubst $(OS_DIR)/%.c,$(OBJS_DIR)/%.o,$(filter $(OS_DIR)/%.c,$(SRCS)))



######################### Includes #########################
INCLUDES	=	-I ./includes -I $(OS_DIR)/includes



######################### UI/UX #########################
RESET		=	\033[0m
BOLD		=	\033[1m
LIGHT_BLUE	=	\033[94m
YELLOW		=	\033[93m

### Progress Bar
TOTAL_FILES	:=	$(words $(OBJS))
CURRENT_FILE :=	0

define progress
	@$(eval COMPILED=$(shell echo $$(expr $(COMPILED) + 1)))
	@CURRENT_PERCENT=$$(expr $(COMPILED) \* 100 / $(TOTAL_FILES)); \
	printf "\r\033[K$(YELLOW)[%3d%%] Compiling: $<$(RESET)\r" $$CURRENT_PERCENT
endef



######################### Targets #########################
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[K$(BOLD)$(LIGHT_BLUE)$(NAME) created successfully!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(progress)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(OS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(progress)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning objects...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning Complete!$(RESET)"

fclean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_DIR) $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME) Complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re