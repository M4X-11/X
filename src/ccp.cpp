#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <optional>
#include <string>

enum class TokenType {
    _return,
    int_lit,
    semi,
    plus,
    minus,
    mul,
    div
};

struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};








void stupidTree(std::vector<Token> tokenss){

}








std::string asmp(std::vector<Token> tkn){
    std::stringstream stream;
    
    stream << "global _start\n_start:\n";
    std::cout << tkn.size() << std::endl;
    for (int i=0; i<tkn.size(); i++){
        std::cout << "\ntest" << std::endl;
        const Token& token = tkn[i];
        if (3 >= tkn.size() && token.type == TokenType::_return && tkn.at(i+1).type == TokenType::int_lit &&tkn.at(i+2).type == TokenType::semi){
            stream << "    mov rax, 60\n    mov rdi, " << tkn[i+1].value.value() << "\n    syscall";
        }
    }
    return stream.str();
}



std::vector<Token> Tokenizer(std::string tok){
    std::vector<Token> tokens;
    std::string buffer;
    
    // FIX 1: Changed '>' to '<' so the loop actually runs
    for (size_t i = 0; i < tok.size(); i++){
        char c = tok.at(i);
        
        if (std::isalpha(c)){
            buffer.push_back(c);
            i++;
            // FIX 2: Added safety check (i < tok.size()) to prevent out-of-bounds crashes
            while (i < tok.size() && std::isalnum(tok.at(i))) {
                buffer.push_back(tok.at(i));
                i++;
            }
            i--; // Step back so the outer loop doesn't skip a character

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
            // FIX 3: Added safety check and updated the character lookup to tok.at(i)
            while (i < tok.size() && std::isdigit(tok.at(i))) {
                buffer.push_back(tok.at(i));
                i++;
            }
            i--; // Step back so the outer loop doesn't skip a character
            
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
        
        else if (c == ';'){
            tokens.push_back({.type = TokenType::semi});
        }
        else if (std::isspace(c)){
            continue;
        }
    }
    return tokens;
}

/// TEST

enum class NodeType{
    _return,
    punkt,
    strich,
    value
};

struct node{
    NodeType type;
    int val;

    //NodeType operation;
    node* left;
    node* right;
};

node* val_node(int val){
    node* n = new node;
    n->val=val;
    return n;
}

node* op_node(TokenType t, node* l, node* r){
    node* n = new node;


    if (t == TokenType::plus || t == TokenType::minus){
        n->type = NodeType::strich;
    }else{
        n->type = NodeType::punkt;
    }

    
    
    n->left=l;
    n->right=r;
    return n;
}

node* parse_term(){

}


// 1+2*3*4+5/6

int BP(TokenType t){
    switch (t)
    {
    case TokenType::plus:
    case TokenType::minus:
        return 10;
        break;
    
    case TokenType::mul:
    case TokenType::div:
        return 20;
        break;
    }
    return 0;
}


size_t pos = 0;


void parseTS(){

}


node* finalTree(std::vector<Token> tokens){
    const Token& toke = tokens[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }
    /////////
    node* left = val_node(std::stoi(tokens[1].value.value()));
    ///
    node* right = val_node(std::stoi(tokens[3].value.value()));

    node* op = op_node(tokens[2].type, left, right);
    node* lastNode = op;

    for (int i=4; i<tokens.size(); i++){
        if (BP(tokens[i].type)>15){
            left = right;
            right =  val_node(std::stoi(tokens[i+1].value.value()));

            node* ex = op_node(tokens[i].type, left, right);
            
            lastNode->right = ex;
            lastNode = ex;
            
            i++;
        }
        else{
            left = op;
            right = val_node(std::stoi(tokens[i+1].value.value()));
            node* ex = op_node(tokens[i].type, left, right);
            //lastNode->right = ex;
            lastNode = ex;
            op = ex;

            
            i++;
        }
    }


    

    return op;
}


/*
if (BP(tokens[4].type)>15){
        left = right;
        right =  val_node(std::stoi(tokens[5].value.value()));

        node* ex = op_node(tokens[2].type, left, right);
        
        op->right = ex;
    }
    else{
        left = op;
        right = val_node(std::stoi(tokens[5].value.value()));
        node* ex = op_node(tokens[2].type, left, right);
    }
*/


node* tree4(std::vector<Token> toks){
    const Token& toke = toks[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }
    for (int i=1; i<toks.size(); i++){
        const Token& token = toks[i];
        if (toks[i].type == TokenType::int_lit && toks[i+2].type != TokenType::int_lit){
            

            node* nT = val_node(std::stoi(toks[i].value.value()));



            //node* n =op_node(toks[i+2].type, )

            if (toks[i+2].type == TokenType::plus){
                

            }
        }
    }
}




















node* tree3(std::vector<Token> toks){
    const Token& toke = toks[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }

    if (toks[1].type == TokenType::int_lit && toks[1+2].type != TokenType::int_lit){
            

            node* nT = val_node(std::stoi(toks[1].value.value()));

            //node* n = op_node(toks[1+2].type, )

        }


    for (int i=3; i<toks.size(); i++){
        const Token& token = toks[i];
        if (toks[i].type == TokenType::int_lit && toks[i+2].type != TokenType::int_lit){
            

            if (i==1){
                node* nT = val_node(std::stoi(toks[1].value.value()));
            }



            //node* n =op_node(toks[i+2].type, )

            if (toks[i+2].type == TokenType::plus){
                

            }
        }
    }
}














node* tree2(std::vector<Token> toks){
    const Token& toke = toks[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }
    for (int i=1; i<toks.size(); i++){
        const Token& token = toks[i];
        if (toks[i].type == TokenType::int_lit && toks[i+2].type != TokenType::int_lit){
            

            node* nT = val_node(std::stoi(toks[i].value.value()));



            //node* n =op_node(toks[i+2].type, )

            if (toks[i+2].type == TokenType::plus){
                

            }
        }
    }
}






/////////////////
node* tree(std::vector<Token> toks){
    const Token& toke = toks[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }
    for (int i=1; i<toks.size(); i++){
        const Token& token = toks[i];
        if (toks[i].type == TokenType::int_lit && toks[i+1].type == TokenType::plus){
            node* n = new node;

            if (toks[i+2].type == TokenType::int_lit){
                node* nl = new node;
                node* nr = new node;
                
                n->type= NodeType::strich;
                n->left= nl;
                n->right= nr;
                nl->type = NodeType::value;
                nr->type = NodeType::value;
                nl->val= std::stoi(toks[i].value.value());
                nr->val= std::stoi(toks[i+2].value.value());

            }
        }
    }
}

///



std::vector<std::string> Tokens(const std::string& args) {
    std::vector<std::string> res;
    std::istringstream stream(args);

    std::string token;

    while (stream >> token) {
        res.push_back(token);
    }
    
    return res;
}



int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout << "no file specified" << std::endl;
    }
    //std::cout << argv[1] << std::endl;


    //read
    // Create a text string, which is used to output the text file
    std::string myText;

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
    }

    // Close the file
    MyReadFile.close();
    //std::cout << myText << std::endl;

    std::string input = "hello world this is C++";

    std::vector<std::string> result = Tokens(myText);
    

    for (const std::string& token : result) {
        std::cout << token << '\n';
    }

    {
        std::ofstream uh("lol.asm");
        uh << asmp(Tokenizer(myText));
        uh.close();
    }

    std::string filename = "lol.asm";
    
    // Construct the command string
    std::string command = "nasm -felf64 " + filename;

    std::system(command.c_str());

    std::system("ld -o out lol.o");

    return 0;
}