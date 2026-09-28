# Mini C++ Compiler Grammar

## Expressions

expression -> term (('+' | '-') term)*

term -> factor (('*' | '/') factor)*

factor -> NUMBER
        | IDENTIFIER
        | '(' expression ')'

## Examples

10

10 + 20

10 + 20 * 5

x + 10

(x + 10) * 5