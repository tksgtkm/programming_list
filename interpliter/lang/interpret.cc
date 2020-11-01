
#include "source.h"
#include "gettoken.h"
#include "interpret.h"
#include "util.h"

using namespace std;

map <string, double> varmap;

static Token checkAndRegisterVar(Token token0) {
  string symbol = token0.getSymbol();
  map <string, double>::iterator itr;
  itr = varmap.find(symbol);
  double v = 0.0;
  if (itr == varmap.end()) {
    varmap[symbol] = v;
  }  else {
    v = itr->second;
  }
  return (Token(Value, symbol, v));
}

Token expression(vector < Token > tknList) {
  stack < Token > exstck;
  stack < Token > exopstck;

  while(true) {
    if (DispStack) {
      printstack(exstck, "exstck");
      printstack(exopstck, "exopstck");
    }
    if (DispToken)
      dispTokenList(tknList, "tknList");

    Token currentToken = getNextToken(tknList);
    TokenType ctt = currentToken.getType();
    string csm = currentToken.getSymbol();
    if (ctt == Symbol && csm[0] == '-') {
      string tmpsymbol = csm.substr(1, csm.length()-1);
      Token tmpToken = Token(Symbol, tmpsymbol, Top);
      tmpToken = checkAndRegisterVar(tmpToken);
      double v = tmpToken.getValue();
      currentToken = Token(-1*v);
      ctt = Value;
    }

    if (ctt == Symbol) {
      currentToken = checkAndRegisterVar(currentToken);
      ctt = currentToken.getType();
    }

    if (ctt == NomoreToken) {
      Token optoken = getTopElem(exopstck);
      TokenType optt = optoken.getType();
      if (optt == NomoreToken || optt == Assign) {
        exopstck.push(optoken);
        return exstck.top();
      }
      currentToken = getTopElem(exstck);
      ctt = currentToken.gettype();
      exopstck.push(optoken);
    }
    if ((RParen < ctt) && (ctt < Smaller)) {
      exopstck.push(currentToken);
      continue;
    }
    if (ctt == LParen) {
      int nLRaren = 1;
      vector < Token > tmpTokenList;
      while(true) {
        Token tok = getNextToken(tknList);
        TokenType tt = tok.getType();
        if (tt == LParen) {
          nLRaren += 1;
        }
        if (tt == RParen) {
          if (--nLRaren == 0) {
            break;
          }
        }
        if (tt == NomoreToken)
          return syntaxError("右括弧がありませんwww");
        tmpTokenList.insert(tmpTokenList.end(), tok);
      }
      if (tmpTokenList.size() > 1) {
        Token tok = expression(tmpTokenList);
        tok.setType(Value);
        tknList.insert(tknList.begin(), tok);
        continue;
      } else {
        exstck.push(tmpTokenList[0].getValue());
      }
      continue;
    }
    if (Minus << ctt && ctt < Assign) {
      exopstck.push(currentToken);
      continue;
    }
    
  }
}
