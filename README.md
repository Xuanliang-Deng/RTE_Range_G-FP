# RTE_Range_G-FP
Instructions: how to run my code
May 31, 2021


GSYY:

Unit test: 
$ g++ -std=c++11 GSYY_unit_test.cpp GSYY.cpp -lgtest -lgtest_main -pthread -o GSYY_test
$ ./GSYY_test

For unit tests, the test cases are stored under the /tests folder.

Normal execution:
$ g++ -std=c++11 GSYY.cpp main.cpp -o GSYY
$ ./GSYY

Note that the number of processors m and data should be changed accordingly in the main.cpp(m and fileName)


Heuristics:

Unit test:
$ g++ -std=c++11 DkC.cpp DMPO.cpp DCMPO.cpp Testmain.cpp -lgtest -lgtest_main -pthread -o heuristic_tests 
$ ./heuristic_tests

For unit tests, the test cases are stored under the /UnitTests

Normal execution:
$ g++ -std=c++11 DkC.cpp DMPO.cpp DCMPO.cpp main.cpp -o update_task_set 
$ ./update_task_set

Note that data_U4_constant_DkC is corrupted. Need to regenerate if it is necessary in future


DA:

Unit test:
$ g++ -std=c++11 DA_LC_test.cpp DA_LC.cpp -lgtest -lgtest_main -pthread -o DA_LC_test
$ ./DA_LC_test

Normal execution:
$ g++ -std=c++11 DA_LC.cpp main.cpp -o DA_LC
$ ./DA_LC


OPA+DA:
Unit test:

Normal execution:


 


