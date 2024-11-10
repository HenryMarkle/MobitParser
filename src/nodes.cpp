#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <MobitParser/tokens.h>
#include <MobitParser/nodes.h>

namespace mp {
    Int::Int(int number) : number(number) {}
    Float::Float(float number) : number(number) {}
    String::String(std::string&& str_) : str(std::move(str_)) {}
    Symbol::Symbol(std::string&& str_) : str(std::move(str_)) {}
    BinOp::BinOp(
        binary_operation op_, 
        std::unique_ptr<Node>&& left_, 
        std::unique_ptr<Node>&& right_) : op(op_), left(std::move(left_)), right(std::move(right_)) {}
    UnOp::UnOp(
        unary_operation op_, 
        std::unique_ptr<Node>&& operand_) : op(op_), operand(std::move(operand_)) {}
    List::List(std::vector<std::unique_ptr<Node>>&& elements_) : elements(std::move(elements_)) {}
    Props::Props(std::unordered_map<std::string, std::unique_ptr<Node>>&& map_) : map(std::move(map_)) {}
    GCall::GCall(std::string&& name_, std::vector<std::unique_ptr<Node>>&& args_) : name(std::move(name_)), args(std::move(args_)) {}

    std::ostream& operator<<(std::ostream& stream, const Node* node) {
        if (const auto *integer = dynamic_cast<const Int*>(node)) {
            stream << integer->number;
        } else if (const auto *floating = dynamic_cast<const Float*>(node)) {
            stream << floating->number;
        } else if (const auto *string = dynamic_cast<const String*>(node)) {
            stream << string->str;
        } else if (const auto *symbol = dynamic_cast<const Symbol*>(node)) {
            stream << symbol->str;
        } else if (const auto *bin_op = dynamic_cast<const BinOp*>(node)) {
            stream << bin_op->left.get() << ' ' << bin_op->op << ' ' << bin_op->right.get();
        } else if (const auto *un_op = dynamic_cast<const UnOp*>(node)) {
            stream << un_op->op << un_op->operand.get();
        } else if (const auto *list = dynamic_cast<const List*>(node)) {
            stream << '[';

            for (int i = 0; i < list->elements.size(); i++) {
                stream << list->elements[i].get();

                if (i != list->elements.size() - 1) stream << ", ";
            }

            stream << ']';
        }else if (const auto *props = dynamic_cast<const Props*>(node)) {
            stream << '[';

            for (auto i = props->map.begin(); i != props->map.end(); i++) {
                stream << '#' << i->first << ": " << i->second.get();
                stream << ",";
            }

            stream << ']';
        } else if (const auto *gcall = dynamic_cast<const GCall*>(node)) {
            stream << gcall->name << '(';

            for (int i = 0; i < gcall->args.size(); i++) {
                stream << gcall->args[i].get();

                if (i != gcall->args.size() - 1) stream << ", ";
            }

            stream << ')';
        } 
    }

    /// TODO: complete this
    /// @brief Constructs an abstract syntax tree from the expression string.
    /// @param str The string of the expression,
    /// @return nullptr if the string is empty; otherwise a pointer to the abstract syntax tree. 
    std::unique_ptr<Node> parse(const std::string &str) {
        if (str.empty()) return nullptr;

        auto tokens = tokenize(str);

        if (tokens.empty()) return nullptr;

        std::unique_ptr<Node> expr = nullptr;

        auto begin = tokens.begin();
        auto end = tokens.end();

        auto cursor = begin;

        switch (cursor->type) {
            // Unary operators

            case token_type::add: {

            }
            break;

            case token_type::subtract: {

            }
            break;

            case token_type::negate: {

            };


        }

        return expr;
    }
};
