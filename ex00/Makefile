# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 15:19:54 by okrahl            #+#    #+#              #
#    Updated: 2024/12/09 15:26:01 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = incl

# Target
TARGET = convert

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $^

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean objects
clean:
	rm -rf $(OBJ_DIR)

# Clean objects and executable
fclean: clean
	rm -f $(TARGET)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
