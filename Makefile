NAME_NM = 			ft_nm
NAME_OTOOL = 		ft_otool

SRC_DIR_NM =		./src/nm
SRC_DIR_OTOOL =	 	./src/otool

OBJ_DIR_NM = 		./obj_nm
OBJ_DIR_OTOOL =		./obj_otool

SRC_NM = 			arch_32.c \
					arch_64.c \
					arch_fat.c \
					arch_lib.c \
					display.c \
					ft_nm.c \
					sort.c \
					utils.c

SRC_OTOOL = 		arch_32.c \
					arch_64.c \
					arch_fat.c \
					arch_lib.c \
					display.c \
					ft_otool.c \
					sort.c \
					utils.c

OBJ_NM = 			$(addprefix $(OBJ_DIR_NM)/,$(SRC_NM:.c=.o))
OBJ_OTOOL = 		$(addprefix $(OBJ_DIR_OTOOL)/,$(SRC_OTOOL:.c=.o))

SRC_PATH_NM = 		$(addprefix $(SRC_DIR_NM)/, $(SRC_NM))
SRC_PATH_OTOOL =	$(addprefix $(SRC_DIR_OTOOL)/, $(SRC_OTOOL))

CC = 		gcc

FLAGS = 	-Wall -Werror -Wextra

HEADERS = 	-I./include

I_LIBFT = 	-I libft/INCLUDES/

LIBFT = 	$(I_LIBFT) -Llibft -lft

all: $(NAME_NM) $(NAME_OTOOL)

nm: $(NAME_NM)

otool: $(NAME_OTOOL)

$(NAME_NM): $(OBJ_NM)
	@make -C libft
	@$(CC) $(FLAGS) -o $@ $(OBJ_NM) $(HEADERS) $(LIBFT)
	@echo "\033[1;34mNm\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(NAME_OTOOL): $(OBJ_OTOOL)
	@make -C libft
	@$(CC) $(FLAGS) -o $@ $(OBJ_OTOOL) $(HEADERS) $(LIBFT)
	@echo "\033[1;34mOtool\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJ_DIR_NM)/%.o: $(SRC_DIR_NM)/%.c
	@mkdir $(OBJ_DIR_NM) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

$(OBJ_DIR_OTOOL)/%.o: $(SRC_DIR_OTOOL)/%.c
	@mkdir $(OBJ_DIR_OTOOL) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

clean:
	@rm -rf $(OBJ_NM) $(OBJ_OTOOL) $(NAME_NM) $(NAME_OTOOL)
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@make fclean -C libft
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@rm -rf $(OBJ_DIR_NM) $(OBJ_DIR_OTOOL)

re: fclean all

norme:
	@echo "\033[1;34mNm_otool\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
	@norminette $(SRC_PATH_NM) $(SRC_PATH_OTOOL)

.PHONY: re fclean clean all norme res
