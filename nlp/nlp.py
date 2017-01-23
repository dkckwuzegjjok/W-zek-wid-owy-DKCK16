import sys
import forkliftlexer
import forkliftparser

def trans(word):
    intab = 'ąęółśżźćń'
    outtab = 'aeolszzcn'
    transtab = str.maketrans(intab, outtab)
    return word.translate(transtab)

cmd = trans(sys.argv[1].lower())

forkliftlexer.flexer.input(cmd)

for tok in forkliftlexer.flexer:
    print(tok)
    
# file = open('out.txt', 'w')
# file.write(forkliftparser.fparser.parse(cmd))
# file.close()

print(forkliftparser.fparser.parse(cmd))