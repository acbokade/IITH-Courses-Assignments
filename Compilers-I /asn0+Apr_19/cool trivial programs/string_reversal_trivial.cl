-- Printing reversal of given string

class Main inherits IO {
  main(): Object {{
    out_string("Enter the input string\n"); -- taking input string
    let str: String <-in_string() in
    let n: Int <- str.length() in
 	   while 0<n loop -- running loop till start of string
 	   {
 	   	n <- n-1; 
 	   	out_string(str.substr(n,1)); -- Printing last character
 	   }
 	   pool;
 	out_string("\n");
  }};
};