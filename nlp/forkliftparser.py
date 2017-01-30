import ply.yacc as yacc
import forkliftlexer

colorsdict = {'czerwon' : 1, 'niebiesk' : 2, 'zolt' : 3, 'zielon' : 4,
              'czarn' : 5, 'bial' : 6}
materialdict = {'drewn' : 1, 'metal' : 2}
sidedict = {'gor' : 1, 'srod' : 2, 'dol' : 3}
categorydict = {'zywnosc' : 1}
numberdict1 = {'jeden' : 1, 'dwa' : 2, 'trzy' : 3, 'cztery' : 4, 'piec' : 5, 'szesc' : 6}
numberdict2 = {'pierwsz' : 1, 'drug' : 2, 'trzeci' : 3, 'czwart' : 4, 'piat' : 5, 'szost' : 6}

tokens = forkliftlexer.tokens

def p_moveitemfromto1(p):
    '''main : movelay fulltype ITEM id FROM rack TO rack'''
    p[0] = '1' + p[2] + p[6] + p[8] + '0' + p[4]

def p_moveitemfromto2(p):
    '''main : movelay fulltype ITEM id TO rack FROM rack'''
    p[0] = '1' + p[2] + p[8] + p[6] + '0' + p[4]

def p_moveitemfromto3(p):
    '''main : movelay ITEM fulltype id FROM rack TO rack'''
    p[0] = '1' + p[3] + p[6] + p[8] + '0' + p[4]

def p_moveitemfromto4(p):
    '''main : movelay ITEM fulltype id TO rack FROM rack'''
    p[0] = '1' + p[3] + p[8] + p[6] + '0' + p[4]

def p_moveitemfromto5(p):
    '''main : movelay ITEM id fulltype FROM rack TO rack'''
    p[0] = '1' + p[4] + p[6] + p[8] + '0' + p[3]

def p_moveitemfromto6(p):
    '''main : movelay ITEM id fulltype TO rack FROM rack'''
    p[0] = '1' + p[4] + p[8] + p[6] + '0' + p[3]

def p_moveitemfromto7(p):
    '''main : FROM rack movelay fulltype ITEM id TO rack'''
    p[0] = '1' + p[4] + p[2] + p[8] + '0' + p[6]

def p_moveitemfromto8(p):
    '''main : FROM rack movelay ITEM fulltype id TO rack'''
    p[0] = '1' + p[5] + p[2] + p[8] + '0' + p[6]

def p_moveitemfromto9(p):
    '''main : FROM rack movelay ITEM id fulltype TO rack'''
    p[0] = '1' + p[6] + p[2] + p[8] + '0' + p[5]

def p_moveitemfromto10(p):
    '''main : FROM rack TO rack movelay fulltype ITEM id'''
    p[0] = '1' + p[6] + p[2] + p[4] + '0' + p[8]

def p_moveitemfromto11(p):
    '''main : FROM rack TO rack movelay ITEM fulltype id'''
    p[0] = '1' + p[7] + p[2] + p[4] + '0' + p[8]

def p_moveitemfromto12(p):
    '''main : FROM rack TO rack movelay ITEM id fulltype'''
    p[0] = '1' + p[8] + p[2] + p[4] + '0' + p[7]

def p_moveitemto1(p):
    '''main : movelay fulltype ITEM id TO rack'''
    p[0] = '2' + p[2] + '00' + p[6] + '0' + p[4]

def p_moveitemto2(p):
    '''main : movelay ITEM fulltype id TO rack'''
    p[0] = '2' + p[3] + '00' + p[6] + '0' + p[4]

def p_moveitemto3(p):
    '''main : movelay ITEM id fulltype TO rack'''
    p[0] = '2' + p[4] + '00' + p[6] + '0' + p[3]

def p_moveitemto4(p):
    '''main : TO rack movelay fulltype ITEM id'''
    p[0] = '2' + p[4] + '00' + p[2] + '0' + p[6]

def p_moveitemto5(p):
    '''main : TO rack movelay ITEM fulltype id'''
    p[0] = '2' + p[5] + '00' + p[2] + '0' + p[6]

