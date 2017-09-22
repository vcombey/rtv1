#include <stdio.h>
#include <stdlib.h>

struct s {
	int a[100];
	int *b;
};

void modify(struct s toto) {
	toto.a[0] = 0;
}

void beuh (int i)
{
	i = 0;
}

int main(void)
{
	struct s toto;

	printf("la taille de la structure est %lu\n", sizeof(toto));
	toto.a[0] = 42;
	toto.b[1] = 21;
	toto.b = malloc(100);


	int *i = (int *)&toto;
	i[0] = -42;


	toto.b[0] = 42;
	toto.b[1] = 21;
	printf("la taille de la structure est %lu\n", sizeof(toto));
	printf("struct is at %p\n", &toto);

	printf("first a field of struct is at %p\n", toto.a);
	printf("first a field of struct is at %p\n", &toto.a[0]);
	printf("first b field of struct is at %p\n", &toto.b[0]);

	modify(toto);

	int k = 42;

	int tab[3];
	int *tab;

	beuh2(tab);
	beuh(k);
	printf("ma valeur est %i\n", toto.a[0]);
	return (0);
}
