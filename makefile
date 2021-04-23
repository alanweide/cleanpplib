CXXFLAGS = -std=c++14
lib_objects = src/clean_nn/natural_number.o src/clean_nn/bounded_nn.o src/clean_nn/stack_nn.o src/clean_integer/integer_impl.o src/clean_integer/nn_integer.o src/clean_integer/vector_integer.o
includepath = -I include/cleanpp
testdir = cleanpp-gtest

all: libCleanpp

libCleanpp libcleanpp libCleanpp.a: $(lib_objects)
	@echo "Building $@..." 
	ar rv libCleanpp.a $^
	@echo "Done."

libCleanpp.exe: %.o libCleanpp
	$(CXX) -o $@ $^

$(lib_objects): %.o: %.cpp
	@echo "Making object file for $@..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(includepath)
# @echo "Done."

%.o: %.cpp libCleanpp
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $< -o $@ -L. -lCleanpp $(includepath)
	@echo "Done."

gtest:
	@echo "Testing..."
	cmake -S $(testdir) -B $(testdir)/build
	cmake --build $(testdir)/build
	cd $(testdir)/build && ctest
	@echo "Done."

clean:
	rm libCleanpp.a $(lib_objects) */**.o