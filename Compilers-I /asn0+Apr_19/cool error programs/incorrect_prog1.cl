class Main inherits IO {
  main(): Object {{
  	out_string("Enter a number\n");
  	let input: int <- in_int() in  -- incorrect declaration of identifier (int is not identified by compiler)
  	out_int(input).out_string("\n");
  	out_string("Enter a number\n");
  	let inpu$t: Int <- in_int() in  -- incorrect declaration of identifier ('$' is not allowed)
  	out_int(inpu$t).out_string("\n");
  	out_string("Enter a string\n");
  	let Name: String <- in_string() in -- incorrect declaration of identifier (starting with uppercase)
    out_string(Name).out_string("\n");
  }};
};

-- ERRORS
-- "incorrect_prog1.cl", line 4: syntax error at or near OBJECTID = int
-- "incorrect_prog1.cl", line 7: syntax error at or near ERROR = $
-- "incorrect_prog1.cl", line 8: syntax error at or near ERROR = $
-- "incorrect_prog1.cl", line 11: syntax error at or near TYPEID = Name
-- Compilation halted due to lex and parse errors



