#include "main.h"

void readFile(FILE * fp, char * str)
{
	int i = 0;
	char c;
	while ((c = getc(fp)) != EOF){
		if (c > 64){
			str[i] = c;
			i++;
		}
	}
	str[i] = '\0';
}

char max(char a, char b, char c)
{
	char max = a;
	if(b > max)
		max = b;
	if(c > max)
		max = c;
	return max;
}

char ** initTable(char * test, char * buf)
{
	char ** table = (char **)malloc(12 * sizeof(char *));
	for (size_t i = 0; i < 12; i++){
		table[i] = (char *)malloc(12 * sizeof(char));
	}
	table[0][0] = '0';
	table[0][1] = '0';
	table[1][0] = '0';

	for (size_t i = 1; i < 12; i++){
		for (size_t j = 1; j < 12; j++){
			table[i][j] = 0;
		}
	}


	for (size_t i = 2; i < 12; i++){
		table[0][i] = buf[i-2];
	}

	for (size_t i = 2; i < 12; i++){
		table[i][0] = test[i-2];
	}
	return table;
}

void printTable(char ** table)
{
	char cn;
	for (size_t i = 0; i < 12; i++){
		for (size_t j = 0; j < 12; j++){
			if(table[i][j] > 40){
				printf("%2c ", table[i][j]);
			}else {
				printf("%2d ", table[i][j]);
			}
		}
		printf("\n");
	}
}

void printFillTable(char * test, char * str, char match, char mismatch, char gap)
{
	char * tmp = str;
	int x = 0, y = 0;
	int maximum = 0;
	char diag = 0, left = 0, top = 0;
	char * buf = (char *)malloc(10 * sizeof(char));
	for (size_t i = 0; i < 10; i++){
		buf[i] = tmp[i];
	}
	char **	table = initTable(test, buf);
	for (size_t i = 2; i < 12; i++) {
		for (size_t j = 2; j < 12; j++) {
			if(table[i][0] == table[0][j]){
				table[i][j] = match + table[i-1][j-1];
			}else {
				diag = table[i-1][j-1] - mismatch;
				left = table[i][j-1] - gap;
				top = table[i-1][j] - gap;
				if  (max(diag, left, top) < 0)
					table[i][j] = 0;
				else
					table[i][j] = max(diag, left, top);
			}
			if(table[i][j] >= maximum){
				maximum = table[i][j];
				x = i;
				y = j;
			}
		}
	}
	printTable(table);
	printf("\n");
	printf("Best position: table[%d][%d]\n", x, y);
	char * result = traceback(table, x, y);
	printf("Traceback: ");
	for (; *result != '\0'; *result++){
		printf("%d ", *result);
	}
	printf("\n");
	printf("-----------------------------------\n");
}

char * traceback(char ** table, char x, char y)
{
	int i = 0, ans = 0;
	char * result = (char *)malloc(20 * sizeof(char));
	while(1){
		result[i] = table[x][y];
		ans = max(table[x-1][y-1], table[x-1][y], table[x][y-1]);
		if(ans == table[x-1][y-1]){
			x--;
			y--;
		}else {
			if(ans == table[x-1][y]){
				x--;
			}else {
				if(ans == table[x][y-1])
					y--;
			}
		}
		if(table[x][y] == 0 && (table[x-1][y-1] == 0 || table[x-1][y-1] >= 45))
			return result;
		i++;
	}
}

int main(int argc, char const *argv[])
{
	FILE * fp = fopen("source.txt", "r");
	char * str = (char *)malloc(3200000 * sizeof(char));
	readFile(fp, str);

	char * test = "cgacgtagtc";
	char * tmp = str;
	char match = 3, mismatch = 3, gap = 2;

	char ** table;
	for (size_t i = 0; i < strlen(str) / 10; i++){
		printFillTable(test, tmp, match, mismatch, gap);
		tmp += 10;	
	}

	free(str);
	return 0;
}