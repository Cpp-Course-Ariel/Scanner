#include "scanner.h"
#include <regex.h>
#include <stdio.h>


bool isValidNumber(string num){
    int counterE = 0;
    int counterDot = 0;
    for( auto i = num.begin(); i!= num.end(); i++){
        if( *i == 'e' || *i == 'E'){
            counterE++;
        }
        if (*i == '.'){
            counterDot++;
        }
    }
    if(counterDot == 2 || counterE ==2)
        return false;
    else
        return true;
}

int i = 0;

shared_ptr<Token> Scanner::nextToken(){
 if(i ==0){
     this->nextChar();
     i++;
 }
char prev;

do{
    switch (this->ch) {

        case ' ' : case '\n' : case '\r' :case '\t':{
            break;
        }
        
    // each character represents itself
        case ';' : case '{' : case '}' : case ',' : case ':' : \
        case '(' : case ')' : case '[' : case ']' : case '~' : \
        case '*' : case '%' : case '^' : case '?' : case '/': case '=':{
            //check if the prev was ( or {
            if(this->ch == ')' && prev == '(' || this->ch == '}' && prev == '{' ){
                shared_ptr<Token> (new Token(static_cast<tokenType>(prev),string(1,prev)))->printToken();
                return shared_ptr<Token> (new Token(static_cast<tokenType>(this->ch),string(1,this->ch)));
                break;
        }
            //check comments
            if(this->ch == '/'){
                if(this->nextChar()){
                    if(this->ch == '*'){
                        while(this->ch != '/'){
                            this->nextChar();
                        }
                    break;
                    }
                    else if(this->ch == '/'){
                        while(this->ch != '\n'){
                            this->nextChar();
                        }
                    break;
                    }
                }
            }
            char prev = this->ch;
            this->nextChar();
            return shared_ptr<Token> (new Token(static_cast<tokenType>(prev),string(1,prev)));
            break;
        }

        case '.':{
            regex e("[0-9]+[.]?[0-9]*[Ee]?");
            string token = string(1,this->ch);
            if(this->nextChar())
                if(isdigit(this->ch)){
                     token = token+this->ch;
                     while(this->nextChar() && !std::isspace(ch) && ( isdigit(this->ch) || this->ch == '.' || this->ch =='e' || this->ch == 'E' ) ){
                        token = token+this->ch;
                }
                if(isValidNumber(token)){
                    symTab.insertToken(token,shared_ptr<Token> (new Token(tokenType::CONSTANT,token)));
                    return shared_ptr<Token> (new Token(tokenType::CONSTANT,token));
                    break;
                }else{
                    return shared_ptr<Token> (new Token(tokenType::ERROR,token));
                    break;
                }

                }else{
                    return shared_ptr<Token> (new Token(static_cast<tokenType>(token[0]),string(1,token[0])));
                    break;
                }
        }


        case '-':{
            
                //ptr_op ->
                this->nextChar();
                if(this->ch == '>'){
                    this->nextChar();
                    return shared_ptr<Token> (new Token(tokenType::PTR_OP,"->"));
                    break;
                }else if(this->ch == '-'){
                    this->nextChar();
                    return shared_ptr<Token> (new Token(tokenType::DEC_OP,"--"));
                    break;
                }else{
                    return shared_ptr<Token> (new Token(static_cast<tokenType>('-'),string(1,'-')));
                    break;
                }
        }

        case '+':{
                if(this->nextChar()){
                    if(this->ch == '+'){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::INC_OP,"++"));
                        break;
                    }else{
                        return shared_ptr<Token> (new Token(static_cast<tokenType>('+'),string(1,'+')));
                        break;
                    }
                }
        }


        case '&':{
                if(this->nextChar()){
                    if(this->ch == '&'){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::AND_OP,"&&"));
                        break;
                    }else{
                        return shared_ptr<Token> (new Token(static_cast<tokenType>('&'),string(1,'&')));
                        break;
                    }
                }
        }

        case '|':{
                if(this->nextChar()){
                    if(this->ch == '|'){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::OR_OP,"||"));
                        break;
                    }
                }
        }   

        case '<':{
                if(this->nextChar()){
                    if(this->ch == '='){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::LE_OP,"<="));
                        break;
                    }else{
                         return shared_ptr<Token> (new Token(static_cast<tokenType>('<'),string(1,'<')));
                        break;
                    }
                }
        }

        case '>':{
                if(this->nextChar()){
                    if(this->ch == '='){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::GE_OP,">="));
                        break;
                    }else{
                         return shared_ptr<Token> (new Token(static_cast<tokenType>('>'),string(1,'>')));
                        break;
                    }
                }
        }

        case '!':{
                if(this->nextChar()){
                    if(this->ch == '='){
                        this->nextChar();
                        return shared_ptr<Token> (new Token(tokenType::NE_OP,"!="));
                        break;
                    }else{
                        return shared_ptr<Token> (new Token(static_cast<tokenType>('!'),string(1,'!')));
                        break;
                    }
                }
        }

        // char case
        case '\'':{
            this->nextChar();
            char nextchar = this->ch;
            this->nextChar();
            if(this->ch == '\''){
                this->nextChar();
                return shared_ptr<Token> (new Token(tokenType::CONSTANT, string(1,nextchar)));
                break;
            }else{
                this->nextChar();
                throw ERROR;
            }
        }

        //string case
        case '\"':{
            string token = "";
            this->nextChar();
            while (this->ch != '\"'){
                token = token + this->ch;
                this->nextChar();
            }
            this->nextChar();
            return shared_ptr<Token> (new Token(tokenType::STRING_LITERAL,token));
            break;
        }

        default:{

            //check if digit
            if(isdigit(ch)){
                regex e("[0-9]+[.]?[0-9]*[Ee]?");
                string token = ""+string(1,this->ch);
                while(this->nextChar() && !std::isspace(ch) && ( isdigit(this->ch) || this->ch == '.' || this->ch =='e' || this->ch == 'E' ) ){
                    token = token+this->ch;
                }
                if(isValidNumber(token)){
                    symTab.insertToken(token,shared_ptr<Token> (new Token(tokenType::CONSTANT,token)));
                    return shared_ptr<Token> (new Token(tokenType::CONSTANT,token));
                    break;
                }else{
                    return shared_ptr<Token> (new Token(tokenType::ERROR,token));
                    break;
                }
            }
            //check if string
            string tokenTmp;
            tokenTmp.push_back(this->ch);
            while(this->nextChar() && (!ispunct(this->ch) || this->ch =='_') && !isspace(this->ch)){
                tokenTmp.push_back(this->ch);
                
            }
            prev = this->ch;
            //check if the token exists in the symtable
            if (this->symTab.lookupToken(tokenTmp) == nullptr){
                shared_ptr<varToken>T (new varToken(tokenTmp));
                symTab.insertToken(tokenTmp,T);
                T->add_line(this->lineno);
                return T;//if not exists create a var token and return its shared_ptr
                break;
            }else if(this->symTab.lookupToken(tokenTmp)->getType() == tokenType::IDENTIFIER){
                this->symTab.lookupToken(tokenTmp)->add_line(this->lineno);
                return (this->symTab.lookupToken(tokenTmp));//if exists return symtab token
                break;    
            }
            return (this->symTab.lookupToken(tokenTmp));//if exists return symtab token
            break;
        }
    }
    }while (this->nextChar()); 

}