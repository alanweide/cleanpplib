objects = bounded_nn.o clean_integer.o natural_number.o nn_integer.o stack_nn.o vector_integer.o
headerfiles = -I ../include/cleanpp -I ../include/cleanpp/clean_integer -I ../include/cleanpp/clean_list -I ../include/cleanpp/clean_nn -I ../include/cleanpp/clean_queue -I ../include/cleanpp/clean_stack -I ../include/cleanpp/flexible_integer -I ../include/cleanpp/flexible_list -I ../include/cleanpp/flexible_nn -I ../include/cleanpp/flexible_queue -I ../include/cleanpp/flexible_stack -I ../include/cleanpp/template_integer -I ../include/cleanpp/template_list -I ../include/cleanpp/template_nn -I ../include/cleanpp/template_queue -I ../include/cleanpp/template_stack 
version = -std=c++14
program = selection_sort5


$(program).exe: $(program).o libCleanpp.a
	g++ -o $@ $^

libCleanpp.a: $(objects)
	ar rv libCleanpp.a $^

$(program).o: $(program).cpp 
	g++ $(version) -c $< -o $@ -I ../include/cleanpp/flexible_nn -I ../include/cleanpp/template_nn -I ../include/cleanpp/flexible_stack -I ../include/cleanpp/template_stack -I ../include/cleanpp -I ../include/cleanpp/template_integer -I ../include/cleanpp/flexible_integer -I ../include/cleanpp/nn_integer -I ../include/cleanpp/bounded_nn -I ../include/cleanpp/vector_integer -I ../include/cleanpp/template_queue -I ../include/cleanpp/flexible_queue -I ../include/cleanpp/clean_queue -I ../include/cleanpp/clean_stack -I ../include/cleanpp/template_list -I ../include/cleanpp/flexible_list -I ../include/cleanpp/clean_list -I ../include/cleanpp/clean_integer -I ../include/cleanpp/clean_nn

bounded_nn.o: ../src/clean_nn/bounded_nn.cpp 
	g++ $(version) -c $< -o ../cleanpp-main/$@ $(headerfiles)

clean_integer.o: ../src/clean_integer/clean_integer.cpp
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
	
