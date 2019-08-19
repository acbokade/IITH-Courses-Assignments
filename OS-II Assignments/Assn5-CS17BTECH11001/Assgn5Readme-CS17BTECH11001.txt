1)  Input to the program is a file named "inp-params.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    Input parameters are - n: the number of philosopher threads, h: the number of times each philosopher 
    thread tries to enter the CS, μeat, μthink (delay values for CS and Remainder section that are 
    exponentially distributed with an average of μeat, μthink milli-seconds.)
    
    Example:
    10 10 1 2

2)  a) Compile the dining-philosopher's code by executing following command:
    g++ -std=c++11 -pthread dphil-CS17BTECH11001.cpp -o dphil

3)  a) Run the TAS executable by :
    ./dphil

4)  Logs of dining-philosopher's code are generated in file name "dphil-log.txt".

5)  Average time taken for a philosopher thread to gain entry to the Critical Section are printed in file 
   	named and Worst-case time taken by the philosopher threads to enter the CS is printed in file named 
    "Time.txt".

6)  Graph is plotted for following values :-
    Count of each philosopher thread kept Constant at value 10
    μeat = 1
    μthink = 2
    Number of philosopher threads are varied from 1 to 20 in increments of 5.
    
    Graph plotted for following values :-
    n = 1
	Average waiting time for philosopher threads is 0.216000 milliseconds
	Worst-case time taken by the philosopher threads to enter the CS is 0.093000 milliseconds

	n = 5
	Average waiting time for philosopher threads is 13.091200 milliseconds
	Worst-case time taken by the philosopher threads to enter the CS is 6.626000 milliseconds

	n = 10
	Average waiting time for philosopher threads is 11.38800 milliseconds
	Worst-case time taken by the philosopher threads to enter the CS is 7.618000 milliseconds

	n = 15
	Average waiting time for philosopher threads is 13.147933 milliseconds
	Worst-case time taken by the philosopher threads to enter the CS is 8.921000 milliseconds

	n = 20
	Average waiting time for philosopher threads is 13.487700 milliseconds
	Worst-case time taken by the philosopher threads to enter the CS is 11.524000 milliseconds