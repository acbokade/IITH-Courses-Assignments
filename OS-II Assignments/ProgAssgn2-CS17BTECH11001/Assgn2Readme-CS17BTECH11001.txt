1)  Input to the program is a file named "inp-params.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    n (number of threads), k (number of times each thread enters critical section) , λ1 (lambda for exponential distribution of delay 		value t1) , λ2 (lambda for exponential distribution of delay value t2).
    
    Example:
    10 10 2 2

2)
    a) Compile the TAS file by executing following command:
    g++ -std=c++11 -pthread SrcAssgn2-tas-CS17BTECH11001.cpp -o tas

    b) Compile the CAS file by executing following commands:
    g++ -std=c++11 -pthread SrcAssgn2-cas-CS17BTECH11001.cpp -o cas
    
    c) Compile the Bounded_CAS file by executing following commands:
    g++ -std=c++11 -pthread SrcAssgn2-cas-bounded-CS17BTECH11001.cpp -o casw


3) 
    a) Run the TAS executable by :
    ./tas

    b) Run the CAS executable by :
    ./cas

	c) Run the Bounded_CAS executable by :
    ./casw

4) Logs of TAS are generated in file name "TAS.txt".
  	 Logs of CAS are generated in file name "CAS.txt".
 	 Logs of Bounded_CAS are generated in file name "Bounded_CAS.txt".

5) Average time taken to enter CS by each thread and Worst case time taken by a process to enter the CS are printed in file 
   	 named "performanceTAS.txt", "performanceCAS.txt", "performanceBounded_CAS.txt" for TAS, CAS and Bounded_CA 
	respectively.
