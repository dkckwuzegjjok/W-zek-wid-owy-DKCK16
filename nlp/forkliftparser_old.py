import ply.yacc as yacc
import forkliftlexer

colorsdict = {'czerwon' : 1, 'niebiesk' : 2, 'zolt' : 3, 'zielon' : 4,
              'czarn' : 5, 'bial' : 6}
materialdict = {'drewn' : 1, 'metal' : 2, 'zywnosc' : 3}
sidedict = {'lew' : 1, 'srod' : 2, 'praw' : 3}
categorydict = {'zywnosc' : 1}


tokens = forkliftlexer.tokens

def p_moveitemfromto(p):
    '''moveitemfromto : MOVEITEM fulltype item rack rack side
                      | MOVEITEM rack rack side fulltype item
                      | rack MOVEITEM fulltype item rack side
                      | rack MOVEITEM rack side fulltype item'''
    if 'i' in p[3]:
        p[0] = ('1' + p[2] + p[4] + p[5] + p[6]).replace('c', '')\
                                                .replace('s', '')\
                                                .replace('m', '')
    elif 'i' in p[6]:
        if 's' in p[2] and p[3]:
            p[0] = ('1' + p[5] + p[2] + p[3] + p[4]).replace('c', '')\
                                                    .replace('s', '')\
                                                    .replace('m', '')
        elif 's' in p[1] and p[3]:
            p[0] = ('1' + p[5] + p[1] + p[3] + p[4]).replace('c', '')\
                                                    .replace('s', '')\
                                                    .replace('m', '')
    elif 'i' in p[4]:
        p[0] = ('1' + p[3] + p[1] + p[5] + p[6]).replace('c', '')\
                                                .replace('s', '')\
                                                .replace('m', '')
# def p_go(p):

# def p_pick(p):

# def p_lay(p):

# def p_find(p):

# def p_fulltype(p):
#     '''fulltype : color material category
#                 | color category material
#                 | category color material
#                 | material color category
#                 | material category color
#                 | category material color'''
#     p[0] = p[1] + p[2] + p[3]


def p_fulltype(p):
    '''fulltype : color matcat
                | matcat color
                | material color category
                | category color material'''
    if len(p) > 3:
        if 'm' in p[1]:
            p[0] = p[2] + p[1] + p[3]
        else:
            p[0] = p[2] + p[3] + p[1]
    if len(p) < 4:
        if 'c' in p[1]:
            p[0] = p[1] + p[2]
        else:
            p[0] = p[2] + p[1]

def p_matcat(p):
    '''matcat : material category
              | category material'''
    p[0] = p[2] + p[1]
    if 'm' in p[1]:
        p[0] = p[1] + p[2]
    elif 'm' in p[2]:
        p[0] = p[2] + p[1]

def p_material(p):
    '''material : MATERIAL
                | empty'''
    p[0] = p[1]
    for i in materialdict:
        if i in p[1]:
            p[0] = str(materialdict[i]) + 'm'

def p_color(p):
    '''color : COLOR
             | empty'''
    p[0] = p[1]        
    for i in colorsdict:
        if i in p[1]:
            p[0] = str(colorsdict[i]) + 'c'

def p_category(p):
    '''category : CATEGORY
                | empty'''
    p[0] = p[1]
    for i in categorydict:
        if i in p[1]:
            p[0] = str(categorydict[i])

def p_rack(p):
    '''rack : shelf lvl
            | lvl shelf'''
    if 's' in p[1]:
       p[0] = p[1] + p[2]
    else:
        p[0] = p[2] + p[1]

def p_shelf(p):
    '''shelf : SHELF NUM
             | NUM SHELF'''
    if type(p[1]) is str:
        p[0] = str(p[2]) + 's'
    else:
        p[0] = str(p[1]) + 's'

def p_lvl(p):
    '''lvl : LVL NUM
           | NUM LVL
           | empty'''
    if len(p) > 2:
        if type(p[1]) is str:
            p[0] = str(p[2])
        elif type(p[2]) is str:
            p[0] = str(p[1])
    else:
        p[0] = p[1]

def p_side(p):
    '''side : SIDE
            | empty'''
    p[0] = p[1]
    p[0] = p[1]
    for i in sidedict:
        if i in p[1]:
            p[0] = str(sidedict[i])

def p_item(p):
    '''item : ITEM'''
    p[0] = 'i'

def p_empty(p):
    'empty :'
    p[0] = '0'

def p_error(p):
    print('Syntax error in input!')

fparser = yacc.yacc(write_tables=False, debug=False)

# def parse(data, debug=False):
