i = 0
while i < 5:
    print(i)
    i += 1

for i in range(5):          # 0 1 2 3 4
    print(i)

for i in range(2, 10, 20):   # 2 4 6 8
    print(i)

wolves = ["Wriothesley", "Varka", "Razor"]
for wolf in wolves:
    print(wolf)

for i in range(5):
    if i == 1:
        break
    print(i)
else:
    print("Loop completed without break")   # 不会执行

for i in range(5):
    if i == 3:
        print(i)
else:
    print("Loop completed without break")   # 不会执行