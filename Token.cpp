/*******************************************
 * File: Token.cpp                         *
 * Author: S. Blythe                       *
 * Date: 12/2023                           *
 * PURPOSE: implementation for Token       *
 *******************************************/

#include "Token.hpp"

#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

static int **DFA=nullptr;
#define ERROR -1
#define NONE 0

// the promised global for string equivalents of TokenType enumeration
string TokStr[]=
{ "ERROR", "EOF_TOK", "NUM_INT", "NUM_REAL", "ADDOP", "MULOP", "ID", "RELOP", "ASSIGNOP", "LPAREN", "RPAREN",  "SEMICOLON",  "LBRACK", "RBRACK", "COMMA", "AND", "OR", "INTEGER", "FLOAT", "WHILE", "IF", "THEN", "ELSE", "VOID", "BEGIN", "END"};

// This is a "list" of the keywords. Note that they are in the same order
//   as found in the TokenType enumaration. 
static string reserved[]={"int" , "float", "while", "if", "then", "else", "void", "begin", "end" };



/******************************************************
 *  just prints out the info describing this Token    *
 *    to specified stream                             *
 *                                                    *
 *   os  - the stream to add the Token to             *
 *                                                    *
 *   returns: the updated stream                      *
 ******************************************************/
ostream&
Token::print(ostream& os) const
{
  os
     << "{ Type:"   << left << setw(10) << TokStr[_type] 
     << " Value:"   << left << setw(10) << _value
     << " Line Number:" << _line_num
     << " }";
  return os;
}

/******************************************************
 *  Fills in information about this Token by reading  *
 *    it from specified input stream                  *
 *                                                    *
 *   is  - the stream to read the Token from          *
 *                                                    *
 *   returns: nothing                                 *
 *                                                    *
 *     **** YOU MUST CODE THIS !!!!!! ****            *
 ******************************************************/
// Deterministic ... 2D-array 

void Token::get(istream &is)
{
  // you must write this code !!!!
    if (!DFA) { // if dfa tabel doesn't exist ... create one
        DFA = new int*[END+1]; // Create the rows, which are the different states 
        for (int state=NONE; state<=END; state++) {
            DFA[state] = new int[256]; // creates the columns, which are the characters
            for (int ch=0; ch<256; ch++) {
                DFA[state][ch] = ERROR; // initializes all the cells with error
            }
        }

        // all the transitions from start state (NONE or 0)        
        for (char ch='0'; ch<'9'; ch++)
            DFA[NONE][(int) ch] = NUM_INT;

        for (char ch='a'; ch<'z'; ch++)
            DFA[NONE][(int) ch] = ID;

        for (char ch='A'; ch<'Z'; ch++)
            DFA[NONE][(int) ch] = ID;
        
        DFA[NONE][(int) '.'] = NUM_REAL;
        DFA[NONE][(int) '+'] = ADDOP;
        DFA[NONE][(int) '-'] = ADDOP;
    
         
        DFA[NONE][(int) '*'] = MULOP;
        DFA[NONE][(int) '/'] = MULOP;
       
        /*
        // need to think with <, >, and <=, >=
        DFA[ERROR][(int) '<'] = RELOP;
        DFA[ERROR][(int) '>'] = RELOP;

        // one '=' goes to state 9, which is a final state but can keep going
        // if next ch is another '=', then go to state 8
        DFA[NONE][(int) '='] = ASSIGNOP;
        */ 
        // States for parentases and brackets
        DFA[NONE][(int) '('] = LPAREN;
        DFA[NONE][(int) ')'] = RPAREN;
        DFA[NONE][(int) '['] = LBRACK;
        DFA[NONE][(int) ']'] = RBRACK;
        
        // one '&' goes to state 12, which only then leads to 13 which is "&&" = '&' + '&'
        //DFA[ERROR][(int) '&'] = AND;

        DFA[NONE][(int) ','] = COMMA;
        DFA[NONE][(int) ';'] = SEMICOLON;

        for (char ch='a'; ch<'z'; ch++)
            DFA[ID][(int) ch] = ID;

        for (char ch='A'; ch<'Z'; ch++)
            DFA[ID][(int) ch] = ID;

        for (char ch='1'; ch<'9'; ch++)
            DFA[ID][(int) ch] = ID;

        // all transitions from NUM_INT state (NUM_INT or 1)
        for(char ch='0'; ch<'9'; ch++)
            DFA[NUM_INT][(int) ch] = NUM_INT; 

        for(char ch='0'; ch<'9'; ch++)
            DFA[NUM_REAL][(int) ch] = NUM_REAL;
    }

    // fill _value from input file and _type as token type
    _value ="";
    char ch;

    // skip white spacing here
    ch = is.get();
    while (isspace(ch)) {
        if(ch=='\n') // increments the number if line when there is also a blank line
            _line_num++;
        
        ch = is.get();
    }
    //if(!is)
    is.putback(ch);

    int curr=NONE;
    int prev=ERROR;

    while (curr!=ERROR) {
        // get next character from input file
        ch = is.get();
        
        // move to the next state based on character read
        prev = curr;
        curr = DFA[curr][(int) ch];

        if (curr!=ERROR) { // if the character is a valid part of the token ... 
            _value+=ch;    // ... add char to lexeme's value
        }
    }

    _type = (TokenType) prev;
    
    // We read one more extra character ... put it back for the next get()
    if (is)
        is.putback(ch);
}
