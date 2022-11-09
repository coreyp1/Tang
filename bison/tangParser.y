// Declarations can be found here:
// https://www.gnu.org/software/bison/manual/html_node/Decl-Summary.html
// Defines can be found here:
// https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html

// Minimum version requirement.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025require
%require "3.8.2"

// Use a C++ skeleton.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025skeleton
%skeleton "lalr1.cc"

// Create a .h file with the proper definitions for the lexer.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025defines-2
%defines

// Choose the namespace to hold the generated code to avoid conflicts.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002enamespace
%define api.namespace { Tang }

// Choose the name of the parser that will be generated.  (e.g., "Parser")
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002eparser_002eclass-1
%define api.parser.class { TangParser }

// Use variant-based values instead of the old union syntax.  Only available
// in C++, but it allows us to use objects without pointer workarounds.
// https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-Variants.html
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002evalue_002etype-1
%define api.value.type variant

// In combination with "%defines", the type "symbol_type" will be defined
// and used when appropriate as the return type of yylex().  In short, it
// consolidates the information returned by the lexer, which makes our job
// easier.  This option should be used when using "api.value.type variant".
// https://www.gnu.org/software/bison/manual/html_node/Complete-Symbols.html#Complete-Symbols
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002etoken_002econstructor
%define api.token.constructor

// Use runtime assertions to verify that variant objects are constructed and
// destroyed properly.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002eassert
%define parse.assert

// Define the YYDEBUG macro so that debugging facilities are compiled.
// https://www.gnu.org/software/bison/manual/bison.html#Tracing
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002etrace
%define parse.trace

// Provide a more helpful error message.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002eerror-verbose
%define parse.error verbose

// Add a locations class to track the parsing location, so that we can generate
// more helpful error messages.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025locations
%locations

// Additional arguments that yylex() should accept.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025lex_002dparam-3
%lex-param { Tang::TangScanner & scanner }

// Additional arguments that yyparse() should accept.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025parse_002dparam-3
%parse-param { Tang::TangScanner & scanner }
%parse-param { std::shared_ptr<Tang::AstNode> & ast }
%parse-param { Tang::Error * & parseError }

// Add a prefix to token names
// %define api.token.prefix {TOKEN_}
// Because the prefix will be added to a suffix, do not include any whitespace
// between the prefix and the closing '}'
%define api.token.prefix {TANG_PARSER_}

// Declare tokens (as opposed to the old, %union approach.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025token
%token EOF 0 "end of code"
%token <int64_t> INTEGER "integer literal"
%token <long double> FLOAT "float literal"
%token <bool> BOOLEAN "boolean literal"
%token <std::string> STRING "string"
%token STRINGERROR "Malformed String"
%token <std::string> IDENTIFIER "identifier"
%token ASSIGN "="
%token PLUS "+"
%token MINUS "-"
%token MULTIPLY "*"
%token DIVIDE "/"
%token MODULO "%"
%token EXCLAMATIONPOINT "!"
%token LPAREN "("
%token RPAREN ")"
%token LESSTHAN "<"
%token LESSTHANEQUAL "<="
%token GREATERTHAN ">"
%token GREATERTHANEQUAL ">="
%token EQUALCOMPARE "=="
%token NOTEQUAL "!="
%token AND "&&"
%token OR "||"
%token LBRACE "{"
%token RBRACE "}"
%token IF "if"
%token ELSE "else"
%token DO "do"
%token WHILE "while"
%token FOR "for"
%token AS "as"
%token NULL "null"
%token CASTINT "int"
%token CASTFLOAT "float"
%token CASTBOOLEAN "boolean"
%token PRINT "print"
%token QUESTIONMARK "?"
%token COLON ":"
%token SEMICOLON ";"

// Any %type declarations of non-terminals.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025type
%type <std::shared_ptr<Tang::AstNode>> program
%type <std::shared_ptr<Tang::AstNode>> expression
%type <std::vector<std::shared_ptr<Tang::AstNode>>> statements
%type <std::shared_ptr<Tang::AstNode>> statement
%type <std::shared_ptr<Tang::AstNode>> codeBlock
%type <std::shared_ptr<Tang::AstNode>> openStatement
%type <std::shared_ptr<Tang::AstNode>> closedStatement
%type <std::shared_ptr<Tang::AstNode>> forExpression

