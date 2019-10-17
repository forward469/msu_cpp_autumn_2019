import subprocess

flag = 1

def check(expr, result):
	global flag
	out = subprocess.run(['./calc', expr], stdout=subprocess.PIPE)
	if out.stdout.decode('ascii').rstrip() != result:
		print('error {0} != {1}, got {2}'.format(expr, result, out.stdout.decode('ascii').rstrip()))
		flag = 0

check('2 + 2', '4')
check('2 + 2 * 2', '6')
check('2 + 2 * -2', '-2')
check('512451 / 23413', '21')
check('-5213 + 2134', '-3079')
check('-5--4', '-1')
check('-9 ', '-9')
check('---9', '-9')
check('----9', '9')
check('---9 - ----9', '-18')

#check('5/0', 'The expression is incorrect')
#check('2^2', 'The expression is incorrect')
if flag:
	print('no errors')