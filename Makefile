NAME = RTv1
N_LFT = libft.a
N_SDLARCH = SDL2-2.0.8.tar.gz

D_LFT = ./Libft/
D_SRC = ./src/
D_INC = ./includes/
D_LFTINC = $(D_LFT)
D_SDL = ./SDL2-2.0.8/
D_SDLINC = $(D_SDL)include
D_SDLLIB = $(D_SDL)lib
D_OBJ = ./obj/
D_OBJ_MATH = $(D_OBJ)math
D_OBJ_RENDER = $(D_OBJ)render_objects
D_OBJ_TOLIBFT = $(D_OBJ)to_libft

L_SDL = `$(D_SDL)sdl2-config --cflags --libs`

LFT = $(D_LFT)$(N_LFT)

HEADER_FILES = $(D_INC)rtv1.h $(D_INC)vector_math.h
LIBHEAD = $(D_LFTINC)libft.h

C_FILES =	main.c \
            math/math_constructors.c \
            math/math_vec3_opeartors.c \
            camera.c \
            ray.c \
            material_scatters.c \
            math/math_utils.c \
            render_objects/sphere.c to_libft/ft_lstadd_end.c
LIBFT_FILES = ft_memset.c \
              		ft_bzero.c \
              		ft_memcpy.c \
              		ft_memccpy.c \
              		ft_memmove.c \
              		ft_memchr.c \
              		ft_memcmp.c \
              		ft_strlen.c \
              		ft_strdup.c \
              		ft_strndup.c \
              		ft_strcpy.c ft_strncpy.c \
              		ft_strcat.c ft_strncat.c ft_strlcat.c \
              		ft_strchr.c ft_strrchr.c \
              		ft_strstr.c ft_strnstr.c \
              		ft_strcmp.c ft_strncmp.c \
              		ft_atoi.c \
              		ft_isalpha.c \
              		ft_isdigit.c \
              		ft_isalnum.c \
              		ft_isascii.c \
              		ft_isprint.c \
              		ft_toupper.c \
              		ft_tolower.c \
              		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
              		ft_lstmap.c \
              		ft_itoa.c \
              		ft_memalloc.c \
              		ft_memdel.c \
              		ft_putchar.c \
              		ft_putchar_fd.c \
              		ft_putendl.c \
              		ft_putendl_fd.c \
              		ft_putnbr.c \
              		ft_putnbr_fd.c \
              		ft_putstr.c \
              		ft_putstr_fd.c \
              		ft_strclr.c \
              		ft_strdel.c \
              		ft_strequ.c \
              		ft_strnequ.c \
              		ft_striter.c \
              		ft_striteri.c \
              		ft_strjoin.c \
              		ft_strmap.c \
              		ft_strmapi.c \
              		ft_strnew.c \
              		ft_strsplit.c \
              		ft_strsub.c \
              		ft_strtrim.c \
              		ft_manywords.c \
              		ft_isupper.c \
              		ft_islower.c \
              		get_next_line.c

SRC = $(addprefix $(D_SRC), $(C_FILES))
LFTSRC = $(addprefix $(D_LFT), $(LIBFT_FILES))
OBJ = $(addprefix $(D_OBJ), $(C_FILES:.c=.o))

CC = gcc
CFLAGS =
INC = -I $(D_INC) -I $(D_LFTINC) -I $(D_SDLINC)

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(D_SDL) $(D_SDLLIB) $(D_OBJ) $(OBJ) $(LFTSRC) $(LIBHEAD)
	@make -C $(D_LFT)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" "libft.a"
	@$(CC) $(OBJ) $(LFT) $(L_SDL) -lm -o $(NAME)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(N_LFT):
	@make -C $(D_LFT)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(D_SDL):
	@tar -xf $(N_SDLARCH)
	@printf "RTv1:  %-25s$(C_CYAN)[extracted]$(C_NONE)\n" $@

$(D_SDLLIB):
	@mkdir $(D_SDLLIB)
	@printf "\n$(C_CYAN)[configuring SDL]$(C_NONE)\n"
	@cd $(D_SDL); ./configure --prefix=`pwd`/lib
	@printf "$(C_CYAN)[compiling SDL]$(C_NONE)\n"
	@make -C $(D_SDL)
	@make -C $(D_SDL) install >/dev/null
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(D_OBJ):
	@mkdir $(D_OBJ)
	@mkdir $(D_OBJ_MATH)
	@mkdir $(D_OBJ_RENDER)
	@mkdir $(D_OBJ_TOLIBFT)
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(D_OBJ)%.o: $(D_SRC)%.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "RTv1:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(D_OBJ)
	@make -C $(D_LFT) clean
	@printf "RTv1:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(D_SDL)
	@make -C $(D_LFT) fclean
	@printf "RTv1:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm: clean
	@norminette $(D_SRC) $(D_INC)

allnorm: norm
	@norminette $(D_LFT)