x = int(input())
print("Y" if x % 400 == 0 or (x % 100 != 0 and x % 4 == 0) else "N")