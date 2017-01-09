import ply.yacc as yacc
import forkliftlexer

colorsdict = {'czerwon' : 1, 'niebiesk' : 2, 'zolt' : 3, 'zielon' : 4,
              'czarn' : 5, 'bial' : 6}
materialdict = {'drewn' : 1, 'metal' : 2}
sidedict = {'lew' : 1, 'srod' : 2, 'praw' : 3}
categorydict = {'zywnosc' : 1}

tokens = forkliftlexer.tokens

def p_moveitemfromto1(p):
    '''main : MOVEITEM fulltype ITEM id FROM rack TO rack side'''
    p[0] = '1' + p[2] + p[6] + p[8] + p[9] + p[4]

def p_moveitemfromto2(p):
    '''main : MOVEITEM fulltype ITEM id FROM rack TO side rack'''
    p[0] = '1' + p[2] + p[6] + p[9] + p[8] + p[4]

def p_moveitemfromto3(p):
    '''main : MOVEITEM fulltype ITEM id TO rack side FROM rack'''
    p[0] = '1' + p[2] + p[9] + p[6] + p[7] + p[4]

def p_moveitemfromto4(p):
    '''main : MOVEITEM fulltype ITEM id TO side rack FROM rack'''
    p[0] = '1' + p[2] + p[9] + p[7] + p[6] + p[4]

def p_moveitemfromto5(p):
    '''main : MOVEITEM ITEM fulltype id FROM rack TO rack side'''
    p[0] = '1' + p[3] + p[6] + p[8] + p[9] + p[4]

def p_moveitemfromto6(p):
    '''main : MOVEITEM ITEM fulltype id FROM rack TO side rack'''
    p[0] = '1' + p[3] + p[6] + p[9] + p[8] + p[4]

def p_moveitemfromto7(p):
    '''main : MOVEITEM ITEM fulltype id TO rack side FROM rack'''
    p[0] = '1' + p[3] + p[9] + p[6] + p[7] + p[4]

def p_moveitemfromto8(p):
    '''main : MOVEITEM ITEM fulltype id TO side rack FROM rack'''
    p[0] = '1' + p[3] + p[9] + p[7] + p[6] + p[4]

def p_moveitemfromto9(p):
    '''main : MOVEITEM ITEM id fulltype FROM rack TO rack side'''
    p[0] = '1' + p[4] + p[6] + p[8] + p[9] + p[3]

def p_moveitemfromto10(p):
    '''main : MOVEITEM ITEM id fulltype FROM rack TO side rack'''
    p[0] = '1' + p[4] + p[6] + p[9] + p[8] + p[3]

def p_moveitemfromto11(p):
    '''main : MOVEITEM ITEM id fulltype TO rack side FROM rack'''
    p[0] = '1' + p[4] + p[9] + p[6] + p[7] + p[3]

def p_moveitemfromto12(p):
    '''main : MOVEITEM ITEM id fulltype TO side rack FROM rack'''
    p[0] = '1' + p[4] + p[9] + p[7] + p[6] + p[3]

def p_moveitemfromto14(p):
    '''main : FROM rack MOVEITEM fulltype ITEM id TO rack side'''
    p[0] = '1' + p[4] + p[2] + p[8] + p[9] + p[6]

def p_moveitemfromto15(p):
    '''main : FROM rack MOVEITEM fulltype ITEM id TO side rack'''
    p[0] = '1' + p[4] + p[2] + p[9] + p[8] + p[6]

def p_moveitemfromto16(p):
    '''main : FROM rack MOVEITEM ITEM fulltype id TO rack side'''
    p[0] = '1' + p[5] + p[2] + p[8] + p[9] + p[6]

def p_moveitemfromto17(p):
    '''main : FROM rack MOVEITEM ITEM fulltype id TO side rack'''
    p[0] = '1' + p[5] + p[2] + p[9] + p[8] + p[6]

def p_moveitemfromto18(p):
    '''main : FROM rack MOVEITEM ITEM id fulltype TO rack side'''
    p[0] = '1' + p[6] + p[2] + p[8] + p[9] + p[5]

def p_moveitemfromto19(p):
    '''main : FROM rack MOVEITEM ITEM id fulltype TO side rack'''
    p[0] = '1' + p[6] + p[2] + p[9] + p[8] + p[5]

def p_moveitemfromto20(p):
    '''main : FROM rack TO rack side MOVEITEM fulltype ITEM id'''
    p[0] = '1' + p[7] + p[2] + p[4] + p[5] + p[9]

def p_moveitemfromto21(p):
    '''main : FROM rack TO side rack MOVEITEM fulltype ITEM id'''
    p[0] = '1' + p[7] + p[2] + p[5] + p[4] + p[9]

def p_moveitemfromto23(p):
    '''main : FROM rack TO rack side MOVEITEM ITEM fulltype id'''
    p[0] = '1' + p[8] + p[2] + p[4] + p[5] + p[9]

def p_moveitemfromto24(p):
    '''main : FROM rack TO side rack MOVEITEM ITEM fulltype id'''
    p[0] = '1' + p[8] + p[2] + p[5] + p[4] + p[9]

def p_moveitemfromto25(p):
    '''main : FROM rack TO rack side MOVEITEM ITEM id fulltype'''
    p[0] = '1' + p[9] + p[2] + p[4] + p[5] + p[8]

