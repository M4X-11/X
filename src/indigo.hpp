#include <optional>
#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

std::unordered_map<std::string, std::string> addr;


enum class TokenType {
    uh,
    memory, // temp test
    var_general,
    identifier,
    var_int,
    _return,
    int_lit,
    asign,
    semi,
    plus,
    minus,
    mul,
    div,
    eckig_start,
    ecking_end,
    less_than,
    more_than,
    root,
    alias,
    equal,
    declaration
};

struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};

struct node{
    TokenType type;
    std::string val;

    node* left;
    node* right;

    //new
    std::vector<node*> Npvec;
};

std::vector<Token> Tokenizer(std::string tok);
node* full_ast(std::vector<Token>& tokens);