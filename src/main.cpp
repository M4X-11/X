#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <optional>

enum class TokenType {
    _return,
    int_lit,
    semi
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

    int operation;
    node* left;
    node* right;
};

node* tree(std::vector<Token> toks){
    const Token& toke = toks[0];
    if (toke.type != TokenType::_return){
            std::cout << "error: no return" << std::endl;
            return NULL;
        }
    for (int i=1; i<toks.size(); i++){
        const Token& token = toks[i];
        if (toks[i].type == TokenType::int_lit && toks[i+1].type == TokenType::int_lit){
            
        }
    }
    return NULL;
}

///



std::vector<std::string> tokens(const std::string& args) {
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
    
    
    //std::cout << myText << std::endl;

    std::string input = "hello world this is C++";

    std::vector<std::string> result = tokens(myText);
    

    for (const std::string& token : result) {
        std::cout << token << '\n';
    }
std::cout << "myText = [" << myText << "]\n";

auto tokens = Tokenizer(myText);

std::cout << "tokens = " << tokens.size() << '\n';

{
    std::ofstream uh("lol.asm");
    uh << asmp(tokens);
}
    MyReadFile.close();
    std::string filename = "lol.asm";
    
    // Construct the command string
    std::string command = "nasm -felf64 " + filename;

    std::system(command.c_str());

    std::system("ld -o out lol.o");

    return 0;
}