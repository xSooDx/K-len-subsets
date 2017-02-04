all: p.out s.out

p.out: klss_p.c
	gcc -std=c99 -o p.out klss_p.c -fopenmp
s.out: klss.c
	gcc -std=c99 -o s.out klss.c
