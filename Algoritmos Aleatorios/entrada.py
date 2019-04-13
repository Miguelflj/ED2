



def main():

	entrada = str(input())

	a,b,c = entrada.split()

	a = float(a)
	b = float(b)
	c = float(c)

	a1 = (a*c)/2
	a2 = (c*c)*3.14159
	a3 = (a+b)*c/2
	a4 = b*b
	a5 = a*b

	print("TRIANGULO: {:.3f}".format(a1) )
	print("CIRCULO: {:.3f}".format(a2) )
	print("TRAPEZIO: {:.3f}".format(a3) )
	print("QUADRADO: {:.3f}".format(a4) )
	print("RETANGULO: {:.3f}".format(a5) )


main()