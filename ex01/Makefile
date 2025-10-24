NAME = RPN

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

BUILD_DIR = build

SRCS = main.cpp \
	RPN.cpp

OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "🧹 Suppression des fichiers objets et dépendances terminée."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ Suppression de $(NAME) terminée."

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re