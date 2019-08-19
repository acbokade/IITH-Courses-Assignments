class Main inherits IO {
  main(): Object {{
  	let name: String <- 'Ajinkya' in -- Strings are enclosed in double quotes "..."
  	out_string(name).out_string("\n");
  	out_string("Sherlock
  		is best") -- A non-escaped newline character may not appear in a string
  }};
};

-- ERRORS
-- "incorrect_prog2.cl", line 3: syntax error at or near ERROR = '
-- "incorrect_prog2.cl", line 6: syntax error at or near ERROR = Unterminated string constant
-- Compilation halted due to lex and parse errors


