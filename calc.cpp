#include <iostream>
#include <string>
#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define EOF "EOF"

class Token {

    public:
    char value;
    std::string type;
    Token(std::string t, char v){
        type = t;
        value = v;
    }
    friend std::ostream& operator<< (std::ostream &out, const Token &token);

};

std::ostream& operator<< (std::ostream &out, const Token &token)
{
        out << "Token type: " << token.type << "\n" << "Token value: " << token.value << "\n";
        return out;
    }

class Interpreter {

    private:
    int position;
    Token *curr_token;
    std::string script;

    public:
    Interpreter(std::string scr){
        position = 0;
        curr_token = nullptr;
        script = scr;
    }

    void error(){
        std::cout << "Error parsing input" << "\n";
    }

    Token *next_token(){

        std::string input = script;
        if(position > input.size() - 1){
            Token token(EOF, NULL);
            return &token;
        }

        char character = input[position];

        if(character == '+'){
            Token token(PLUS, character);
            position++;
            return &token;
        }
        if(std::isdigit){
            Token token(INTEGER, character);
            position++;
            return &token;
        }
        error();
        return nullptr;
    };

    int process(Token **token, std::string expected_type){
        if((*token) -> type == expected_type){
            *token = next_token();
            return 1;
        }
        else{
            error();
            return 0;
        }
    }

    int calc(){
        curr_token = next_token();
        Token *left_side = curr_token;
        if(!process(&curr_token, INTEGER)){
            return NULL;
        }
        Token *op = curr_token;
        if(!process(&curr_token, PLUS)){
            return NULL;
        }
        Token *right_side = curr_token;
        if(!process(&curr_token, INTEGER)){
            return NULL;
        }

        if(!process(&curr_token, EOF)){
            return NULL;
        }

        return int(right_side -> value) + int(left_side -> value);

    }

};

int main(){
    std::string input;
    std::cin >> input;
    Interpreter interpreter(input);
    std::cout << interpreter.calc();
    return 0;

}
