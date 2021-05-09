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
# WARNING: Doesn't work.
libCleanpp.so: $(lib_objects)
	$(CXX) $(CXXFLAGS) -shared -o libCleanpp.so $^

# @Will: does this work in Windows?
libCleanpp.exe: $(lib_objects) libCleanpp.a
	$(CXX) -o $@ $^

$(lib_objects): %.o: %.cpp $(includepath)/clean_base.hpp $(wildcard $(includepath)/**/*.hpp)
	@echo "Making object file for $@..."
# @ls $(includepath)/**/*.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(includepath)
	@echo "Done."

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
test gtest: $(testdir)/build
	@echo "Running tests..."
	@cd $(testdir)/build && ctest
	@echo "Done."

build-test: $(testdir)/build

$(testdir)/build: libCleanpp.a
	@cmake -S $(testdir) -B $(testdir)/build
	@cmake --build $(testdir)/build

# ----------------
# Cleaning targets
# ----------------
.PHONY: clean clean-lib clean-obj clean-test
clean: clean-lib clean-obj clean-test
	@echo "Done."

clean-lib:
	@echo "Cleaning library..."
	@-rm -f libCleanpp.a $(lib_objects)

clean-obj:
	@echo "Cleaning miscellaneous object files..."
	@-rm -f */**.o
	
clean-test:
	@echo "Cleaning $(testdir) build files..."
	@-rm -rf $(testdir)/build
