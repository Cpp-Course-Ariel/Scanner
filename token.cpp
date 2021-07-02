#include "token.h"
#include "tokenstrings.h"



using namespace std;


tokenType Token::getType(){
    return this->type;
}
string Token::getText(){
    return this->text;
    }
void Token::printToken(){
    if(this->type >=258){
    cout << tokenStrings[this->getType()-258] << "\t" << this->getText() << endl;
    }
    else {
        cout << this->getText() << "\t" << this->getText() << endl;
    }
}


// this is for the varToken    
void varToken::add_line(int l) {
    this->lines->insert(l);

}
shared_ptr<set<int>> varToken::getLines() {
    return this->lines;
}