def p_moveitemfromto26(p):
    '''main : FROM rack TO side rack MOVEITEM ITEM id fulltype'''
    p[0] = '1' + p[9] + p[2] + p[5] + p[4] + p[8]

def p_go1(p):
    '''main : GO TO rack side'''
    p[0] = '2' + '000' + '00' + p[3] + p[4] + '000'

def p_go2(p):
    '''main : GO TO side rack'''
    p[0] = '2' + '000' + '00' + p[4] + p[3] + '000'

def p_go3(p):
    '''main : GO TO ITEM fulltype id'''
    p[0] = '3' + p[4] + '00' + '00' + '0' + p[5]

def p_go4(p):
    '''main : GO TO ITEM id fulltype'''
    p[0] = '3' + p[5] + '00' + '00' + '0' + p[4]

def p_go5(p):
    '''main : GO TO fulltype ITEM id'''
    p[0] = '3' + p[3] + '00' + '00' + '0' + p[5]

def p_find1(p):
    '''main : FIND rack side'''
    p[0] = '2' + '000' + '00' + p[2] + p[3] + '000'

def p_find2(p):
    '''main : FIND side rack'''
    p[0] = '2' + '000' + '00' + p[3] + p[2] + '000'

def p_find3(p):
    '''main : FIND ITEM fulltype id'''
    p[0] = '3' + p[3] + '00' + '00' + '0' + p[4]

def p_find4(p):
    '''main : FIND ITEM id fulltype'''
    p[0] = '3' + p[4] + '00' + '00' + '0' + p[3]

def p_find5 (p):
    '''main : FIND fulltype ITEM id'''
    p[0] = '3' + p[2] + '00' + '00' + '0' + p[4]

def p_pick1(p):
    '''main : PICK fulltype ITEM FROM rack id'''
    p[0] = '4' + p[2] + p[5] + '00' + '0' + p[6]

def p_pick2(p):
    '''main : PICK fulltype ITEM id FROM rack'''
    p[0] = '4' + p[2] + p[6] + '00' + '0' + p[4]

def p_pick3(p):
    '''main : PICK ITEM fulltype id FROM rack'''
    p[0] = '4' + p[3] + p[6] + '00' + '0' + p[4]

def p_pick4(p):
    '''main : PICK ITEM id fulltype FROM rack'''
    p[0] = '4' + p[4] + p[6] + '00' + '0' + p[3]

def p_pick5(p):
    '''main : FROM rack PICK fulltype ITEM id'''
    p[0] = '4' + p[4] + p[2] + '00' + '0' + p[6]

def p_pick6(p):
    '''main : FROM rack PICK ITEM fulltype id'''
    p[0] = '4' + p[5] + p[2] + '00' + '0' + p[6]

def p_pick7(p):
    '''main : FROM rack PICK ITEM id fulltype'''
    p[0] = '4' + p[6] + p[2] + '00' + '0' + p[5]

def p_pick8(p):
    '''main : PICK fulltype ITEM id'''
    p[0] = '4' + p[2] + '00' + '00' + '0' + p[4]

def p_pick9(p):
    '''main : PICK ITEM fulltype id'''
    p[0] = '4' + p[3] + '00' + '00' + '0' + p[4]

def p_pick10(p):
    '''main : PICK ITEM id fulltype'''
    p[0] = '4' + p[4] + '00' + '00' + '0' + p[3]

def p_lay1(p):
    '''main : LAY ITEM TO rack side'''
    p[0] = '5' + '000' + '00' + p[4] + p[5] + '000'

def p_lay2(p):
    '''main : LAY ITEM TO side rack'''
    p[0] = '5' + '000' + '00' + p[5] + p[4] + '000'

def p_lay3(p):
    '''main : ITEM LAY TO rack side'''
    p[0] = '5' + '000' + '00' + p[4] + p[5] + '000'

def p_lay4(p):
    '''main : ITEM LAY TO side rack'''
    p[0] = '5' + '000' + '00' + p[5] + p[4] + '000'

# def p_sort(p):

def p_fulltype1(p):
    '''fulltype : color material category'''
    p[0] = p[1] + p[2] + p[3]

def p_fulltype2(p):
    '''fulltype : color category material'''
    p[0] = p[1] + p[3] + p[2]

def p_fulltype3(p):
    '''fulltype : material category color'''
    p[0] = p[3] + p[1] + p[2]

def p_fulltype4(p):
    '''fulltype : material color category'''
    p[0] = p[2] + p[1] + p[3]

def p_fulltype5(p):
    '''fulltype : category material color'''
    p[0] = p[3] + p[2] + p[1]

def p_fulltype6(p):
    '''fulltype : category color material'''
    p[0] = p[2] + p[3] + p[1]

def p_material(p):
    '''material : MATERIAL
                | empty'''
    p[0] = p[1]
    for i in materialdict:
        if i in p[1]:
            p[0] = str(materialdict[i])

def p_color(p):
    '''color : COLOR
             | empty'''
    p[0] = p[1]        
    for i in colorsdict:
        if i in p[1]:
            p[0] = str(colorsdict[i])

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
            | SIDE
            | empty'''
    if len(p) == 2:
        if p[1] != '0':
            for i in sidedict:
                if i in p[1]:
                    p[0] = str(sidedict[i])
        else:
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