

def main():
	n = int(input()) 
	entrada = []
	palavrasTotal = []
	for i in range(n):
		entrada.append((input()))
		palavrasTotal.append(entrada[i].split())
	for i in range(len(palavrasTotal)):
		for j in range( len(palavrasTotal[i]) ):
			test = len(palavrasTotal[i][j])
			print(test)
main()