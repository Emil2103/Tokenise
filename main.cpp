#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1.Токенезация
// 2.Парсер (построение дерева разбора выражения)

struct OpeningBracket{
};

struct ClosingBracket{
};

struct Number{
    int value;
};

struct UnknownToken{
    std::string value;
};

struct MinToken{
};

struct AbsToken{
};

struct Plus{};

struct Minus{};

struct Multiply{};

struct Modulo{};

struct Divide {};

struct MaxToken {};

struct SqrToken {};

using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken,
            Plus, Minus, Multiply, Modulo, Divide, MaxToken, SqrToken>;

const std::unordered_map<unsigned char, Token> kSymbol2Token{
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'(', OpeningBracket{}}, {')', ClosingBracket{}}};

int ToDigit(unsigned char symbol){
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos){
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while(std::isdigit(symbol)){
        value = value * 10 + ToDigit(symbol);
        if(pos == input.size()){
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
}

Token ParseName(const std::string& input, size_t& pos){
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while(std::isalpha(symbol)){
        name += symbol;
        if(pos == input.size()){
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    
    if (name == "min") {
        return MinToken{};
    } else if (name == "abs") {
        return AbsToken{};
    } else if (name == "max") {
        return MaxToken{};
    } else if (name == "sqr") {
        return SqrToken{};
    } else {
        return UnknownToken{name};
    }
}

std::vector<Token> Tokenize(const std::string& input){
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while(pos < size){
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if(std::isspace(symbol)){
            ++pos;
        }else if(std::isdigit(symbol)){
            tokens.emplace_back(ParseNumber(input, pos));
            
        }else if(auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()){
            tokens.emplace_back(it->second);
            ++pos;
        }else if(std::isalpha(symbol)){
            tokens.emplace_back(ParseName(input, pos));
            
        }
    }
    return tokens;
}

int main(){
    std::string expression = "1 + 2 * 3 - (2 + sqr(4)) + 10 q";
    auto tokens = Tokenize(expression);

    // Выводим токены
    for (const auto& token : tokens) {
        if (std::holds_alternative<Number>(token)) {
            std::cout << "Number: " << std::get<Number>(token).value << std::endl;
        } else if (std::holds_alternative<Plus>(token)) {
            std::cout << "Plus" << std::endl;
        } else if (std::holds_alternative<Minus>(token)) {
            std::cout << "Minus" << std::endl;
        } else if (std::holds_alternative<Multiply>(token)) {
            std::cout << "Multiply" << std::endl;
        } else if (std::holds_alternative<Divide>(token)) {
            std::cout << "Divide" << std::endl;
        } else if (std::holds_alternative<Modulo>(token)) {
            std::cout << "Modulo" << std::endl;
        } else if (std::holds_alternative<OpeningBracket>(token)) {
            std::cout << "OpeningBracket" << std::endl;
        } else if (std::holds_alternative<ClosingBracket>(token)) {
            std::cout << "ClosingBracket" << std::endl;
        } else if (std::holds_alternative<UnknownToken>(token)) {
            std::cout << "UnknownToken: " << std::get<UnknownToken>(token).value << std::endl;
        } else if (std::holds_alternative<MinToken>(token)) {
            std::cout << "MinToken" << std::endl;
        } else if (std::holds_alternative<AbsToken>(token)) {
            std::cout << "AbsToken" << std::endl;
        } else if (std::holds_alternative<MaxToken>(token)) {
            std::cout << "MaxToken" << std::endl;
        } else if (std::holds_alternative<SqrToken>(token)) {
            std::cout << "SqrToken" << std::endl;
        }
    }

    return 0;
}