// Precedence rules.
// For guidance, see:
// https://efxa.org/2014/05/17/techniques-for-resolving-common-grammar-conflicts-in-parsers/
// Notice that the order is reversed from:
// https://en.cppreference.com/w/cpp/language/operator_precedence
// Here, rules are in order of lowest to highest precedence.
%right "=" "?" ":"
%left "||"
%left "&&"
%left "==" "!="
%left "<" "<=" ">" ">="
%left "+" "-"
%left "*" "/" "%"
%right UMINUS AS "!"

// Code sections.
// https://www.gnu.org/software/bison/manual/bison.html#g_t_0025code-Summary
// `requires` will be included in the .hpp file.
%code requires {
#include <memory>
#include <stdint.h>
#include "astNode.hpp"
#include "error.hpp"
namespace Tang {
  class TangScanner;
}
}

// `top` will be included at the top of the .cpp file, but not in .hpp.
%code top {
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "location.hh"
#include "astNodeUnary.hpp"
#include "astNodeAssign.hpp"
#include "astNodeBinary.hpp"
#include "astNodeFloat.hpp"
#include "astNodeIdentifier.hpp"
#include "astNodeInteger.hpp"
#include "astNodeBoolean.hpp"
#include "astNodeString.hpp"
#include "astNodeTernary.hpp"
#include "astNodeCast.hpp"
#include "astNodeBlock.hpp"
#include "astNodeIfElse.hpp"
#include "astNodeWhile.hpp"
#include "astNodeDoWhile.hpp"
#include "astNodeFor.hpp"
#include "astNodePrint.hpp"

// We must provide the yylex() function.
// yylex() arguments are defined in the bison .y file.
// It is conceivable that a programmer may want to have multiple compilers in
// the same project.  Each compiler will need its own yylex() function.
// Because yylex() is only defined and used in this file, we can set its
// linkage as "internal", by declaring the function "static", which allows
// each compiler's yylex() to not interfere with that of another linked file.
// https://en.cppreference.com/w/cpp/language/storage_duration

static Tang::TangParser::symbol_type yylex(Tang::TangScanner & scanner) {
  return scanner.get_next_token();
}
}


// The grammar start symbol (non-terminal).
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025start
%start program


%%
// Grammar Section.
// https://efxa.org/2014/05/17/techniques-for-resolving-common-grammar-conflicts-in-parsers/
// https://stackoverflow.com/a/12732388/3821565

// `program` represents every possible syntactically-valid program.
program
  : expression
    {
      ast = $1;
    }
  | statements
    {
      ast = std::make_shared<AstNodeBlock>($1, @1);
    }
  | EOF
    {}
  ;

// `statements` represent a sequence of `statement` expressions.
statements
  : statement
    {
      vector<shared_ptr<AstNode>> s{};
      s.push_back($1);
      $$ = s;
    }
  | statements statement
    {
      $1.push_back($2);
      $$ = $1;
    }
  ;

// `statement` represents an `expression`
statement
  : closedStatement
  | openStatement
  ;

// To avoid the "dangling else" problem:
// https://en.wikipedia.org/wiki/Dangling_else#Avoiding_the_conflict_in_LR_parsers
// These should only contain closedStatements

closedStatement
  : "if" "(" expression ")" closedStatement "else" closedStatement
    {
      $$ = std::make_shared<AstNodeIfElse>($3, $5, $7, @1);
    }
  | "while" "(" expression ")" closedStatement
    {
      $$ = std::make_shared<AstNodeWhile>($3, $5, @1);
    }
  | "do" statement "while" "(" expression ")" ";"
    {
      $$ = std::make_shared<AstNodeDoWhile>($5, $2, @1);
    }
  | "for" "(" forExpression ";" forExpression ";" forExpression ")" closedStatement
    {
      $$ = std::make_shared<AstNodeFor>($3, $5, $7, $9, @1);
    }
  | codeBlock
  | expression ";"
  ;

