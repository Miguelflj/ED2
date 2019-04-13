


def fatorial(fat):
	if( fat == 1):
		return 1
	else:
		return fat * fatorial(fat-1)





def main():
	n = int(input())
	fat = fatorial(n)
	print("Fatorial de %d! é: %d" %(n,fat))

main()