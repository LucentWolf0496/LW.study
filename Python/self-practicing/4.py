x = int(input())
res = []
if x % 3 == 0:
    res.append('3')
if x % 5 == 0:
    res.append('5')
if x % 7 == 0:
    res.append('7')
if res:
    print(' '.join(res))   # 将列表中的数字字符串连接起来输出
else:
    print('n')