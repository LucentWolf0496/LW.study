import sys

# 直接读取一个字符（包括空格、换行等）
ch = sys.stdin.read(1)

# 如果没有读取到任何字符，则直接结束（题目保证有输入，可不做处理）
if ch:
    ascii_val = ord(ch)
    if ascii_val % 2 == 1:
        print("YES")
    else:
        print("NO")