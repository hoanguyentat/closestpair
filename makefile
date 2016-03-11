PROGRAM = ClosestPair
$(PROGRAM) : $(PROGRAM).cpp
	g++ -o $(PROGRAM) $(PROGRAM).cpp
	./$(PROGRAM)
run: 
	./$(PROGRAM)