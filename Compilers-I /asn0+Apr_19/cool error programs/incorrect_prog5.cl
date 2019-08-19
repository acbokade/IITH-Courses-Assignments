class Main inherits IO {
  main(): Object {{
  	let input: Str ing <- in_string() in -- no whitespaces should be there between keywords. 
  	out_int(input);
  }};
};

-- ERRORS
-- "incorrect_prog5.cl", line 3: syntax error at or near OBJECTID = ing
-- Compilation halted due to lex and parse errors