// These should only have an openStatement as the last terminal.
openStatement
  : "if" "(" expression ")" statement
    {
      $$ = std::make_shared<AstNodeIfElse>($3, $5, @1);
    }
  | "if" "(" expression ")" closedStatement "else" openStatement
    {
      $$ = std::make_shared<AstNodeIfElse>($3, $5, $7, @1);
    }
  | "while" "(" expression ")" openStatement
    {
      $$ = std::make_shared<AstNodeWhile>($3, $5, @1);
    }
  | "for" "(" forExpression ";" forExpression ";" forExpression ")" openStatement
    {
      $$ = std::make_shared<AstNodeFor>($3, $5, $7, $9, @1);
    }
  ;

// `forExpression` is an optional expression.
forExpression
  : %empty
    {
      $$ = std::make_shared<AstNode>(Tang::location{});
    }
  | expression
  ;

// `codeBlock` represents a series of statements.
codeBlock
  : "{" "}"
    {
      $$ = std::make_shared<AstNodeBlock>(std::vector<shared_ptr<AstNode>>{}, @1);
    }
  | "{" statements "}"
    {
      $$ = std::make_shared<AstNodeBlock>($2, @1);
    }
  ;

// `expression` represents a computable value.
expression
  : NULL
    {
      $$ = std::make_shared<Tang::AstNode>(@1);
    }
  | IDENTIFIER
    {
      $$ = std::make_shared<Tang::AstNodeIdentifier>($1, @1);
    }
  | INTEGER
    {
      $$ = std::make_shared<Tang::AstNodeInteger>($1, @1);
    }
  | FLOAT
    {
      $$ = std::make_shared<AstNodeFloat>($1, @1);
    }
  | BOOLEAN {
      $$ = std::make_shared<AstNodeBoolean>($1, @1);
    }
  | STRING {
      $$ = std::make_shared<AstNodeString>($1, @1);
    }
  | expression "=" expression
    {
      $$ = std::make_shared<AstNodeAssign>($1, $3, @2);
    }
  | expression "+" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Add, $1, $3, @2);
    }
  | expression "-" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Subtract, $1, $3, @2);
    }
  | expression "*" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Multiply, $1, $3, @2);
    }
  | expression "/" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Divide, $1, $3, @2);
    }
  | expression "%" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Modulo, $1, $3, @2);
    }
  | "-" expression %prec UMINUS
    {
      $$ = std::make_shared<AstNodeUnary>(AstNodeUnary::Negative, $2, @1);
    }
  | "!" expression
    {
      $$ = std::make_shared<AstNodeUnary>(AstNodeUnary::Not, $2, @1);
    }
  | expression "<" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::LessThan, $1, $3, @2);
    }
  | expression "<=" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::LessThanEqual, $1, $3, @2);
    }
  | expression ">" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::GreaterThan, $1, $3, @2);
    }
  | expression ">=" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::GreaterThanEqual, $1, $3, @2);
    }
  | expression "==" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Equal, $1, $3, @2);
    }
  | expression "!=" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::NotEqual, $1, $3, @2);
    }
  | expression "&&" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::And, $1, $3, @2);
    }
  | expression "||" expression
    {
      $$ = std::make_shared<AstNodeBinary>(AstNodeBinary::Or, $1, $3, @2);
    }
  | "(" expression ")"
    {
      $$ = $2;
    }
  | expression "as" "int"
    {
      $$ = std::make_shared<AstNodeCast>(AstNodeCast::Integer, $1, @2);
    }
  | expression "as" "float"
    {
      $$ = std::make_shared<AstNodeCast>(AstNodeCast::Float, $1, @2);
    }
  | expression "as" "boolean"
    {
      $$ = std::make_shared<AstNodeCast>(AstNodeCast::Boolean, $1, @2);
    }
  | "print" "(" expression ")"
    {
      $$ = std::make_shared<AstNodePrint>(AstNodePrint::Default, $3, @1);
    }
  | expression "?" expression ":" expression
    {
      $$ = std::make_shared<AstNodeTernary>($1, $3, $5, @2);
    }
  ;

%%

// An error-handler must be defined.  See the end of the following section:
// https://www.gnu.org/software/bison/manual/bison.html#A-Simple-C_002b_002b-Example
void Tang::TangParser::error(const location & location, const std::string & message) {
  parseError = new Error{message, location};
}

