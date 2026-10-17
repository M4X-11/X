#include <indigo.hpp>

int pos=0;

int binding_power(TokenType t) {
    switch (t) {
        case TokenType::plus:
        case TokenType::minus:
            return 10;

        case TokenType::mul:
        case TokenType::div:
            return 20;

        default:
            return 0;
    }
}



node* Simple_tree(std::vector<Token>& tokens, int& pos, int min_bp);

node* val_node(std::string val){
    node* n = new node;
    n->val=val;
    n->type=TokenType::int_lit;
    n->left = nullptr;
    n->right = nullptr;
    
    return n;
}

node* val_node_from_token(const Token& t){
    node* n = new node;
    n->val = t.value.value_or(std::string());
    n->left = nullptr;
    n->right = nullptr;
    if (t.type == TokenType::int_lit)
        n->type = TokenType::int_lit;
    else if (t.type == TokenType::identifier)
        n->type = TokenType::identifier;
    else if (t.type == TokenType::memory)
        n->type = TokenType::memory;
    else{
        //n->type = t.type;
    }
    return n;
}

node* parse_LowVar(std::string mem, std::vector<Token> tokens){
    node* n = new node;
    n->type = TokenType::identifier;
    //n->val = mem;

    node* nAlias = new node;
    nAlias->val = mem;
    nAlias->type = TokenType::alias;

    node* nAddress = new node;
    nAddress->type = TokenType::memory;
    nAddress->val = addr[mem];

    
    pos+=1;

    n->Npvec.push_back(Simple_tree(tokens, pos, 0));



    n->Npvec.push_back(nAlias);
    n->Npvec.push_back(nAddress);
    //n->Npvec.push_back(nSet);


    return n;
}

node* op_node(TokenType t, node* l, node* r){
    node* n = new node;


    /*
    if (t == TokenType::plus || t == TokenType::minus){
        n->type = NodeType::strich;
    }else{
        n->type = NodeType::punkt;
    }*/
   n->type=t;

    
    n->Npvec.push_back(l);
    n->Npvec.push_back(r);
    //n->left=l;
    //n->right=r;
    return n;
}

node* parse_intVar(){

    return NULL;
}

node* Simple_tree(std::vector<Token>& tokens, int& pos, int min_bp) {

    if (tokens[pos].type == TokenType::semi){
        pos++;
        return nullptr;
    }

    if (tokens[pos].type == TokenType::identifier){
        node* n = new node;
        n->type = TokenType::alias;
        n->val = tokens[pos].value.value();
        pos++;
        return n;
    }

    

    if (pos >= tokens.size())
        return nullptr;
    // Parse the first value
    if (tokens[pos].type == TokenType::_return) {
        pos++;  // move past "return"

        node* expression = Simple_tree(tokens, pos, min_bp);

        node* n = new node;
        n->type = TokenType::_return;
        //n->left = expression;
        n->Npvec.push_back(expression);
        //n->right = nullptr;

        return n;
    }

    if (tokens[pos].type == TokenType::var_int){
        node* n = new node;
        n->type = TokenType::declaration;
        pos++;
        n->val = tokens[pos].value.value();
        pos+=2;
        n->Npvec.push_back(Simple_tree(tokens, pos, 0));
        return n;
    }

    /////////
    if (tokens[pos].type == TokenType::var_general) {
    if (pos + 4 < tokens.size() && 
        tokens[pos+1].type == TokenType::identifier &&
        tokens[pos+2].type == TokenType::less_than && 
        tokens[pos+3].type == TokenType::memory && 
        tokens[pos+4].type == TokenType::more_than) {
        
        pos++;
        addr[tokens[pos].value.value()] = tokens[pos+2].value.value();
        pos += 4; // Advance past the identifier and <memory>

        return parse_LowVar(tokens[pos-4].value.value(), tokens);
    } else {
        //printf("error: missing addr\n");
        std::cout << "error: missing addr" << std::endl;
        pos++;
        return  NULL;
        //pos++; // Just skip the identifier
    }}
    //////////////////

    if (pos >= tokens.size()) return nullptr;
    node* left = val_node_from_token(tokens[pos]);

    pos++;

    // Look at operators after it
    while (pos < tokens.size()) {

        TokenType op = tokens[pos].type;

        int op_bp = binding_power(op);

        // Operator isn't strong enough
        if (op_bp <= min_bp)
            break;

        pos++; // consume operator

        // Parse right side
        node* right = Simple_tree(tokens, pos, op_bp);

        left = op_node(op, left, right);
    }

    return left;
}

node* full_ast(std::vector<Token>& tokens){
    node* Rnode = new node;
    Rnode->type = TokenType::root;

    while (pos < tokens.size())
    {
        std::cout << pos << std::endl;
        Rnode->Npvec.push_back(Simple_tree(tokens, pos, 0));
    }
    return Rnode;
}