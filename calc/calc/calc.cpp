// calc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define MUL "MUL"
#define DIV "DIV"

class Token {

public:
    char value;
    std::string type;
    Token(std::string t, char v) {
        type = t;
        value = v;
    }
    friend std::ostream& operator<< (std::ostream& out, const Token& token);

};

std::ostream& operator<< (std::ostream& out, const Token& token)
{
    out << "Token type: " << token.type << "\n" << "Token value: " << token.value << "\n";
    return out;
}

class Interpreter {

private:
    int position;
    Token* curr_token;
    std::string script;
    char curr_character;

public:
    Interpreter(std::string scr) {
        position = 0;
        script = scr;
        curr_character = script[position];
        curr_token = next_token();
    };

    void error() {
        std::cout << "Error parsing input" << "\n";
        throw;
    }

    void skip_whitespace() {
        while(curr_character != NULL && curr_character == ' ')
            advance();
    }

    void advance() {
        position++;
        if (position > script.size() - 1) {
            curr_character = NULL;
        }
        else {
             curr_character = script[position];
        }
    }

    int integer() {
        std::string number = "";
        while (curr_character != NULL && isdigit(curr_character)) {
            number.push_back(curr_character);
            advance();
        }
        return to_integer(number);
    }

    int to_integer(std::string number) {
        int result = 0;
        for (int i = 0; i < number.size(); i++) {
            result += (int(number[i]) - 48) * std::pow(10, number.size() - 1 - i);
        }
        return result;
    }

    Token* next_token() {
        while (curr_character != NULL) {
            
            skip_whitespace();

            if (curr_character == '+') {
                Token* token = new Token(PLUS, curr_character);
                advance();
                return token;
            }
            if (curr_character == '-') {
                Token* token = new Token(MINUS, curr_character);
                advance();
                return token;
            }
            if (std::isdigit(curr_character)) {
                Token* token = new Token(INTEGER, integer());

                return token;
            }
            if (curr_character == '/') {
                Token* token = new Token(DIV, curr_character);
                advance();
                return token;
            }
            if (curr_character == '*') {
                Token* token = new Token(MUL, curr_character);
                advance();
                return token;
            }

            error();
        }
        return nullptr;
    }

    int factor() {
        int val = curr_token->value;
        process(INTEGER);
        return val;
    }

    int term() {

        int result = factor();

        while (curr_token && (curr_token->type == DIV || curr_token->type == MUL)) {
            if (curr_token->type == DIV) {
                process(DIV);
                result /= factor();
            }
            else if (curr_token->type == MUL) {
                process(MUL);
                result *= factor();
            }
        }
        return result;
    }

    void process(std::string expected_type) {
        if (curr_token->type == expected_type) {
            curr_token = next_token();
        }
        else {
            error();
        }
    }

    int calc() {

        int result = term();

        while (curr_token && (curr_token->type == PLUS || curr_token->type == MINUS)) {
            if (curr_token->type == PLUS) {
                process(PLUS);
                result += term();
            }
            else if (curr_token->type == MINUS) {
                process(MINUS);
                result -= term();
            }
        }
        return result;
    }

};

int main() {
    std::string input;
    std::getline(std::cin, input);;
    Interpreter interpreter(input);
    std::cout << interpreter.calc();
    return 0;

}
