import ply.yacc as yacc
import forkliftlexer

colorsdict = {'czerwon' : 1, 'niebiesk' : 2, 'zolt' : 3, 'zielon' : 4,
              'czarn' : 5, 'bial' : 6}
materialdict = {'drewn' : 1, 'metal' : 2, 'zywnosc' : 3}
sidedict = {'lew' : 1, 'srod' : 2, 'praw' : 3}
categorydict = {'zywnosc' : 1}

tokens = forkliftlexer.tokens

def p_moveitemfromto1(p):
    '''moveitemfromto : MOVEITEM fulltype ITEM id FROM rack TO rack side'''
    p[0] = '1' + p[2] + p[6] + p[8] + p[9] + p[4]

def p_moveitemfromto02(p):
    '''moveitemfromto : MOVEITEM fulltype ITEM id FROM rack side TO rack'''
    p[0] = '1' + p[2] + p[6] + p[9] + p[7] + p[4]

def p_moveitemfromto2(p):
    '''moveitemfromto : MOVEITEM fulltype ITEM id FROM rack side rack'''
    p[0] = '1' + p[2] + p[6] + p[8] + p[7] + p[4]

def p_moveitemfromto3(p):
    '''moveitemfromto : MOVEITEM fulltype ITEM id rack side FROM rack'''
    p[0] = '1' + p[2] + p[8] + p[5] + p[6] + p[4]

def p_moveitemfromto4(p):
    '''moveitemfromto : MOVEITEM fulltype ITEM id side rack FROM rack'''
    p[0] = '1' + p[2] + p[8] + p[6] + p[5] + p[4]

def p_moveitemfromto5(p):
    '''moveitemfromto : MOVEITEM ITEM fulltype id FROM rack rack side'''
    p[0] = '1' + p[3] + p[6] + p[7] + p[8] + p[4]

def p_moveitemfromto6(p):
    '''moveitemfromto : MOVEITEM ITEM fulltype id FROM rack side rack'''
    p[0] = '1' + p[3] + p[6] + p[8] + p[7] + p[4]

def p_moveitemfromto7(p):
    '''moveitemfromto : MOVEITEM ITEM fulltype id rack side FROM rack'''
    p[0] = '1' + p[3] + p[8] + p[5] + p[6] + p[4]

def p_moveitemfromto8(p):
    '''moveitemfromto : MOVEITEM ITEM fulltype id side rack FROM rack'''
    p[0] = '1' + p[3] + p[8] + p[6] + p[5] + p[4]

def p_moveitemfromto9(p):
    '''moveitemfromto : MOVEITEM ITEM id fulltype FROM rack rack side'''
    p[0] = '1' + p[4] + p[6] + p[7] + p[8] + p[4]

def p_moveitemfromto10(p):
    '''moveitemfromto : MOVEITEM ITEM id fulltype FROM rack side rack'''
    p[0] = '1' + p[4] + p[6] + p[8] + p[7] + p[3]

def p_moveitemfromto11(p):
    '''moveitemfromto : MOVEITEM ITEM id fulltype rack side FROM rack'''
    p[0] = '1' + p[4] + p[8] + p[5] + p[6] + p[3]

def p_moveitemfromto12(p):
    '''moveitemfromto : MOVEITEM ITEM id fulltype side rack FROM rack'''
    p[0] = '1' + p[4] + p[8] + p[6] + p[5] + p[3]

def p_moveitemfromto14(p):
    '''moveitemfromto : FROM rack MOVEITEM fulltype ITEM id rack side'''
    p[0] = '1' + p[4] + p[2] + p[7] + p[8] + p[6]

def p_moveitemfromto15(p):
    '''moveitemfromto : FROM rack MOVEITEM fulltype ITEM id side rack'''
    p[0] = '1' + p[4] + p[2] + p[8] + p[7] + p[6]

def p_moveitemfromto16(p):
    '''moveitemfromto : FROM rack MOVEITEM ITEM fulltype id rack side'''
    p[0] = '1' + p[5] + p[2] + p[7] + p[8] + p[6]

def p_moveitemfromto17(p):
    '''moveitemfromto : FROM rack MOVEITEM ITEM fulltype id side rack'''
    p[0] = '1' + p[5] + p[2] + p[8] + p[7] + p[6]

def p_moveitemfromto18(p):
    '''moveitemfromto : FROM rack MOVEITEM ITEM id fulltype rack side'''
    p[0] = '1' + p[6] + p[2] + p[7] + p[8] + p[5]

def p_moveitemfromto19(p):
    '''moveitemfromto : FROM rack MOVEITEM ITEM id fulltype side rack'''
    p[0] = '1' + p[6] + p[2] + p[8] + p[7] + p[5]

def p_moveitemfromto20(p):
    '''moveitemfromto : FROM rack rack side MOVEITEM fulltype ITEM id'''
    p[0] = '1' + p[6] + p[2] + p[3] + p[4] + p[8]

def p_moveitemfromto21(p):
    '''moveitemfromto : FROM rack side rack MOVEITEM fulltype ITEM id'''
    p[0] = '1' + p[6] + p[2] + p[4] + p[3] + p[8]

def p_moveitemfromto23(p):
    '''moveitemfromto : FROM rack rack side MOVEITEM ITEM fulltype id'''
    p[0] = '1' + p[7] + p[2] + p[3] + p[4] + p[8]

def p_moveitemfromto24(p):
    '''moveitemfromto : FROM rack side rack MOVEITEM ITEM fulltype id'''
    p[0] = '1' + p[7] + p[2] + p[4] + p[3] + p[8]

def p_moveitemfromto25(p):
    '''moveitemfromto : FROM rack rack side MOVEITEM ITEM id fulltype'''
    p[0] = '1' + p[8] + p[2] + p[3] + p[4] + p[7]

def p_moveitemfromto26(p):
    '''moveitemfromto : FROM rack side rack MOVEITEM ITEM id fulltype'''
    p[0] = '1' + p[8] + p[2] + p[4] + p[3] + p[7]

# def p_go(p):

# def p_pick(p):

# def p_lay(p):

# def p_find(p):

def p_fulltype(p):
    '''fulltype : color matcat
                | matcat color
                | material color category
                | category color material'''
    if len(p) == 4:
        if 'm' in p[1]:
            p[0] = p[2].replace('c', '') + p[1].replace('m', '') + p[3]
        else:
            p[0] = p[2].replace('c', '') + p[3].replace('m', '') + p[1]
    elif len(p) == 3:
        if 'c' in p[1]:
            p[0] = p[1].replace('c', '') + p[2].replace('m', '')
        else:
            p[0] = p[2].replace('c', '') + p[1].replace('m', '')

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
       p[0] = p[1].replace('s', '') + p[2]
    else:
        p[0] = p[2].replace('s', '') + p[1]

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
    if len(p) == 3:
        if type(p[1]) is str:
            p[0] = str(p[2])
        elif type(p[2]) is str:
            p[0] = str(p[1])
    elif len(p) == 2:
        p[0] = p[1]

def p_side(p):
    '''side : TO SIDE
            | empty'''
    if len(p) == 2:
        p[0] = p[1]
    elif len(p) == 3:
        for i in sidedict:
            if i in p[2]:
                p[0] = str(sidedict[i])

def p_id(p):
    '''id : ID
          | emptyid'''
    p[0] = str(p[1])

def p_emptyid(p):
    '''emptyid :'''
    p[0] = '000'

def p_empty(p):
    '''empty :'''
    p[0] = '0'

def p_error(p):
    print('Syntax error in input! %s' % (p))

fparser = yacc.yacc(write_tables=False, debug=False)