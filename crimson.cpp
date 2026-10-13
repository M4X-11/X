#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <optional>
#include <string>

#include <unordered_map>

std::unordered_map<std::string, std::string> addr;




int pos=0;

enum class TokenType {
    memory, // temp test
    var_general,
    identifier,
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
    std::string val;

    node* left;
    node* right;

    //new
    std::vector<node> vec;
};

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
    else
        n->type = t.type;
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
    if (pos >= tokens.size()) return nullptr;
    node* left = val_node_from_token(tokens[pos]);
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
    if (tokens[pos].type == TokenType::identifier) {
    if (pos + 3 < tokens.size() && 
        tokens[pos+1].type == TokenType::less_than && 
        tokens[pos+2].type == TokenType::memory && 
        tokens[pos+3].type == TokenType::more_than) {
        
        pos += 4; // Advance past the identifier and <memory>
        addr[std::to_string(pos-1)] = std::to_string(pos); 
    } else {
        //printf("error: missing addr\n");
        std::cout << "error: missing addr" << std::endl;
        return  NULL;
        pos++; // Just skip the identifier
    }
}

    /*
    if (tokens[pos].type == TokenType::var_general) {
        pos++;  // move past "return"

        node* expression = Simple_tree(tokens, pos, min_bp);

        node* n = new node;
        n->type = TokenType::_return;
        n->left = expression;
        n->right = nullptr;

        return n;
    }*/

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

int dec=0;
int m=0;
std::vector<Token> Tokenizer(std::string tok){
    std::vector<Token> tokens;
    std::string buffer;
    
    
    for (size_t i = 0; i < tok.size(); i++){
        char c = tok.at(i);

         if (c == '>'){
            tokens.push_back({.type = TokenType::more_than});
            m=0;
        }
        
        if (std::isalpha(c) || m){
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
            } else
            if (buffer == "var"){
                tokens.push_back({.type = TokenType::var_general});
                buffer.clear();
            }
            else if (!dec) {
                tokens.push_back({
                    .type = TokenType::identifier,
                    .value = buffer
                });
                std::cout << static_cast<int>(TokenType::identifier) << " : " << buffer << std::endl;
                buffer.clear();
                dec=1;
            }else {
                tokens.push_back({
                    .type = TokenType::memory,
                    .value = buffer
                });
                std::cout << static_cast<int>(TokenType::memory) << " : " << buffer << std::endl;
                buffer.clear();
                dec=0;
            }
            /*else{
                std::cerr << "error: unrecognized identifier '" << buffer << "'" << std::endl;
                exit(EXIT_FAILURE);
            }*/
        }
        else if (std::isdigit(c) && m==0){
            buffer.push_back(c);
            i++;
            
            while (i < tok.size() && std::isdigit(tok.at(i))) {
                buffer.push_back(tok.at(i));
                i++;
            }
            i--; 
            
            tokens.push_back({.type = TokenType::int_lit, .value = buffer});
            std::cout << static_cast<int>(TokenType::int_lit) << " : " << buffer << std::endl;
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
            m=1;
        }
        
        else if (std::isspace(c)){
            continue;
        }
    }
    return tokens;
}

std::stringstream stream;

std::string generate(node* n)
{
    if (n == nullptr)
        return stream.str();

    if (n->type == TokenType::int_lit) {
        stream << "    mov rax, " << n->val << "\n";
        stream << "    push rax\n";
        return stream.str();
    }

    if (n->type == TokenType::identifier) {
        stream << "    mov rax, " << addr[n->val] << "\n";
        stream << "    push rax\n";
        return stream.str();
    }

    if (n->type == TokenType::_return) {
        generate(n->left);

        stream << "    pop rax\n";
        stream << "    mov rdi, rax\n";
        stream << "    mov rax, 60\n";
        stream << "    syscall\n";

        return stream.str();
    }

    // binary operators
    generate(n->left);
    generate(n->right);

    stream << "    pop rbx\n";
    stream << "    pop rax\n";

    switch (n->type)
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
    std::cout << "\n";

    // Close the file
    
    
    //std::cout << myText << std::endl;

    
    

  

auto tokens = Tokenizer(buf.str());
auto hm = Simple_tree(tokens, pos, 0);

std::cout << '\n' << std::endl;
for (int i=0; i<tokens.size(); i++){
    std::cout << "tok[" << i << "]: " << static_cast<int>(tokens.at(i).type) << '\n';
}

if (hm == nullptr) {
    std::cerr << "parse error: AST is null\n";
    return 1;
}

std::cout << "tokens = " << tokens.size() << '\n';

{
    std::ofstream uh("lol.asm");
    stream << "global _start\n_start:\n";
    uh << generate(hm);
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