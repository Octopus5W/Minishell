# my_minishell


* The source code is first split into smaller chunks called tokens through the process of lexical analysis. Lexical analysis is also called tokenization.

* The tokens are then parsed into a tree called the syntax tree by the parser. 

[An Abstract Syntax Tree (AST) abstracts away certain details and retains just enough information to help the compiler understand the structure of the code.]

We know that **parse trees** are tree data structures that contain the grammatical structure of our code; in other words, they contain all the syntactic information that appears in a code “sentence”, and is derived directly from the grammar of the programming language itself.
A **abstract syntax tree**, on the other hand, ignores a significant amount of the syntatic information that a parse tree would otherwise contain.

grammar = [http://craftinginterpreters.com/representing-code.html]