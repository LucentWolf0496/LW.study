n = int(input())
male = []
female = []
for i in range(n):
    gender , height = input().split()
    if gender == "male":
        male.append(float(height))
    else:
        female.append(float(height))

k1 = len(male)
k2 = len(female)
for i in range (0 , k1 - 1):
    for j in range (0 , k1 - i - 1):
        if male[j] > male[j + 1]:
            temp = male[j]
            male[j] = male[j + 1]
            male[j + 1] = temp
for i in range (0 , k2 - 1):
    for j in range (0 , k2 - i - 1):
        if female[j] < female[j + 1]:
            temp = female[j]
            female[j] = female[j + 1]
            female[j + 1] = temp

print(' '.join(f"{h:.2f}" for h in male) + ' ' + ' '.join(f"{h:.2f}" for h in female))