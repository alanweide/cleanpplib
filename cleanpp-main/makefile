objects = bounded_nn.o integer_impl.o natural_number.o nn_integer.o stack_nn.o vector_integer.o
headerfiles = -I ../include/cleanpp -I ../include/cleanpp/clean_integer -I ../include/cleanpp/clean_list -I ../include/cleanpp/clean_nn -I ../include/cleanpp/clean_queue -I ../include/cleanpp/clean_stack -I ../include/cleanpp/integer_impls -I ../include/cleanpp/list_impls -I ../include/cleanpp/natural_number_impls -I ../include/cleanpp/queue_impls -I ../include/cleanpp/stack_impls -I ../include/cleanpp/clean_set -I ../include/cleanpp/set_impls
version = -std=c++14
program = clean_map


$(program).exe: $(program).o libCleanpp.a
	g++ -o $@ $^

libCleanpp.a: $(objects)
	ar rv libCleanpp.a $^

$(program).o: $(program).cpp 
	g++ $(version) -c $< -o $@ $(headerfiles)

bounded_nn.o: ../src/clean_nn/bounded_nn.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

integer_impl.o: ../src/clean_integer/integer_impl.cpp
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

natural_number.o: ../src/clean_nn/natural_number.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

nn_integer.o: ../src/clean_integer/nn_integer.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

stack_nn.o: ../src/clean_nn/stack_nn.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

vector_integer.o: ../src/clean_integer/vector_integer.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)


clean: 
	rm *.o