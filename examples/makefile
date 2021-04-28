objects = bounded_nn.o integer_impl.o natural_number.o nn_integer.o stack_nn.o vector_integer.o
headerfiles = -I ../include/cleanpp -I ../include/cleanpp/clean_integer -I ../include/cleanpp/clean_list -I ../include/cleanpp/clean_nn -I ../include/cleanpp/clean_queue -I ../include/cleanpp/clean_stack -I ../include/cleanpp/integer_impls -I ../include/cleanpp/list_impls -I ../include/cleanpp/natural_number_impls -I ../include/cleanpp/queue_impls -I ../include/cleanpp/stack_impls -I ../include/cleanpp/clean_set -I ../include/cleanpp/set_impls -I ../include/cleanpp/clean_map -I ../include/cleanpp/map_impls
headerfiles_prereq = ../include/cleanpp/clean_base.hpp ../include/cleanpp/clean_integer/integer.hpp ../include/cleanpp/clean_list/list.hpp ../include/cleanpp/clean_map/map.hpp ../include/cleanpp/clean_nn/natural_number.hpp ../include/cleanpp/clean_queue/queue.hpp ../include/cleanpp/clean_set/set.hpp ../include/cleanpp/clean_stack/stack.hpp ../include/cleanpp/integer_impls/integer_impl.hpp ../include/cleanpp/integer_impls/nn_integer.hpp ../include/cleanpp/integer_impls/vector_integer.hpp ../include/cleanpp/list_impls/list_impl.hpp ../include/cleanpp/list_impls/stack_based_list.hpp ../include/cleanpp/map_impls/map_impl.hpp ../include/cleanpp/map_impls/map_on_set.hpp ../include/cleanpp/natural_number_impls/bounded_nn.hpp ../include/cleanpp/natural_number_impls/natural_number_impl.hpp ../include/cleanpp/natural_number_impls/stack_nn.hpp ../include/cleanpp/set_impls/set_impl.hpp ../include/cleanpp/set_impls/set_on_queue.hpp ../include/cleanpp/stack_impls/array_stack.hpp ../include/cleanpp/stack_impls/linked_stack.hpp ../include/cleanpp/stack_impls/stack_impl.hpp ../include/cleanpp/clean_base.hpp
version = -std=c++14
program = quicksort_clean


$(program).exe: $(program).o libCleanpp.a 
	g++ -o $@ $^

libCleanpp.a: $(objects)
	echo "building libCleanpp.a" 
	@ar rv libCleanpp.a $^ 

$(program).o: $(program).cpp
	echo "building $@"
	@g++ $(version) -c $< -o $@ $(headerfiles)

bounded_nn.o: ../src/clean_nn/bounded_nn.cpp 
	@g++ $(version) -c $< -o $@ $(headerfiles)

integer_impl.o: ../src/clean_integer/integer_impl.cpp
	@g++ $(version) -c $< -o $@ $(headerfiles)

natural_number.o: ../src/clean_nn/natural_number.cpp 
	@g++ $(version) -c $< -o $@ $(headerfiles)

nn_integer.o: ../src/clean_integer/nn_integer.cpp 
	@g++ $(version) -c $< -o $@ $(headerfiles)

stack_nn.o: ../src/clean_nn/stack_nn.cpp 
	@g++ $(version) -c $< -o $@ $(headerfiles)

vector_integer.o: ../src/clean_integer/vector_integer.cpp 
	@g++ $(version) -c $< -o $@ $(headerfiles)

clean: 
	rm *.o *.exe