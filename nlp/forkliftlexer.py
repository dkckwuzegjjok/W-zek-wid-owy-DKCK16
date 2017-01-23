import ply.lex as lex

tokens = ('MOVEITEM', 'GO', 'LAY', 'SORT', 'PICK', 'FIND', 'MATERIAL', 'CATEGORY',
          'SHELF', 'LVL', 'SIDE', 'FROM', 'TO', 'ITEM', 'COLOR', 'ID', 'NUM')

t_MOVEITEM = (r'za(wiez|nies)|prze(nies|wiez)')
t_GO = (r'(za|do|po(d)?)?jedz|idz|pojdz')
t_LAY = (r'(po|od)loz|(po|do)staw')
t_SORT = (r'u?porzadkuj|(po)?sortuj|po(u|prze)kladaj')
t_PICK = (r'podnies|(z|po)?bierz|zdejmij')
t_FIND = (r'(od|z)najdz|(po|od)?szukaj')
t_MATERIAL = (r'drewn(a|iana|ianej)|metal(u|owa|owej)')
t_CATEGORY = (r'zywnosc(ia|iowa|iowej)?')
t_SHELF = (r'regal(u|e|y|ach)?')
t_LVL = (r'poziom(u|ie|ach)?|pol(ce|k(a|e|i|ach))')
t_SIDE = (r'praw(o|a|y|ej)|lew(o|a|y|ej)|srod(ek|ku)|posrodku')
t_FROM = (r'\bz\b|\bod\b')
t_TO = (r'\bna\b|\bdo\b')
t_ITEM = (r'pacz(ce|ek|k(e|a|i|ach|om))|pakun(ek|ki)|skrzyn(i|ce|ie|iach|kach)|'
          r'karton(u|y|ow(i)?|em|ie|a(mi|ch))|pale(t(e|a(mi)?|y)|cie)')
t_COLOR = (r'czerwon(ego|ych|ym|ej|y|a|e)|niebiesk(i|a|ie(j)?|ich|im(i)?|iego)|'
           r'zolt(y|a|e|ym|ej|ego|ych)|zielon(y|a|e|ym|ej|ego|ych)|'
           r'czarn(y|a|e|ym|ej|ego|ych)|bial(y|a|e|ym|ej|ego|ych)')
# t_NUM = (r'\d')

def t_zignoruj(t):
    (r'\bjej\b|\bo\b|\bi\b|\bma\b|\bnr\b|\bnumer(u|ze)?\b|\bstron(a|e|ie)\b|\bid\b|\bto\b|'
     r'\bpo\b|\bktor(a|ej)\b|\bjest\b|\bkolor(u|ze)\b|\s|\t|,|\.|"|\'|!|\?')
    pass

def t_ID(t):
    r'\d{3}'
    t.value = int(t.value)
    return t

def t_NUM(t):
    r'\d'
    t.value = int(t.value)
    return t

def t_error(t):
    print('Nie wiem co masz na myśli od momentu: "%s".' % (t.value))
    t.lexer.skip(len(t.value))

flexer = lex.lex()