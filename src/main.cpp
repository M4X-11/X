#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <optional>
#include <string>

#include <indigo.hpp>


std::string token_type_name(TokenType type) {
    switch (type) {
        case TokenType::memory:      return "memory";
        case TokenType::var_general: return "var";
        case TokenType::identifier:  return "identifier";
        case TokenType::_return:     return "return";
        case TokenType::int_lit:     return "int";
        case TokenType::semi:        return ";";
        case TokenType::plus:        return "+";
        case TokenType::minus:       return "-";
        case TokenType::mul:         return "*";
        case TokenType::div:         return "/";
        case TokenType::eckig_start: return "[";
        case TokenType::ecking_end:  return "]";
        case TokenType::less_than:   return "<";
        case TokenType::more_than:   return ">";
        case TokenType::root:        return "root";
        case TokenType::alias:       return "alias";
        case TokenType::declaration:       return "declaration";
        default:                     return "?";
    }
}

void print_tree(node* n, std::string prefix = "", bool last = true) {
    if (n == nullptr)
        return;

    // Print this node
    std::cout << prefix;

    if (last)
        std::cout << "└── ";
    else
        std::cout << "├── ";

    std::cout << token_type_name(n->type);

    // Print value if it has one
    if (!n->val.empty())
        std::cout << " (" << n->val << ")";

    std::cout << '\n';

    // Prefix used for children
    std::string child_prefix = prefix + (last ? "    " : "│   ");

    for (size_t i = 0; i < n->Npvec.size(); ++i) {
        print_tree(
            n->Npvec[i],
            child_prefix,
            i == n->Npvec.size() - 1
        );
    }
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
    buf << myText << " ";
    }
    std::cout << "\n";

    // Close the file
    
    
    //std::cout << myText << std::endl;

    
    

  

auto tokens = Tokenizer(buf.str());
//auto hm = Simple_tree(tokens, pos, 0);
auto hm = full_ast(tokens);

std::cout << "\nAST:\n";
print_tree(hm);

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
    
    //uh << generate(hm);
    uh << full_gen(hm);
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