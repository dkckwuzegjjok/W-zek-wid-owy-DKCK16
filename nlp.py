import sys
import tokenrules
import ply.lex as lex

def trans(word):
    intab = 'ąęółśżźćń'
    outtab = 'aeolszzcn'
    transtab = str.maketrans(intab, outtab)
    return word.translate(transtab)

lexer = lex.lex(module=tokenrules)

cmd = trans(sys.argv[1].lower())

lexer.input(cmd)
for tok in lexer:
    print(tok)