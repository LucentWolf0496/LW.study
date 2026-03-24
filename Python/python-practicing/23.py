n = int(input())
patients = []
for _ in range(n):
    pid, age = input().split()
    patients.append((pid, int(age)))

elderly = [p for p in patients if p[1] >= 60]
non_elderly = [p for p in patients if p[1] < 60]
k = len(elderly)
for i in range(0 , k - 1):
    for j in range(0 , k - i - 1):
        if (elderly[j][1] < elderly[j + 1][1]):
            temp = elderly[j]
            elderly[j] = elderly[j + 1]
            elderly[j + 1] = temp

for i in elderly:
    print(i[0])
for i in non_elderly:
    print(i[0])