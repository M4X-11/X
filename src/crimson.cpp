#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <optional>
#include <string>

int pos=0;

enum class TokenType {
    _return,
    int_lit,
    semi,
    plus,
    minus,
    mul,
    div,
    eckig_start,
    ecking_end,
    less_than,
    more_than
};

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




struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};



enum class NodeType{
    _return,
    punkt,
    strich,
    value
};

struct node{
    TokenType type;
    int val;

    node* left;
    node* right;
};

node* val_node(int val){
    node* n = new node;
    n->val=val;
    n->type=TokenType::int_lit;
    n->left = nullptr;
    n->right = nullptr;
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

    
    
    n->left=l;
    n->right=r;
    return n;
}

node* tree(std::vector<Token> tokens, int bp){
    node* left = val_node(std::stoi(tokens[pos].value.value()));
    pos++;
    //node* op = op_node(tokens[pos].type)


    while (bp > binding_power(tokens[pos].type))
    {
        /* code */
    }
    
    
    return NULL;
}

node* Simple_tree(std::vector<Token>& tokens, int& pos, int min_bp) {

    if (pos >= tokens.size())
        return nullptr;
    // Parse the first value
    if (tokens[pos].type == TokenType::_return) {
        pos++;  // move past "return"

        node* expression = Simple_tree(tokens, pos, min_bp);

        node* n = new node;
        n->type = TokenType::_return;
        n->left = expression;
        n->right = nullptr;

        return n;
    }

    node* left = val_node(
        std::stoi(tokens[pos].value.value())
    );

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


std::vector<Token> Tokenizer(std::string tok){
    std::vector<Token> tokens;
    std::string buffer;
    
    
    for (size_t i = 0; i < tok.size(); i++){
        char c = tok.at(i);
        
        if (std::isalpha(c)){
            buffer.push_back(c);
            i++;
            
            while (i < tok.size() && std::isalnum(tok.at(i))) {
                buffer.push_back(tok.at(i));
                i++;
            }
            i--; 

            if (buffer == "return"){
                tokens.push_back({.type = TokenType::_return});
                buffer.clear();
            } else {
                std::cerr << "error: unrecognized identifier '" << buffer << "'" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isdigit(c)){
            buffer.push_back(c);
            i++;
            
            while (i < tok.size() && std::isdigit(tok.at(i))) {
                buffer.push_back(tok.at(i));
                i++;
            }
            i--; 
            
            tokens.push_back({.type = TokenType::int_lit, .value = buffer});
            buffer.clear();
        }
        else if (c == '+')
        {
            tokens.push_back({.type = TokenType::plus});
        }
        else if (c == '-')
        {
            tokens.push_back({.type = TokenType::minus});
        }
        else if (c == '*')
        {
            tokens.push_back({.type = TokenType::mul});
        }
        else if (c == '/')
        {
            tokens.push_back({.type = TokenType::div});
        }
        
        else if (c == ';'){
            tokens.push_back({.type = TokenType::semi});
        }
        else if (c == '['){
            tokens.push_back({.type = TokenType::eckig_start});
        }
        else if (c == ']'){
            tokens.push_back({.type = TokenType::ecking_end});
        }
        else if (c == '<'){
            tokens.push_back({.type = TokenType::less_than});
        }
        else if (c == '>'){
            tokens.push_back({.type = TokenType::more_than});
        }
        else if (std::isspace(c)){
            continue;
        }
    }
    return tokens;
}

std::stringstream stream;

std::string generate(node n)
{
    if (n.type == TokenType::int_lit) {

        stream << "    mov rax, " << n.val << "\n";
        stream << "    push rax\n";
    }

    else if (n.type == TokenType::_return) {

        generate(*n.left);

        stream << "    pop rax\n";
        stream << "    mov rdi, rax\n";
        stream << "    mov rax, 60\n";
        stream << "    syscall\n";
    }

    else {

        generate(*n.left);
        generate(*n.right);

        stream << "    pop rbx\n";
        stream << "    pop rax\n";

        switch (n.type)
        {
        case TokenType::plus:
            stream << "    add rax, rbx\n";
            stream << "    push rax\n";
            break;

        case TokenType::minus:
            stream << "    sub rax, rbx\n";
            stream << "    push rax\n";
            break;

        case TokenType::mul:
            stream << "    imul rax, rbx\n";
            stream << "    push rax\n";
            break;

        case TokenType::div:
            stream << "    cqo\n";
            stream << "    idiv rbx\n";
            stream << "    push rax\n";
            break;

        default:
            break;
        }
    }

    return stream.str();
}



int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout << "no file specified" << std::endl;
    }
    //std::cout << argv[1] << std::endl;


    //read
    // Create a text string, which is used to output the text file
    std::string myText;
    std::stringstream buf;

    // Read from the text file
    std::ifstream MyReadFile(argv[1]);

    if (!MyReadFile.is_open()) {
        std::cout << "could not open file: " << argv[1] << std::endl;
        return 1;
    }

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
    // Output the text from the file
    //std::cout << myText;
    if (!myText.empty() && myText.front() == '/') {
        continue;
    }
    std::cout << myText;
    buf << myText;
    }

    // Close the file
    
    
    //std::cout << myText << std::endl;

    
    

  

auto tokens = Tokenizer(myText);
auto hm = Simple_tree(tokens, pos, 0);

std::cout << "tokens = " << tokens.size() << '\n';

{
    std::ofstream uh("lol.asm");
    stream << "global _start\n_start:\n";
    uh << generate(*hm);
}
    MyReadFile.close();
    std::string filename = "lol.asm";
    
    // Construct the command string
    std::string command = "nasm -felf64 " + filename;

    std::system(command.c_str());

    std::system("ld -o out lol.o");

    auto tokenr = Tokenizer("return []]3+2;");

    std::cout << tokenr.size() << '\n';

    return 0;
}