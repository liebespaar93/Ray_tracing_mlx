# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 08:58:54 by kyoulee           #+#    #+#              #
#    Updated: 2023/01/12 13:36:03 by kyoulee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = ray_tracing

CC = cc -g
CXXFLAGS = $(NULL)
CFLAGS = -Wall -Werror -Wextra
DFLAGS = $(NULL)
IFLAGS =								\
	-I $(INCLUDE_DIR)
LDFLAGS =						\
	-L $(MINILIBX_DIR)
LDLIBS =											\
	-lmlx -lm -framework OpenGL -framework AppKit

## MODULES ##
MINILIBX = $(MINILIBX_DIR)/libmlx.a

#####***** DIR *****#####
ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
INCLUDE_DIR = $(ROOTDIR)/include
MINILIBX_DIR = $(ROOTDIR)/modules/minilibx_opengl

OBJ_DIR = $(ROOTDIR)/obj

SRC_01_APP_DIR = $(ROOTDIR)/src_01_app
SRC_TOOL_DIR = $(ROOTDIR)/src_tool


## MODULES ##
MINILIBX_DIR = $(ROOTDIR)/modules/minilibx_opengl

#####***** SRC *****#####
SRC_01_APP_SRC =	ft_app.c	\
					ft_image.c

SRC_01_APP_C = $(addprefix $(SRC_01_APP_DIR)/, $(SRC_01_APP_SRC))


SRC_TOOL_SRC =					\
				ft_bzero.c		\
				ft_error.c		\
				ft_memcpy.c		\
				ft_memset.c		\
				ft_strlen.c		\
				ft_zeromalloc.c

SRC_TOOL_C = $(addprefix $(SRC_TOOL_DIR)/, $(SRC_TOOL_SRC))


OBJS =	$(SRC_01_APP_C:$(SRC_01_APP_DIR)/%.c=$(OBJ_DIR)/%.o)	\
		$(SRC_TOOL_C:$(SRC_TOOL_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_CLEAN = $(OBJS)

#####***** working *****#####

all : $(TARGET)

$(OBJ_DIR) : 
	mkdir $@

$(TARGET) : $(OBJ_DIR) $(MINILIBX) $(OBJS) $(TARGET) 
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) main.c -o $(TARGET)
	@echo "$(FG_LMAGENTA)$(CC) $(FG_BLUE) $(CFLAGS)"
	@(for i in $(IFLAGS) $(LDFLAGS); do echo $$i; done)
	@echo "$(LDLIBS) $(FG_LCYAN)"
	@(for i in $(OBJS); do echo $$i; done)
	@echo "$(FG_BLUE)-o $(FG_LYELLOW)$(TARGET)$(NO_COLOR)"



$(OBJ_DIR)/%.o : $(SRC_01_APP_DIR)/%.c
	$(CC) $(CXXFLAGS) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_TOOL_DIR)/%.c
	$(CC) $(CXXFLAGS) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $< -o $@

## MODULES ##
$(MINILIBX):
	echo "$(FG_MAGENTA)module $(FG_LYELLOW)minilibx$(NO_COLOR) -> $(FG_LCYAN)$(MINILIBX)$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(MINILIBX_DIR)
	@echo "$(NO_COLOR)"



#####***** clean *****#####
clean : clean_minilibx
	rm -f $(OBJS_CLEAN)

fclean : OBJS_CLEAN+=$(TARGET)
fclean : clean

re : fclean all

.PHONY: all re  clean fclean clean_minilibx

## MODULES ##
clean_minilibx :
	@echo "clean $(FG_MAGENTA)module $(FG_LYELLOW)$(notdir $(MINILIBX))$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(MINILIBX_DIR) clean 
	@echo "$(NO_COLOR)"



#####***** COLOR *****#####
BG_RED     = \033[41m
BG_GREEN   = \033[42m
BG_YELLOW  = \033[43m
BG_BLUE    = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN    = \033[46m
BG_LGREY   = \033[47m
BG_DGREY   = \033[100m
BG_LRED    = \033[101m
BG_LGREEN  = \033[102m
BG_LYELLOW = \033[103m
BG_LBLUE   = \033[104m
BG_LMAGENTA= \033[105m
BG_LCYAN   = \033[106m
BG_WHITE   = \033[107m
BG_MAKE1   = \033[48;5;236m
BG_MAKE2   = \033[48;5;238m
BG_MAKE3   = \033[48;5;240m

FG_BLACK   = \033[30m
FG_RED     = \033[31m
FG_GREEN   = \033[32m
FG_YELLOW  = \033[33m
FG_BLUE    = \033[34m
FG_MAGENTA = \033[35m
FG_CYAN    = \033[36m
FG_LGREY   = \033[37m
FG_DGREY   = \033[90m
FG_LRED    = \033[91m
FG_LGREEN  = \033[92m
FG_LYELLOW = \033[93m
FG_LBLUE   = \033[94m
FG_LMAGENTA= \033[95m
FG_LCYAN   = \033[96m
FG_WHITE   = \033[97m
 
CL_BOLD   = \033[1m
CL_DIM    = \033[2m
CL_UDLINE = \033[4m
CL_BLINK  = \033[5m
CL_INVERT = \033[7m
CL_HIDDEN = \033[8m
 
NO_COLOR = \033[0m