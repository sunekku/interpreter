// calc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define INTEGER "INTEGER"
#define PLUS "PLUS"
#define EOF "EOF"
#define MINUS "MINUS"

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
        curr_token = nullptr;
        script = scr;
        curr_character = script[position];
    }

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
            result += int((number[i]) - 48) * std::pow(10, number.size() - 1 - i);
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
            error();
        }
        return nullptr;
    };

    void process(Token** token, std::string expected_type) {
        if ((*token)->type == expected_type) {
            *token = next_token();
        }
        else {
            error();
        }
    }

    int calc() {
        curr_token = next_token();

        Token* left_side = curr_token;
        process(&curr_token, INTEGER);
        
        Token* op = curr_token;
        if (op -> type == PLUS) {
            process(&curr_token, PLUS);
        }
        else {
            process(&curr_token, MINUS);
        }

        Token* right_side = curr_token;
        process(&curr_token, INTEGER);

        if (op->type == PLUS) {
            return left_side->value + right_side->value;
        }
        else {
            return left_side->value - right_side->value;
        }
    }

};

int main() {
    std::string input;
    std::cin >> input;
    Interpreter interpreter(input);
    std::cout << interpreter.calc();
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
