#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	putnbr_bin(unsigned int n)
{
	unsigned int  mask = 2147483648;
	int i;
	i = 1;
	while (mask) 
	{
		if (n & mask)
			ft_putchar('1');
		else
			ft_putchar('0');
		mask >>= 1;
		if (i % 8 == 0)
			ft_putchar(' ');
		i++;
	}

}

int main(int ac, char **av)
{
	unsigned long int a = (unsigned long int)atoi(av[1]);
	//unsigned long int a = 0x00000100UL;
	unsigned long int b = (a) - 0x01010101UL;
	unsigned long int c = ~(a) & 0x80808080UL;
	unsigned long int d = b & c;

	printf("LOW MASK = \n");
	putnbr_bin(0x01010101UL);
	printf("\nHIGH MASK = \n");
	putnbr_bin(0x80808080UL);
	printf("\na = \n"); 
	putnbr_bin(a);
	printf("\nb = \n"); 
	putnbr_bin(b);
	printf("\nc = \n"); 
	putnbr_bin(c);
	printf("\nd = \n"); 
	putnbr_bin(d);
	return (0);
}
