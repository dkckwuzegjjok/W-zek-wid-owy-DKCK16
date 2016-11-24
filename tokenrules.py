#Contains just the lexing lexing rules.

tokens = ('DO', 'TYPE', 'COLOR', 'NUM', 'SHELF', 'LVL', 'ID', 'WHAT')

t_DO = (r'znajdz|zanies|pobierz|przenies|przewiez|podjedz|odszukaj|odloz|'
        r'uporzadkuj|posortuj')
t_COLOR = (r'czerwon(?:a|ej){1}|niebieska|zolta|zielona|czarna|biala')
t_TYPE = (r'drewn(?:a|iana|ianej){1}|metal(?:u|owa|owej){1}|zywnosc(?:ia|iowa|iowej)?')
t_LVL = (r'poziom(?:u|ie|ach)?|pol(?:ce|ke|ki|kach){1}')
t_SHELF = (r'regal(?:u|e|y|ach)?')
t_WHAT = (r'paczk(?:e|i|ach){1}|pakun(?:ek|ki){1}|skrzyn(?:i|ce|ie|iach|kach){1}')

def t_ID(t):
    r'\d{2,}'
    t.value = int(t.value)
    return t

def t_NUM(t):
    r'\d'
    t.value = int(t.value)
    return t

def t_zignoruj(t):
    r'\bz\b|\bna\b|\bjej\b|\bo\b|\s|\t'
    pass

def t_error(t):
    raise TypeError('Unknown text "%s"' % (t.value))
    t.lexer.skip(1)