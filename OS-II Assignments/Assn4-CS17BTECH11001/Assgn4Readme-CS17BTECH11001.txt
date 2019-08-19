1)  Input to the program is a file named "inp-params.txt,".
    The processes details in the file named inp-params.txt should be given in the format as follows:

    Input parameters are - nw: the number of writer threads, nr: the number of reader
    threads, kw: the number of times each writer thread tries to enter the CS, kr: the number of
    times each reader thread tries enter the CS, μCS, μRem (delay values that are exponentially distributed
    with an average of μCS, μRem milli-seconds.)
    
    Example:
    10 10 10 10 2 2

2)
    a) Compile the reader writer file by executing following command:
    g++ -std=c++11 -pthread rw-CS17BTECH11001.cpp -o rw

    b) Compile the fair reader writer file by executing following commands:
    g++ -std=c++11 -pthread frw-CS17BTECH11001.cpp -o frw

3) 
    a) Run the TAS executable by :
    ./rw

    b) Run the CAS executable by :
    ./frw

4)  Logs of RW are generated in file name "RW-log.txt".
  	Logs of Fair RW are generated in file name "FairRW-log.txt".

5)  Average time taken for a thread to gain entry to the Critical Section are printed in file 
   	named "RW.txt", "Fair-RW.txt" for RW and Fair RW respectively.

6)  Graph is plotted for following values :-
    Writers kept Constant at value 10
    Average waiting times
    #Writers in non fair
    x1 = [1,5,10,15,20] 
    y1 = [88.546,113.6392,62.146,20.3593,32.062]

    #Readers in fair
    x2 = [1,5,10,15,20] 
    y2 = [94.274800,458.241400,888.912000,1518.556000,2120.567500]

    #Writers in non fair 
    x3 = [1,5,10,15,20] 
    y3 = [807.144,936.457,905.317,821.671,778.2445]

    #Writers in fair 
    x4 = [1,5,10,15,20] 
    y4 = [837.331900,859.904200,827.734000,932.287000,971.582600] 



    Readers kept constant at value 10
    Average waiting times
    #Readers in non fair
    x1 = [1,5,10,15,20] 
    y1 = [10.209,24.5505,79.611,34.9797,10.209000] 

    #Readers in fair
    x2 = [1,5,10,15,20] 
    y2 = [94.518300,471.303700,937.651900,1369.996600,1921.184300 ] 

    #Writers in non fair 
    x3 = [1,5,10,15,20] 
    y3 = [2.383300,207.733500, 896.176300,1951.983300,3404.530200] 

    #Writers in fair 
    x4 = [1,5,10,15,20] 
    y4 = [2.087800,186.017700,883.970600,1987.848100,3701.666800] 



    Writers kept constant at value 10
    Worst Case waiting times
    #Readers in non fair
    x1 = [1,5,10,15,20] 
    y1 = [116.878000,123.678000,134.386000,89.387000,53.753000] 

    #Readers in fair
    x2 = [1,5,10,15,20] 
    y2 = [117.420000,132.819000,150.934000,162.378000,157.111000] 

    #Writers in non fair 
    x3 = [1,5,10,15,20] 
    y3 = [134.808000,207.239000, 145.588000,129.051000,124.889000] 

    #Writers in fair 
    x4 = [1,5,10,15,20] 
    y4 = [141.335000,157.435000,136.115000,126.048000,142.380000] 



    Readers kept constant at value 10
    Worst Case waiting times
    #Readers in non fair
    x1 = [1,5,10,15,20] 
    y1 = [29.896000,74.378000,148.666000,165.366000,265.522000] 

    #Readers in fair
    x2 = [1,5,10,15,20] 
    y2 = [29.313000,97.708000,153.696000,197.056000,264.002000] 

    #Writers in non fair 
    x3 = [1,5,10,15,20] 
    y3 = [21.424000,93.189000,142.870000,209.958000,320.450000 ]

    #Writers in fair 
    x4 = [1,5,10,15,20] 
    y4 = [3.245000,77.938000,142.423000,194.685000,251.813000] 