#include <vector>
#include <string>
#include <indigo.hpp>
#include <iostream>

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
            } else
            if (buffer == "int"){
                tokens.push_back({.type = TokenType::var_int});
                buffer.clear();
            }
            else if (!dec) {
                tokens.push_back({
                    .type = TokenType::identifier,
                    .value = buffer
                });
                std::cout << static_cast<int>(TokenType::identifier) << " : " << buffer << std::endl;
                buffer.clear();
                //dec=1;
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
        else if (c == '='){
            if (tok.at(i+1) == '='){
                tokens.push_back({.type = TokenType::equal});
                i++;
            }else{
                tokens.push_back({.type = TokenType::asign});
            }
        }
        
        else if (std::isspace(c)){
            continue;
        }
    }
    return tokens;
}