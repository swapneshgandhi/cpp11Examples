#include <stdio.h>
#include <limits.h>
#include <string.h>

#define B(x) (1ULL << (x))

void createAutomata(int rule,unsigned  long state, int width, int limit)
{
	int i;
	unsigned long st=state;
	int count;

	//long width=sizeof(long) * CHAR_BIT;

	for (i = width; i--; ) putchar(st & B(i) ? 'o' : ' ');
	putchar('\n');

	do {
		st = state;
		for (i = width; i--; ) putchar(st & B(i) ? 'o' : ' ');
		putchar('\n');
 
		for (state = i = 0; i < width; i++)
			if (rule & B(7 & (st>>(i-1) | st<<(width+1-i))))
				state |= B(i);

	} while (st != state && ++count<=limit);
}
 
//this function takes initial position and converts it to state of type long which can be used to create automatas
void auto1d(int rule, char * positions, int limit){

	char binaryInitialState[strlen(positions)];

	int i;
	for (i=0;i<strlen(positions);i++){
		binaryInitialState[i] = positions[i]==' ' ? '0' : '1';
	}

	char *tmp;
	unsigned long state = strtol(binaryInitialState, &tmp , 2);
	createAutomata(rule, state,strlen(positions), limit);

}

int main(){

	auto1d(18, "          o              ",20);

}

