SHELL = bash
CXXFLAGS = -std=c++14

lib_objects = src/clean_nn/natural_number.o src/clean_nn/bounded_nn.o src/clean_nn/stack_nn.o src/clean_integer/integer_impl.o src/clean_integer/nn_integer.o src/clean_integer/vector_integer.o
includepath = include/cleanpp
testdir = cleanpp-gtest

# ---------------
# Library targets
# ---------------
# Static library
libCleanpp.a: $(lib_objects)
	@echo "Building $@..." 
	ar rv libCleanpp.a $^
	@echo "Done."

# Dynamic library
libCleanpp.so: $(lib_objects)
	$(CXX) $(CXXFLAGS) -shared -o libCleanpp.so $^

# @Will: does this work in Windows?
libCleanpp.exe: $(lib_objects) libCleanpp
	$(CXX) -o $@ $^

$(lib_objects): %.o: %.cpp $(includepath)/clean_base.hpp $(wildcard $(includepath)/**/*.hpp)
	@echo "Making object file for $@..."
# @ls $(includepath)/**/*.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(includepath)

# ------------------------------------------
# Build (simple) individual Clean++ programs
# ------------------------------------------
%.o: %.cpp libCleanpp.a
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $< -o $@ -L. -lCleanpp -I $(includepath)
	@echo "Done."

# ---------------
# Testing targets
# ---------------
test gtest: build-test
	@echo "Running tests..."
	@cd $(testdir)/build && ctest
	@echo "Done."

build-test:
	@echo "Building tests..."
	@cmake -S $(testdir) -B $(testdir)/build
	@cmake --build $(testdir)/build
	@echo "Done."

# ----------------
# Cleaning targets
# ----------------
clean: clean-lib clean-obj clean-test
	@echo "Done."

clean-lib:
	-rm libCleanpp.a $(lib_objects)

clean-obj:
	-rm */**.o
	
clean-test:
	-rm -r $(testdir)/build