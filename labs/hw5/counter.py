f = open('3.in')

I = 0
D = 0

line = 0
for i in range(410):
    line = f.readline()
    if line == '':
        break
    if line[0] == 'I':
        I += 1
    elif line[0] == 'D':
        D += 1
    
print('D:', D)
print('I:', I)