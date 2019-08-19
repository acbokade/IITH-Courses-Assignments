class Main inherits IO {
  main(): Object {{
  	out_string("Enter a string\n"); -- Proper commenting 
  	let name: String <- in_string() in - improper commenting
    out_string(name).out_string("\n");
  }};
};

-- ERRORS
-- "incorrect_prog3.cl", line 4: syntax error at or near '-'
-- Compilation halted due to lex and parse errors


