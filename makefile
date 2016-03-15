$(NAME) : $(NAME).cpp
	g++ -o $(NAME) $(NAME).cpp
	./$(NAME)
run: 
	./$(NAME)