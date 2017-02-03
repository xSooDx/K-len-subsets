all: p.out s.out

p.out:
	gcc -std=c99 -o p.out klss_p.c -fopenmp
s.out:
	gcc -std=c99 -o s.out klss.c
