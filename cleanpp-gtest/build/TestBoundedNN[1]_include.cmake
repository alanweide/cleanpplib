if(EXISTS "/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/TestBoundedNN[1]_tests.cmake")
  include("/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/TestBoundedNN[1]_tests.cmake")
else()
  add_test(TestBoundedNN_NOT_BUILT TestBoundedNN_NOT_BUILT)
endif()
