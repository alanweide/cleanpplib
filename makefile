SHELL = bash
CXXFLAGS = -std=c++14
lib_objects = src/clean_nn/natural_number.o src/clean_nn/bounded_nn.o src/clean_nn/stack_nn.o src/clean_integer/integer_impl.o src/clean_integer/nn_integer.o src/clean_integer/vector_integer.o
includepath = include/cleanpp
testdir = cleanpp-gtest

all: libCleanpp

libCleanpp libcleanpp libCleanpp.a: $(lib_objects)
	@echo "Building $@..." 
	ar rv libCleanpp.a $^
	@echo "Done."

libCleanpp.exe: $(lib_objects) libCleanpp
	$(CXX) -o $@ $^

$(lib_objects): %.o: %.cpp $(includepath)/clean_base.hpp $(wildcard $(includepath)/**/*.hpp)
	@echo "Making object file for $@..."
	@ls $(includepath)/**/*.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(includepath)

%.o: %.cpp libCleanpp
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $< -o $@ -L. -lCleanpp -I $(includepath)
	@echo "Done."

test gtest: libCleanpp $(wildcard $(includepath)/**/*.hpp)
	@echo "Testing..."
	cmake -S $(testdir) -B $(testdir)/build
	cmake --build $(testdir)/build
	cd $(testdir)/build && ctest
	@echo "Done."

clean:
	rm libCleanpp.a $(lib_objects) */**.o
	rm -rf $(testdir)/build