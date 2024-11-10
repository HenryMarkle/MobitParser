#include <memory>
#include <string>
#include <vector>

#include <MobitParser/tokens.h>
#include <MobitParser/exceptions.h>

namespace mp {
    token::token(token_type type, const std::string&& value) : type(type), value(value) {}

    std::vector<token> tokenize(const std::string &str) {
        if (str.size() == 0) return {};

        std::vector<token> tokens;
    
        auto cursor = str.begin();

        do {

            switch (*cursor) {
                case ' ':
                case '\r':
                case '\n':
                case '\t':
                continue;

                case '[': tokens.push_back(token(token_type::open_bracket, "[")); break;
                case ']': tokens.push_back(token(token_type::close_bracket, "]")); break;

                case '(': tokens.push_back(token(token_type::open_paren, "(")); break;
                case ')': tokens.push_back(token(token_type::close_paren, ")")); break;
                
                case ',': tokens.push_back(token(token_type::comma, ",")); break;
                case ':': tokens.push_back(token(token_type::comma, ":")); break;

                case '#':
                {
                    std::string symbol;

                    auto peek = cursor + 1;

                    while (peek < str.end() && isalnum(*peek)) {
                        symbol.push_back(*peek);
                        peek++;
                    }

                    tokens.push_back(token(token_type::symbol, std::move(symbol)));
                    cursor = peek - 1;
                }
                break;

                case '"':
                {
                    std::string _str;

                    auto peek = cursor + 1;

                    while (peek != str.end() && *peek != '"') {
                        _str.push_back(*peek);
                    }

                    tokens.push_back(token(token_type::string, std::move(_str)));
                    cursor = peek;
                }
                break;

                case '&':
                {
                    auto peek = cursor + 1;

                    if (peek != str.end() && *peek == '&') {
                        cursor++;

                        tokens.push_back(token(token_type::space_concat, "&&"));
                    } else {
                        tokens.push_back(token(token_type::concat, "&"));
                    }
                }
                break;

                case '-': tokens.push_back(token(token_type::subtract, "-")); break;
                case '+': tokens.push_back(token(token_type::add, "+")); break;
                case '*': tokens.push_back(token(token_type::multiply, "*")); break;
                case '/': tokens.push_back(token(token_type::divide, "/")); break;

                case 'n':
                {
                    auto peek = cursor;

                    if (++peek == str.end() && *peek != 'o') break;
                    if (++peek == str.end() && *peek != 't') break;

                    tokens.push_back(token(token_type::negate, "not"));
                    cursor = peek;
                }
                break;

                case 'a':
                {
                    auto peek = cursor;

                    if (++peek == str.end() && *peek != 'n') break;
                    if (++peek == str.end() && *peek != 'd') break;

                    tokens.push_back(token(token_type::and_, "and"));
                    cursor = peek;
                }
                break;

                case 'o':
                {
                    auto peek = cursor;

                    if (++peek == str.end() && *peek != 'r') break;

                    tokens.push_back(token(token_type::or_, "or"));
                    cursor = peek;
                }
                break;

                case 'v':
                {
                    auto peek = cursor;

                    if (++peek == str.end() && *peek != 'o') break;
                    if (++peek == str.end() && *peek != 'i') break;
                    if (++peek == str.end() && *peek != 'd') break;

                    tokens.push_back(token(token_type::void_val, "void"));
                    cursor = peek;
                }
                break;

                // identifier
                default:
                {
                    auto peek = cursor + 1;
                    std::string iden;

                    while (peek != str.end() && isalnum(*peek)) {
                        iden.push_back(*peek);
                    }

                    tokens.push_back(token(token_type::identifier, std::move(iden)));
                    cursor = peek - 1;
                }
                break;
            }

            cursor++;

        } while (cursor != str.end());
    
        return tokens;
    };
};
