S → Translation_Unit

Translation_Unit → Function_Definition</br>
Translation_Unit → Variable_Declaration</br>
Translation_Unit → Translation_Unit Function_Definition</br>
Translation_Unit → Translation_Unit Variable_Declaration</br>
Translation_Unit → Translation_Unit ERROR ←any token found after a translation unit that doesn’t start a Function Definition or a Variable Declaration is an error</br>

Function_Definition → Function_Header Function_Body</br>
Function_Definition → Function_Header ERROR Function_Header</br>
Function_Definition → Function_Header ERROR Variable_Declaration</br>

Function_Header → FN IDENTIFIER  Optional_Parameters</br>
Function_Header → FN ERROR Function_Header</br>
Function_Header → FN IDENTIFIER ERROR Function_Header</br>

Optional_Parameters → /* empty */ </br>
Optional_Parameters → ‘(‘ Optional Parameter_Definitions ‘)’</br>
Optional_Parameters → ‘(‘ ERROR  ‘)’</br>
Optional_Parameters → ‘(‘ Optional Parameter_Definitions ERROR ‘)’</br>

Optional_Parameter_Definitions → /* empty */</br>
Optional_Parameter_Definitions → Parameter_Definitions</br>

Parameter_Definitions → Parameter_Definition</br>
Parameter_Definitions → Parameter_Definitions ‘,’ Parameter_Definition</br>
Parameter_Definitions → Parameter_Definition ‘,’ ELISPIS</br>
Parameter_Definitions → Parameter_Definition ERROR ‘)’</br>
Parameter_Definitions → Parameter_Definition ‘,’ ERROR ‘)’</br>

Parameter_Definition → IDENTIFIER Optional_Type</br>
Parameter_Definition → IDENTIFIER ERROR ‘)’</br>

Optional_Type → /* empty */</br>
Optional_Type → ‘:’ Variable_Type_Specifier</br>

Variable_Type_Specifier → type1 | type2 | user_declared | etc….</br>

Function_Body → ‘{‘ True_Function_Body ‘}’</br>
Function_Body → ‘{‘ ERROR ‘}’</br>
Function_Body → ‘{‘ True_Function_Body ERROR ‘}’</br>

True_Function_Body → Variable_Declaration</br>
True_Function_Body → Statement</br>
True_Function_Body → True_Function_Body Variable_Declaration</br>
True_Function_Body → True_Function_Body Statement</br>


Variable_Declaration → VAR IDENTIFIER Optional_Type Optional_Variable_Initializer</br>
Variable_Declaration → LET IDENTIFIER Optional_Type Optional_Variable_Initializer</br>
Variable_Declaration → VAR ERROR Variable_Declaration</br>
Variable_Declaration → VAR IDENTIFIER ERROR Variable_Declaration</br>
Variable_Declaration → VAR ERROR Statement</br>
Variable_Declaration → LET IDENTIFIER ERROR Statement</br>
Variable_Declaration → LET  ERROR Variable_Declaration</br>
Variable_Declaration → LET  IDENTIFIER ERROR Variable_Declaration</br>
Variable_Declaration → LET  ERROR Statement</br>
Variable_Declaration → LET  IDENTIFIER ERROR Statement</br>

Optional_Variable_Initializer → /* empty */</br>
Optional_Variable_Initializer → Variable_Initializer</br>

Variable_Initializer → ‘=’  Expression</br>


Statement → Expression ‘;’</br>
Statement → RETURN‘;’</br>
Statement → RETURN Expression ‘;’</br>
Statement → WHILE ‘(‘ Expression ‘)’ Optional_Statement ‘;’</br>
Statement → UNTIL‘(‘ Expression ‘)’ Optional_Statement ‘;’</br>
Statement → DO Optional_Statement WHILE ‘(‘ Expression ‘)’‘;’</br>
Statement → DO Optional_Statement UNTIL ‘(‘ Expression ‘)’‘;’</br>
Statement → FOR‘(‘ Expression  ‘;’ Expression  ‘;’ Expression  ‘)’ Optional_Statement ‘;’</br>
Statement → FOREACH  IDENTIFIER IN Expression Optional_Statement ‘;’</br>
Statement → LOOP Optional_Statement ‘;’</br>
Statement → SWITCH ‘(‘ Expression ‘)’  ‘{‘ Switch_Statements ‘}’</br>
Statement → IF ‘(‘ Expression ‘)’ Statement</br>
Statement → IF ‘(‘ Expression ‘)’ Statement ELSE Statement</br>
Statement → ‘{‘ True_Function_Body ‘}’</br>
Statement → BREAK</br>
Statement → CONTINUE</br>

Optional_Statement → /* empty */</br>
Optional_Statement → Statement</br>

Switch_Statements → Case_Statement</br>
Switch_Statement → Default_Statement</br>
Switch_Statement → Switch_Statement Case_Statement</br>
Switch_Statement → Switch_Statement Default_Statement</br>

Case_Statement → CASE Expression ‘:’</br>
Default_Statement → ‘DEFAULT Expression ‘:’</br>

Expression → Equals_Expression ‘=’ Equals_Expression</br>
Expression → Equals_Expression</br>
Expression → Equals_Expression EQUAL ERROR</br>

Equals_Expression → Relational_Expression EqOp Relation_Expression</br>
Equals_Expression → Relational_Expression</br>
Equals_Expression → Relation_Expression EqOp ERROR</br>

Relational_Expression → Simple_Expression RelOp SimpleExpression</br>
Relation_Expression → Simple_Expression</br>

Simple_Expression → Simple_Expression AddOp Term</br>
Simple_Expression → Term</br>

Term → Term MulOp Factor</br>
Term → Factor</br>

Factor → Constant</br>
Factor → IDENTIFIER</br>
Factor → ‘(‘ Expression ‘)’</br>
Factor → ‘&’ Factor</br>
Factor → ‘&’ IDENTIFIER</br>
Factor → Function_Call

Function_Call → IDENTIFIER ‘(‘ Optional_Arguments ‘)’</br>

Optional_Arguments → /* empty */</br>
Optional_Arguments → Expresson_List</br>

Expression_List → Expression</br>
Expression_List → Expression_List ‘,’ Expression</br>

Identifier_List → IDENTIFIER</br>
Identifer_List → Identifier_List ‘,’ IDENTIFIER</br>

Constant → STRCONSTANT</br>
Constant → INTCONSTANT</br>
Constant → FLOATCONSTANT</br>

AddOp → ‘+’</br>
AddOp → ‘-’</br>

MulOp → ‘*’</br>
MulOp → ‘/’</br>

EqOp → EQUEQU</br>
EqOp → NEQ</br>

RelOp → ‘<’</br>
RelOp → ‘>’</br>
RelOp → LEQ</br>
RelOp → GEQ</br>
