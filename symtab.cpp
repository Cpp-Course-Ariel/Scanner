#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include <regex>
using namespace std;

void SymbolTable::initReserved(){
    regex rgx("\\s");
    string line = "";
    ifstream reserved;
    reserved.open("reserved.txt");
    while( getline(reserved,line,'\n')){
        if(!line.empty()){
            vector<string> tokens(sregex_token_iterator(line.begin(), line.end(), rgx, -1),sregex_token_iterator());
            switch (stoi(tokens[1])){
            case 261:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::SIZEOF,tokens[0]))));
                break;
            case 287:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::AUTO,tokens[0]))));
                break;
            case 314:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::BREAK,tokens[0]))));
                break;
            case 304:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::CASE,tokens[0]))));
                break;
            case 289:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::CHAR,tokens[0]))));
                break;
            case 297:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::CONST,tokens[0]))));
                break;
            case 313:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::CONTINUE,tokens[0]))));
                break;
            case 305:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::DEFAULT,tokens[0]))));
                break;
            case 310:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::DO,tokens[0]))));
                break;
            case 296:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::DOUBLE,tokens[0]))));
                break;
            case 307:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::ELSE,tokens[0]))));
                break;
            case 302:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::ENUM,tokens[0]))));
                break;
            case 285:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::EXTERN,tokens[0]))));
                break;
            case 295:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::FLOAT,tokens[0]))));
                break;
            case 311:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::FOR,tokens[0]))));
                break;
            case 312:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::GOTO,tokens[0]))));
                break;
            case 306:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::IF,tokens[0]))));
                break;
            case 291:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::INT,tokens[0]))));
                break;
            case 292:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::LONG,tokens[0]))));
                break;
            case 288:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::REGISTER,tokens[0]))));
                break;
            case 315:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::RETURN,tokens[0]))));
                break;
            case 290:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::SHORT,tokens[0]))));
                break;
            case 293:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::SIGNED,tokens[0]))));
                break;
            case 286:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::STATIC,tokens[0]))));
                break;
            case 300:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::STRUCT,tokens[0]))));
                break;
            case 308:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::SWITCH,tokens[0]))));
                break;
            case 284:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::TYPEDEF,tokens[0]))));
                break;
            case 301:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::UNION,tokens[0]))));
                break;
            case 294:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::UNSIGNED,tokens[0]))));
                break;
            case 299:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::VOID,tokens[0]))));
                break;
            case 298:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::VOLATILE,tokens[0]))));
                break;
            case 309:
                this->symMap.insert(pair<string,shared_ptr<Token>>(tokens[0], shared_ptr<Token>(new Token(tokenType::WHILE,tokens[0]))));
                break;
            
            default:
                break;
        }//switch
        }
    } 
}

shared_ptr<Token> SymbolTable::lookupToken(string text){
    
    for (auto itr = this->symMap.find(text); itr != this->symMap.end(); itr++) {   
        return itr->second;//return the second object from the map of symbols
    }
    return nullptr;//if nothing found
}

/**
 * enter new tokens to the map
 * */

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp){

    this->symMap.insert(pair<string,shared_ptr<Token>>(text, tokenp));//enter thr token to the map
}


/**
 * print all the non-ENUM that add to the map, IIDENTIFIER and CONSTANT
 **/
void SymbolTable::xref(){
    
    for (auto it = this->symMap.begin(); it != this->symMap.end(); ++it){
        if (it->second->getType() == tokenType::IDENTIFIER ){
                cout << it->second->getText() << "\t";
            for(auto numLines= it->second->getLines()->begin(); numLines != it->second->getLines()->end() ; numLines++){
                cout << *numLines<< " ";
            
            }
            cout << endl;
        }
        
    }
}