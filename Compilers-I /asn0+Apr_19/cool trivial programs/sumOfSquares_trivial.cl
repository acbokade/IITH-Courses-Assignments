-- Calculating sum of squares of first n natural numbers

class Main inherits IO{
	main(): Object{{
		out_string("Enter the number n upto which you want to find sum of squares of\n");
		let n: Int <- in_int()  in -- n
		let total: Int <- 0 in -- storing sum of squares of natural numbers
		if n < 0 then
   		out_string("ERROR: Number of elements must be greater or equal to 0\n")
  		else {
  			let loopVar : Int <- 1 in 
    		(while loopVar <= n loop -- looping till n
    		  {
    		      total <- total + loopVar*loopVar; -- adding sum of square of current value 
    		      loopVar <- loopVar + 1;
    		  }
    		  pool
    		);
    		out_string("The sum of squares of first ").out_int(n).out_string(" natural numbers is ").out_int(total);
    		out_string("\n");
   		}
    	fi;
	}};
};