1)  Input to the program is a file named "inp-params.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    Input parameters are :capacity (size of buffer), np (number of producer threads), nc  (number of consumer threads),
    cntp (count of producer threads), cntc (count of consumer threads), μp (Average value for exponential distribution 
    of delay value t1 in producers), μc (Average value for exponential distribution of delay value t2 in consumers).
    
    Example:
    10 10 2 2

2)
    a) Compile the prod_cons-sems file by executing following command:
    g++ -std=c++11 -pthread prod_cons-sems-CS17BTECH11001.cpp -o sem

    b) Compile the prod_cons-locks file by executing following commands:
    g++ -std=c++11 -pthread prod_cons-locks-CS17BTECH11001.cpp -o mutex
    

3) 
    a) Run the prod_cons-sems executable by :
    ./sem

    b) Run the prod_cons-locks executable by :
    ./mutex

4)  Logs of prod_cons-sems are generated in file name "sems.txt".
  	Logs of prod_cons-locks are generated in file name "locks.txt".

5)  Average time taken by producer and consumer threads taken in prod_cons-sems and prod_cons-locks
    are printed in files named "avgtimes-sems.txt", "avgtimes-locks.txt" respectively.