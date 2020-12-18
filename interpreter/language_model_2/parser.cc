
#include "token.h"
#include "prot.h"

#define NO_FIX_ADRS 0
Token token;
SymTbl tmpTb;
int blkNest;
int localAdrs;
int mainTblNbr;
int loopNest;
bool finDecl_F;
bool explicit_F;
char codebuf[LIN_SIZ+1], *codebuf_p;
extern vector<char*> intercode;

void init() {
  initChTyp();
  mainTblNbr = -1;
  blkNest = loopNest = 0;
  fncDecl_F = explicit_F = false;
  codebuf_p = codebuf;
}

void convert_to_internalCode(char *fname) {
  init();
  fileOpen(fname);
  while (token=nextLine_tkn(), token.kind != EofProg) {
    if (token.kind == Func) {
      token = nextTkn(); set_name(); enter(tmpTb, fncId);
    }
  }

  push_intercode();
  fileOpen(fname);
  token = nextLine_tkn();
  while (token.kind != EofProg) {
    convert();
  }

  set_startPc(1);
  if (mainTblNbr != -1) {
    set_startPc(intercode.size());
    setCode(Fcall, mainTblNbr); setCode('('); setCode(')');
    push_intercode();
  }
}

void convert() {
  switch (token.kind) {
    case Option:
      optionSet();
      break;
    case Var:
      varDecl();
      break;
    case Func:
      fncDecl();
      break;
    case While: case For:
      ++loopNest;
      convert_block_set();
      setCode_End();
      --loopNest;
      break;
    case If:
      convert_block_set();
      while (token.kind == Elif) {convert_block_set();}
      if (token.kind == Else) {convert_block_set();}
      setCode_End();
      break;
    case Break:
      if (loopNest <= 0) err_exit("Invalid break.");
      setCode(token.kind); token = nextTkn(); convert_rest();
      break;
  }
}