def p_moveitemto6(p):
    '''main : TO rack movelay ITEM id fulltype'''
    p[0] = '2' + p[6] + '00' + p[2] + '0' + p[5]

def p_find1(p):
    '''main : FIND ITEM fulltype id'''
    p[0] = '4' + p[3] + '00' + '00' + '0' + p[4]

def p_find2(p):
    '''main : FIND ITEM id fulltype'''
    p[0] = '4' + p[4] + '00' + '00' + '0' + p[3]

def p_find3 (p):
    '''main : FIND fulltype ITEM id'''
    p[0] = '4' + p[2] + '00' + '00' + '0' + p[4]

def p_pick1(p):
    '''main : PICK fulltype ITEM FROM rack id'''
    p[0] = '5' + p[2] + p[5] + '00' + '0' + p[6]

def p_pick2(p):
    '''main : PICK fulltype ITEM id FROM rack'''
    p[0] = '5' + p[2] + p[6] + '00' + '0' + p[4]

def p_pick3(p):
    '''main : PICK ITEM fulltype id FROM rack'''
    p[0] = '5' + p[3] + p[6] + '00' + '0' + p[4]

def p_pick4(p):
    '''main : PICK ITEM id fulltype FROM rack'''
    p[0] = '5' + p[4] + p[6] + '00' + '0' + p[3]

def p_pick5(p):
    '''main : FROM rack PICK fulltype ITEM id'''
    p[0] = '5' + p[4] + p[2] + '00' + '0' + p[6]

def p_pick6(p):
    '''main : FROM rack PICK ITEM fulltype id'''
    p[0] = '5' + p[5] + p[2] + '00' + '0' + p[6]

def p_pick7(p):
    '''main : FROM rack PICK ITEM id fulltype'''
    p[0] = '5' + p[6] + p[2] + '00' + '0' + p[5]

def p_pick8(p):
    '''main : PICK fulltype ITEM id'''
    p[0] = '5' + p[2] + '00' + '00' + '0' + p[4]

def p_pick9(p):
    '''main : PICK ITEM fulltype id'''
    p[0] = '5' + p[3] + '00' + '00' + '0' + p[4]

def p_pick10(p):
    '''main : PICK ITEM id fulltype'''
    p[0] = '5' + p[4] + '00' + '00' + '0' + p[3]

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

def p_movelay(p):
    '''movelay : MOVEITEM
               | LAY'''
    p[0] = p[1]

def p_rack1(p):
    '''rack : shelf lvl'''
    p[0] = p[1] + p[2]

def p_rack2(p):
    '''rack : lvl shelf'''
    p[0] = p[2] + p[1]

def p_shelf1(p):
    '''shelf : SHELF num'''
    p[0] = str(p[2])

def p_shelf2(p):
    '''shelf : num SHELF'''
    p[0] = str(p[1])

def p_shelf3(p):
    '''shelf : TO SHELF num'''
    p[0] = str(p[3])

def p_shelf4(p):
    '''shelf : TO num SHELF'''
    p[0] = str(p[2])

def p_lvl1(p):
    '''lvl : LVL num'''
    p[0] = str(p[2])

def p_lvl2(p):    
    '''lvl : num LVL'''
    p[0] = str(p[1])

def p_lvl3(p):
    '''lvl : TO LVL num'''
    p[0] = str(p[3])

def p_lvl4(p):
    '''lvl : TO num LVL'''
    p[0] = str(p[2])

def p_lvl5(p):
    '''lvl : LVL TO num'''
    p[0] = str(p[3])

def p_lvl6(p):
    '''lvl : empty'''
    p[0] = p[1]

def p_num1(p):
    '''num : SIDE'''
    for i in sidedict:
        if i in p[1]:
            p[0] = sidedict[i]

def p_num2(p):
    '''num : NUM'''
    p[0] = p[1]

def p_num3(p):
    '''num : NUMWORD1'''
    for i in numberdict1:
        if i in p[1]:
            p[0] = numberdict1[i]

def p_num4(p):
    '''num : NUMWORD2'''
    for i in numberdict2:
        if i in p[1]:
            p[0] = numberdict2[i]

def p_num5(p):
    '''num : empty'''
    p[0] = p[1]

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