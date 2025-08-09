# CMake generated Testfile for 
# Source directory: /home/christian/local/repos/Animated-3D-Fractals
# Build directory: /home/christian/local/repos/Animated-3D-Fractals/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "/home/christian/local/repos/Animated-3D-Fractals/build/unit_tests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/christian/local/repos/Animated-3D-Fractals/CMakeLists.txt;152;add_test;/home/christian/local/repos/Animated-3D-Fractals/CMakeLists.txt;0;")
subdirs("External/googletest")
