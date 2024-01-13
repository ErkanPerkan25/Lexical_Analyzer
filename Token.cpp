/*******************************************
 * File: Token.cpp                         *
 * Author: S. Blythe                       *
 * Date: 12/2023                           *
 * PURPOSE: implementation for Token       *
 *******************************************/

#include "Token.hpp"

#include <fstream>
#include <iomanip>

using namespace std;

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
static int **DFA = nullptr;

void Token::get(istream &is)
{
  // you must write this code !!!!
    if (!DFA) { // if dfa tabel doesn't exist ... create one
        DFA = new int*[END+1]; // Create the rows, which are the different states 
        for (int state=ERROR; state<=END; state++) {
            DFA[state] = new int[256]; // creates the columns, which are the characters
            for (int ch=0; ch<256; ch++) {
                DFA[state][ch] = ERROR; // initializes all the cells with error
            }
        }

        // all the transitions from start state (ERROR or 0)        
        for (char ch='0'; ch<'9'; ch++)
            DFA[ERROR][int (ch)] = NUM_INT;

        DFA[ERROR][(int) '.'] = NUM_REAL;
        DFA[ERROR][(int) '+'] = ADDOP;
        DFA[ERROR][(int) '-'] = ADDOP;

        DFA[ERROR][(int) '*'] = MULOP;
        DFA[ERROR][(int) '/'] = MULOP;
        // need to think with <, >, and <=, >=
        DFA[ERROR][(int) '<'] = RELOP;
        DFA[ERROR][(int) '>'] = RELOP;

        DFA[ERROR][(int) '='] = ASSIGNOP;

        DFA[ERROR][(int) '('] = LPAREN;
        DFA[ERROR][(int) ')'] = RPAREN;
        DFA[ERROR][(int) '['] = LBRACK;
        DFA[ERROR][(int) ']'] = RBRACK;

        // "&&" = '&' + '&'
        DFA[ERROR][(int) '&'] = AND;

        DFA[ERROR][(int) ','] = COMMA;
        DFA[ERROR][(int) ';'] = SEMICOLON;

        
    }

    // fill _value from input file and _type as token type
    _value ="";
    char ch;

    // skip white spacing here


    int curr=ERROR;
    int prev=EOF_TOK;

    while (curr!=ERROR) {
        // get next character from input file
        ch = is.get();
        
        // move to the next state based on character read
    }
}
