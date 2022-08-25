S → Translation_Unit

Translation_Unit → Function_Definition</br>
Translation_Unit → Variable_Declaration
Translation_Unit → Translation_Unit Function_Definition
Translation_Unit → Translation_Unit Variable_Declaration
Translation_Unit → Translation_Unit ERROR ←any token found after a translation unit that doesn’t start a Function Definition or a Variable Declaration is an error

Function_Definition → Function_Header Function_Body
Function_Definition → Function_Header ERROR Function_Header
Function_Definition → Function_Header ERROR Variable_Declaration

Function_Header → FN IDENTIFIER  Optional_Parameters
Function_Header → FN ERROR Function_Header
Function_Header → FN IDENTIFIER ERROR Function_Header

Optional_Parameters → /* empty */ 
Optional_Parameters → ‘(‘ Optional Parameter_Definitions ‘)’
Optional_Parameters → ‘(‘ ERROR  ‘)’
Optional_Parameters → ‘(‘ Optional Parameter_Definitions ERROR ‘)’

Optional_Parameter_Definitions → /* empty */
Optional_Parameter_Definitions → Parameter_Definitions

Parameter_Definitions → Parameter_Definition
Parameter_Definitions → Parameter_Definitions ‘,’ Parameter_Definition
Parameter_Definitions → Parameter_Definition ‘,’ ELISPIS
Parameter_Definitions → Parameter_Definition ERROR ‘)’
Parameter_Definitions → Parameter_Definition ‘,’ ERROR ‘)’

Parameter_Definition → IDENTIFIER Optional_Type
Parameter_Definition → IDENTIFIER ERROR ‘)’

Optional_Type → /* empty */
Optional_Type → ‘:’ Variable_Type_Specifier

Variable_Type_Specifier → type1 | type2 | user_declared | etc….

Function_Body → ‘{‘ True_Function_Body ‘}’
Function_Body → ‘{‘ ERROR ‘}’
Function_Body → ‘{‘ True_Function_Body ERROR ‘}’

True_Function_Body → Variable_Declaration
True_Function_Body → Statement
True_Function_Body → True_Function_Body Variable_Declaration
True_Function_Body → True_Function_Body Statement


Variable_Declaration → VAR IDENTIFIER Optional_Type Optional_Variable_Initializer
Variable_Declaration → LET IDENTIFIER Optional_Type Optional_Variable_Initializer
Variable_Declaration → VAR ERROR Variable_Declaration
Variable_Declaration → VAR IDENTIFIER ERROR Variable_Declaration
Variable_Declaration → VAR ERROR Statement
Variable_Declaration → LET IDENTIFIER ERROR Statement
Variable_Declaration → LET  ERROR Variable_Declaration
Variable_Declaration → LET  IDENTIFIER ERROR Variable_Declaration
Variable_Declaration → LET  ERROR Statement
Variable_Declaration → LET  IDENTIFIER ERROR Statement

Optional_Variable_Initializer → /* empty */
Optional_Variable_Initializer → Variable_Initializer

Variable_Initializer → ‘=’  Expression


Statement → Expression ‘;’
Statement → RETURN‘;’
Statement → RETURN Expression ‘;’
Statement → WHILE ‘(‘ Expression ‘)’ Optional_Statement ‘;’
Statement → UNTIL‘(‘ Expression ‘)’ Optional_Statement ‘;’
Statement → DO Optional_Statement WHILE ‘(‘ Expression ‘)’‘;’
Statement → DO Optional_Statement UNTIL ‘(‘ Expression ‘)’‘;’
Statement → FOR‘(‘ Expression  ‘;’ Expression  ‘;’ Expression  ‘)’ Optional_Statement ‘;’
Statement → FOREACH  IDENTIFIER IN Expression Optional_Statement ‘;’
Statement → LOOP Optional_Statement ‘;’
Statement → SWITCH ‘(‘ Expression ‘)’  ‘{‘ Switch_Statements ‘}’
Statement → IF ‘(‘ Expression ‘)’ Statement
Statement → IF ‘(‘ Expression ‘)’ Statement ELSE Statement
Statement → ‘{‘ True_Function_Body ‘}’
Statement → BREAK
Statement → CONTINUE

Optional_Statement → /* empty */
Optional_Statement → Statement

Switch_Statements → Case_Statement
Switch_Statement → Default_Statement
Switch_Statement → Switch_Statement Case_Statement
Switch_Statement → Switch_Statement Default_Statement

Case_Statement → CASE Expression ‘:’
Default_Statement → ‘DEFAULT Expression ‘:’

Expression → Equals_Expression ‘=’ Equals_Expression
Expression → Equals_Expression
Expression → Equals_Expression EQUAL ERROR

Equals_Expression → Relational_Expression EqOp Relation_Expression
Equals_Expression → Relational_Expression
Equals_Expression → Relation_Expression EqOp ERROR

Relational_Expression → Simple_Expression RelOp SimpleExpression
Relation_Expression → Simple_Expression

Simple_Expression → Simple_Expression AddOp Term
Simple_Expression → Term

Term → Term MulOp Factor
Term → Factor

Factor → Constant
Factor → IDENTIFIER
Factor → ‘(‘ Expression ‘)’
Factor → ‘&’ Factor
Factor → ‘&’ IDENTIFIER
Factor → Function_Call

Function_Call → IDENTIFIER ‘(‘ Optional_Arguments ‘)’

Optional_Arguments → /* empty */
Optional_Arguments → Expresson_List

Expression_List → Expression
Expression_List → Expression_List ‘,’ Expression

Identifier_List → IDENTIFIER
Identifer_List → Identifier_List ‘,’ IDENTIFIER

Constant → STRCONSTANT
Constant → INTCONSTANT
Constant → FLOATCONSTANT

AddOp → ‘+’
AddOp → ‘-’

MulOp → ‘*’
MulOp → ‘/’

EqOp → EQUEQU
EqOp → NEQ

RelOp → ‘<’
RelOp → ‘>’
RelOp → LEQ
RelOp → GEQ
