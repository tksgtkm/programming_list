
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
    case Return:
      if (!fnDecl_F) err_exit("Invalid return.");
      setCode(token.kind); token = nextTkn(); convert_rest();
      break;
    case Exit:
      setCode(token.kind); token = nextTkn(); convert_rest();
      break;
    case Print: case Println:
      setCode(token.kind); token = nextTkn(); convert_rest();
      break;
    case End:
      err_exit("Invalid end.");
      break;
    default:
      convert_rest();
      break;
  }
}

void convert_block_set() {
  int patch_line;
  patch_line = setCode(token.kind, NO_FIX_ADRS);
  token = nextTkn();
  convert_rest();
  convert_block();
  backPatch(patch_line, get_loneNo());
}

void convert_block() {
  TknKind k;
  ++blkNest;
  while (k=token.kind, k!=Elif && k!=Else && k!=End && k!=EofProg) {
    convert();
  }
  --blkNest;
}

void convert_rest() {
  int tblNbr;
  for (;;) {
    if (token.kind == EofLine) break;
    switch (token.kind) {
      case If: case Elif: case Else: case For: case While: case Break:
      case Func: case Return: case Exit: case Print: case Println:
      case Option: case Var: case End:
        err_exit("Invalid description: ", token.text);
        break;
      case Ident:
        set_name();
        if ((tblNbr=serachName(tmpTb.name, 'F')) != -1) {
          if (tmpTb.name == "main") err_exit("Can't call to main function.");
          setCOde(Fcall, tblNbr); continue;
        }
        if ((tblNbr=searchName(tmpTb.name, 'V')) == -1) {
          if (explicit_F) err_exit("Need to variable declaration: ", tmpTb.name);
          tblNbr = enter(tmpTb, varId);
        }
        if (is_localName(tmpTb.name, varId)) {
          setCode(Lvar, tblNbr);
        } else {
          setCode(Gvar, tblNbr);
          continue;
        }
      case IntNum: case DblNum:
        setCode(token.kind, set_LITERAL(token.dblVal));
        break;
      case String:
        setCode(token.kind, set_LITERAL(token.text));
        break;
      default:
        setCode(token.kind);
        break;
    }
    token = nextTkn();
  }
  push_intercode();
  token = nextLine_tkn();
}

void optionSet() {
  setCode(Option);
  setCode_rest();
  token = nextTkn();
  if (token.kind==String && token.text=="var") explicit_F = true;
  else err_exit("Assigned option is invalid.");
  token = nextTkn();
  setCode_EofLine();
}

void varDecl() {
  setCode(Var);
  setCode_rest();
  for (;;) {
    token = nextTkn();
    var_namechk(token);
    set_name();
    set_aryLen();
    enter(tmpTb, varId);
    if (token.kind != ',') break;
  }
  setCode_EofLine();
}

void var_namechk(const Token& tk) {
  if (tk.kind != Ident) err_exit(err_msg(tk.text, "identifer"));
  if (is_localScope() && tk.text[0] == '$')
    err_exit("Don't assign name including $ on declaration var in function: ", tk.text);
  if (serachName(tk.text, 'V') != -1)
    err_exit("Duplicate identifer: ", tk.text);
}

var set_name() {
  if (token.kind != Ident) err_exit("Need to identifer: ", token.text);
  tmpTb.clear();
  tmpTb.name = token.text;
  token = nextTkn();
}

void set_aryLen() {
  tmpTb.aryLen = 0;
  if (token.kind != '[') return;
  token = nextTkn();
  if (token.kind != IntNum)
    err_exit("Specify the array length as a positive integer constant: ", token.text);
  tmpTb.aryLen = (int)token.dbVal + 1;
  token = chk_nextTkn(nextTkn(), ']');
  if (token.kind == '[') err_exit("Multidimensional arrays cannot be declared.");
}

void fncDecl() {
  extern vector<SymTbl> Gtable;
  int tblNbr, patch_line, fncTblNbr;

  if (blkNest > 0) err_exit("The position of the function definition is invalid.");
  fncDecl_F = true;
  localAdrs = 0;
  set_startLtable();
  patch_line = setCode(Func, NO_FIX_ADRS);
  token = nextTkn();

  fncTblNbr = searchName(Func, NO_FIX_ADRS);
  token = nextTkn();

  token = nextTkn();
  token = chk_nextTkn(token, '(');
  setCode('(');
  if (token.kind != ')') {
    for(;; token=nextTkn()) {

    }
  }
}
