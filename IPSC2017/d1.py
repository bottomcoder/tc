valids = []
for i in range(1, 10001):
	s = list(str(i))
	digits = set()
	valid = True
	for digit in s:
		if digit in digits:
			valid = False
			break
		digits.add(digit)
	if valid:
		valids += [i]

dp = [0] * 10001
bef = [0] * 10001

for i in range(1, 10001):
	dp[i] = 99999999
	for v in valids:
		if v > i:
			break
		if dp[i - v] + 1 < dp[i]:
			dp[i] = dp[i - v] + 1
			bef[i] = i - v

T = int(input())
while T > 0:
	T -= 1
	n = input()
	n = int(input())

	print(dp[n], end = ' ')
	while n > 0:
		mov = n - bef[n]
		print(mov, end = ' ')
		n -= mov
	
	print('')
