CME
1)  Input to the program is a file named "inp-params.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    Input parameters are - n: the number of threads, k: the number of times each  
    thread tries to enter the CS, S (number of sections), lambda1, lambda2 (delay values for CS and Remainder section that are 
    exponentially distributed with an average of lambda1, lambda2 milli-seconds.)
    
    Example:
    20 20 5 5 20

2)  a) Compile the CME code by executing following command:
    g++ -std=c++11 -pthread cme-CS17BTECH11001.cpp -o cme

3)  a) Run the CME executable by :
    ./cme

4)  Logs of CME code are generated in file name "Log.txt".

5)  Average time taken for a thread to enter the CS is printed in file named 
    "times.txt".

SME
1)  Input to the program is a file named "inp-params1.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    Input parameters are - n: the number of threads, k: the number of times each  
    thread tries to enter the CS,lambda1, lambda2 (delay values for CS and Remainder section that are 
    exponentially distributed with an average of lambda1, lambda2 milli-seconds.)
    
    Example:
    20 20 5 20

2)  a) Compile the CME code by executing following command:
    g++ -std=c++11 -pthread sme-CS17BTECH11001.cpp -o sme

3)  a) Run the CME executable by :
    ./sme

4)  Logs of CME code are generated in file name "Log1.txt".

5)  Average time taken for a thread to enter the CS is printed in file named 
    "times1.txt".