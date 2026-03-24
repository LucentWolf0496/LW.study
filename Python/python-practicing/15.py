x1 = str(input())
x = ''
for i in x1:
    x = i + x
x = x.swapcase()
n = len(x)
result = []
for i in range(0 , n):
    if x[i] == 'x':
        result.append('a')
    elif x[i] == 'X':
        result.append('A')
    elif x[i] == 'y':
        result.append('b')
    elif x[i] == 'Y':
        result.append('B')
    elif x[i] == 'z':
        result.append('c')
    elif x[i] == 'Z':
        result.append('C')
    else:
        result.append(chr(ord(x[i]) + 3))
print(''.join(result))