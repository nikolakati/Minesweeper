#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void easy_level(int **minesweeper, char **minesweeper_closed, int mines, int row, int column);
void medium_level(int **minesweeper, char **minesweeper_closed, int mines, int row, int column);
void hard_level(int **minesweeper, char **minesweeper_closed, int mines, int row, int column);
void expert_level(int **minesweeper, char **minesweeper_closed, int mines, int row, int column);
void show_table(char **minesweeper_closed, int row, int column);
void reveal_blocks(int **minesweeper, char **minesweeper_closed, int row, int column, int block1, int block2);
int counter_open_blocks(int **minesweeper, char **minesweeper_closed, int row, int column);
int neighbor_mines(int **minesweeper, char **minesweeper_closed, int row, int column, int block1, int block2);

int main(void)
{
	int row, column, level, assistant_row, assistant_column, **minesweeper, mines, i, flag=1, block1, block2, counter_open, counter_open_no_mines, counter_marks, counter_mines, j;
	int counter, random_row, random_column, assistant_block1, assistant_block2;
	char ch, **minesweeper_closed, str[15], str1[5], str2[6], str3[7];

	srand(time(NULL));

	printf("WELCOME TO MINESWEEPER GAME!\n");
	printf("----------------------------\n");

	do
	{
		printf("Do you want to play, y/n?\n");
		ch = getchar();
		while(getchar() != '\n'); //when the user types enter the program dos nothing
	}while((ch != 'y') && (ch != 'n'));

	if(ch == 'n')
	{
		printf("Bye bye!\n");
		return 0;
	}

	printf("\n");
	printf("RULES OF THE GAME!\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------\n");
	printf("open(x,y): With this command you can open a block (x for row - y for column) e.g. open(4,2).\n");
	printf("mark(x,y): With this command you mark a block that you believe that there is a mine (x for row - y for column) e.g. mark(8,10).\n");
	printf("unmark(x,y): With this command you unmark the block that you have marked (x for row - y for column) e.g. unmark(8,10).\n");
	printf("cheat(x,y): With this command you can see what is behind the block you choosed (x for row - y for column) e.g. cheat(1,1).\n");
	printf("P.S.Your first move in each level must be open or exit!\n");
	printf("P.S.You have marks equal to mines!\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n\n");

	printf("Now you will create your array to play, have fun!!\n");

	do
	{
		printf("\n");
		printf("The array can be created in numbers between [5,30], (minimum 5, maximum 30).\n\n");
		printf("Give me the row: ");
		scanf("%d", &row);
		printf("Give me the column: ");
		scanf("%d", &column);
	}while((row < 5) || (row > 30) || (column < 5) || (column > 30));

	do
	{
		printf("MENU LEVEL!\n");
		printf("---------------\n");
		printf("1.Easy Level.\n");
		printf("2.Medium Level.\n");
		printf("3.Hard Level.\n");
		printf("4.Expert Level.\n");
		printf("---------------\n");
		printf("Select level (number): ");
		scanf("%d", &level);
		getchar();
	}while((level < 1) || (level > 4));

	NEW_LEVEL:

	assistant_row = row + 1;
	assistant_column = column + 1;

	minesweeper = (int**)malloc(assistant_row*sizeof(int*));
	if(minesweeper == NULL)
	{
		printf("No memory allocated!\n");
		exit(0);
	}

	for(i=0; i < assistant_row; i++)
	{
		*(minesweeper+i) = (int*)malloc(assistant_column*sizeof(int));
		if((*(minesweeper+i)) == NULL)
		{
			printf("No memory allocated!\n");
			exit(0);
		}
	}

	minesweeper_closed = (char**)malloc(assistant_row*sizeof(char*));
        if(minesweeper_closed == NULL)
        {
                printf("No memory allocated!\n");
                exit(0);
        }

        for(i=0; i < assistant_row; i++)
        {
                *(minesweeper_closed+i) = (char*)malloc(assistant_column*sizeof(char));
                if((*(minesweeper_closed+i)) == NULL)
                {
                        printf("No memory allocated!\n");
                        exit(0);
                }
        }

	printf("\n\n");

	switch(level)
	{
		case 1:
			mines = (int)((row*column)*0.1);
			printf("EASY LEVEL!\n");
			printf("%dx%d array with %d mines!\n", row, column, mines);
			easy_level(minesweeper, minesweeper_closed, mines, row, column);
			show_table(minesweeper_closed, row, column);
			break;
		case 2:
			mines = (int)((row*column)*0.15);
			printf("MEDIUM LEVEL!\n");
                        printf("%dx%d array with %d mines!\n", row, column, mines);
			medium_level(minesweeper, minesweeper_closed, mines, row, column);
			show_table(minesweeper_closed, row, column);
			break;
		case 3:
			mines = (int)((row*column)*0.2);
			printf("HARD LEVEL!\n");
                        printf("%dx%d array with %d mines!\n", row, column, mines);
                        hard_level(minesweeper, minesweeper_closed, mines, row, column);
			show_table(minesweeper_closed, row, column);
                        break;
		case 4:
			mines = (int)((row*column)*0.25);
			printf("EXPERT LEVEL!\n");
                        printf("%dx%d array with %d mines!\n", row, column, mines);
                        expert_level(minesweeper, minesweeper_closed, mines, row, column);
			show_table(minesweeper_closed, row, column);
                        break;
	}

	printf("START!\n\n");

	counter=0;
	counter_open = 0;
	counter_open_no_mines = ((row*column)-mines);
	counter_marks = mines;

	while(flag)
	{
		do
		{
			AGAIN:

			printf("Enter command: ");
			fgets(str, sizeof(str), stdin);
			str[strcspn(str, "\n")] = 0;
			if((strcmp(str, "exit")) == 0)
			{
				do
				{
					printf("Are you sure you want to leave, y/n?\n");
					ch = getchar();
					while(getchar() != '\n');//when the user typer enter the program does nothing
				}while((ch != 'y') && (ch != 'n'));

				if(ch == 'y')
				{
					printf("Thanks for playing!\n");

					for(i=0; i < assistant_row; i++)
				        	free(*(minesweeper+i));
        				free(minesweeper);

        				for(i=0; i < assistant_row; i++)
                				free(*(minesweeper_closed+i));
        				free(minesweeper_closed);

        				return 0;
				}
				else if(ch == 'n')
					goto AGAIN;
			}

			strncpy(str1, str, 5);
			str1[5] = '\0';

			strncpy(str2, str, 6);
			str2[6] = '\0';

			strncpy(str3, str, 7);
			str3[7] = '\0';

			if((strcmp(str1, "open(")) == 0)
				sscanf(str, "open(%d,%d)", &block1, &block2);
			if((strcmp(str1, "mark(")) == 0)
				sscanf(str, "mark(%d,%d)", &block1, &block2);
			if((strcmp(str2, "cheat(")) == 0)
				sscanf(str, "cheat(%d,%d)", &block1, &block2);
			if((strcmp(str3, "unmark(")) == 0)
				sscanf(str, "unmark(%d,%d)", &block1, &block2);
		}while((block1 <= 0) || (block1 > row) || (block2 <= 0) || (block2 > column));

		while(!counter)
		{
			if(((strcmp(str1, "open(")) == 0) && ((*(*(minesweeper+block1)+block2)) == -1))
			{
				*(*(minesweeper+block1)+block2) = 0;
				random_row = 1 + rand() % row;
				random_column = 1 + rand() % column;
				if(((*(*(minesweeper+random_row)+random_column)) != -1) && (block1 != random_row) && (block2 != random_column))
				{
					*(*(minesweeper+random_row)+random_column) = -1;
					counter++;
				}
				reveal_blocks(minesweeper, minesweeper_closed, row, column, block1, block2);
                                show_table(minesweeper_closed, row, column);
				counter_open = counter_open_blocks(minesweeper, minesweeper_closed, row, column);
			}
			else if(((strcmp(str1, "open(")) == 0) && ((*(*(minesweeper+block1)+block2)) != -1))
			{
				reveal_blocks(minesweeper, minesweeper_closed, row, column, block1, block2);
				show_table(minesweeper_closed, row, column);
				counter++;
				counter_open = counter_open_blocks(minesweeper, minesweeper_closed, row, column);
			}
			else
			{
				printf("Your first move must be open or exit!!\n\n");
				goto AGAIN;
			}

			if(counter_open == counter_open_no_mines)
			{
				printf("YOU WON!!!\n");

				do
				{
					printf("Do you want to continue to the next level, y/n?\n");
					ch = getchar();
					while(getchar() != '\n');
				}while((ch != 'n') && (ch != 'y'));

				if(ch == 'n')
				{
					printf("Thanks for playing, bye bye!!\n");

					for(i=0; i < assistant_row; i++)
						free(*(minesweeper+i));
					free(minesweeper);

					for(i=0; i < assistant_row; i++)
                                                free(*(minesweeper_closed+i));
                                        free(minesweeper_closed);

					return 0;
				}
				else if(ch == 'y')
				{
					printf("LEVEL UP!\n\n");
					row = row + 5;
					column = column + 5;
					if((row > 30) || (column > 30))
					{
						printf("Sorry but you cant play the next level because the array went out of limits!\n\n");
						printf("Thanks for playing, bye bye!!\n");

                                        	for(i=0; i < assistant_row; i++)
                                                	free(*(minesweeper+i));
                                        	free(minesweeper);

                                        	for(i=0; i < assistant_row; i++)
                                                	free(*(minesweeper_closed+i));
                                        	free(minesweeper_closed);

                                        	return 0;
					}
					else
						goto NEW_LEVEL;
				}
			}
			goto AGAIN;
		}

		printf("\n");

		if(counter)
		{
			//open command
			if(((strcmp(str1, "open(")) == 0) && (((*(*(minesweeper+block1)+block2)) == 1) || ((*(*(minesweeper_closed+block1)+block2)) == '.')))
                        {
                                printf("It is already open!!\n\n");
                                show_table(minesweeper_closed, row, column);
                        }
                        else if(((strcmp(str1, "open(")) == 0) && ((*(*(minesweeper_closed+block1)+block2)) == '@'))
                        {
                                printf("It is marked!!\n\n");
                                show_table(minesweeper_closed, row, column);
			}
			else if(((strcmp(str1, "open(")) == 0) && ((*(*(minesweeper+block1)+block2)) == -1))
			{
				printf("You hit a mine!!\n\n");
				printf("GAME OVER!!!\n");
				for(i=0; i < assistant_row; i++)
               	 			free(*(minesweeper+i));
        			free(minesweeper);

	        		for(i=0; i < assistant_row; i++)
        	        		free(*(minesweeper_closed+i));
       				free(minesweeper_closed);

	        		return 0;
			}
			else if(((strcmp(str1, "open(")) == 0) && ((*(*(minesweeper+block1)+block2)) == 0))
			{
				reveal_blocks(minesweeper, minesweeper_closed, row, column, block1, block2);
				counter_open = counter_open_blocks(minesweeper, minesweeper_closed, row, column);
				show_table(minesweeper_closed, row, column);
			}
			//mark command
			if(((strcmp(str1, "mark(")) == 0) && (counter_marks == 0))
				printf("You dont have other marks!!\n\n");
			else if(((strcmp(str1, "mark(")) == 0) && ((*(*(minesweeper_closed+block1)+block2)) == '@'))
			{
				printf("It is already marked!\n\n");
				show_table(minesweeper_closed, row, column);
                	}
			else if(((strcmp(str1, "mark(")) == 0) && (((*(*(minesweeper_closed+block1)+block2)) == '.') || ((*(*(minesweeper+block1)+block2)) == 1)))
			{
				printf("You cant mark it, it is open!\n\n");
				show_table(minesweeper_closed, row, column);
                	}
			else if((strcmp(str1, "mark(")) == 0)
			{
				*(*(minesweeper_closed+block1)+block2) = '@';
				show_table(minesweeper_closed, row, column);
				counter_marks--;
				printf("You still have %d mark(s)!\n\n", counter_marks);
			}
			//unmark command BONUS
			if(((strcmp(str3, "unmark(")) == 0) && (((*(*(minesweeper_closed+block1)+block2)) == '.') || ((*(*(minesweeper+block1)+block2)) == 1)))
                	{
                        	printf("You cant unmark it, it is open!\n\n");
                        	show_table(minesweeper_closed, row, column);
                	}
			else if(((strcmp(str3, "unmark(")) == 0) && ((*(*(minesweeper_closed+block1)+block2)) != '@'))
                	{
                	        printf("You cant unmark it, it is not marked!\n\n");
                        	show_table(minesweeper_closed, row, column);
                	}
			else if(((strcmp(str3, "unmark(")) == 0) && ((*(*(minesweeper_closed+block1)+block2)) == '@'))
                	{
                        	*(*(minesweeper_closed+block1)+block2) = '#';
                        	show_table(minesweeper_closed, row, column);
				counter_marks++;
				printf("Now you have %d mark(s)!!\n\n", counter_marks);
                	}
			//cheat command
			if(((strcmp(str2, "cheat(")) == 0) && ((*(*(minesweeper+block1)+block2)) == -1))
				printf("It has a mine!!\n\n");
			else if(((strcmp(str2, "cheat(")) == 0) && ((*(*(minesweeper+block1)+block2)) == 0))
			{
				counter_mines = 0;
				for(i=-1; i <= 1; i++)
				{
					for(j=-1; j <= 1; j++)
					{
						assistant_block1 = block1 + i;
						assistant_block2 = block2 + j;
						if((assistant_block1 >= 0) && (assistant_block1 <= row) && (assistant_block2 >= 0) && (assistant_block2 <= column))
							if((*(*(minesweeper+assistant_block1)+assistant_block2)) == -1)
								counter_mines++;
					}
				}

				if(counter_mines)
					printf("This block neighbors with %d mines!\n\n", counter_mines);
				else
					printf("It is empty!!\n\n");
			}
			//wrong command
			if(((strcmp(str1, "open(")) != 0) && ((strcmp(str1, "mark(")) != 0) && ((strcmp(str3, "unmark(")) != 0) && ((strcmp(str2, "cheat(")) != 0))
				printf("Wrong synantax or wrong command!!\n\n");
			//checking if the player opened all the blocks
			if(counter_open == counter_open_no_mines)
			{
				printf("YOU WON!!!\n");

				do
				{
					printf("Do you want to continue to the next level, y/n?\n");
					ch = getchar();
					while(getchar() != '\n'); //when the user types enter the program does nothing
				}while((ch != 'n') && (ch != 'y'));

				if(ch == 'n')
				{
					printf("Thanks for playing, bye bye!!\n");

					for(i=0; i < assistant_row; i++)
			                	free(*(minesweeper+i));
       					free(minesweeper);

        				for(i=0; i < assistant_row; i++)
                				free(*(minesweeper_closed+i));
        				free(minesweeper_closed);

       				 	return 0;
				}
				else if(ch == 'y')
				{
					printf("LEVEL UP!!\n\n");
					row = row + 5;
					column = column +5;
					if((row > 30) || (column > 30))
					{
						printf("Sorry but you cant play the next level because the array went out of limits!\n|n");
						printf("Thanks for playing, bye bye!\n");

						for(i=0; i < assistant_row; i++)
	                                	        free(*(minesweeper+i));
        	                        	free(minesweeper);

	                                	for(i=0; i < assistant_row; i++)
        	                                	free(*(minesweeper_closed+i));
                	                	free(minesweeper_closed);

                        	         	return 0;
					}
					else
						goto NEW_LEVEL;
				}
			}
		}
	}

	for(i=0; i < assistant_row; i++)
		free(*(minesweeper+i));
	free(minesweeper);

	for(i=0; i < assistant_row; i++)
                free(*(minesweeper_closed+i));
        free(minesweeper_closed);

	return 0;
}

void easy_level(int **minesweeper, char **minesweeper_closed, int mines, int row , int column)
{
	int i, j, random_row, random_column, counter_mines=mines;

	for(i=0; i <= row; i++)
		for(j=0; j <= column; j++)
		{
			*(*(minesweeper+i)+j) = 0;
			*(*(minesweeper_closed+i)+j) = '#';
		}

	while(counter_mines)
	{
		random_row = 1 + rand() % row;
		random_column = 1 + rand() % column;
		if((*(*(minesweeper+random_row)+random_column)) != -1)
		{
			*(*(minesweeper+random_row)+random_column) = -1;
			counter_mines--;
		}
	}

	return;
}

void medium_level(int **minesweeper, char **minesweeper_closed, int mines, int row , int column)
{
        int i, j, random_row, random_column, counter_mines=mines;

        for(i=0; i <= row; i++)
                for(j=0; j <= column; j++)
                {
                        *(*(minesweeper+i)+j) = 0;
                        *(*(minesweeper_closed+i)+j) = '#';
                }

        while(counter_mines)
        {
                random_row = 1 + rand() % row;
                random_column = 1 + rand() % column;
                if((*(*(minesweeper+random_row)+random_column)) != -1)
                {
                        *(*(minesweeper+random_row)+random_column) = -1;
                        counter_mines--;
                }
        }

        return;
}

void hard_level(int **minesweeper, char **minesweeper_closed, int mines, int row , int column)
{
        int i, j, random_row, random_column, counter_mines=mines;

        for(i=0; i <= row; i++)
                for(j=0; j <= column; j++)
                {
                        *(*(minesweeper+i)+j) = 0;
                        *(*(minesweeper_closed+i)+j) = '#';
                }

        while(counter_mines)
        {
                random_row = 1 + rand() % row;
                random_column = 1 + rand() % column;
                if((*(*(minesweeper+random_row)+random_column)) != -1)
                {
                        *(*(minesweeper+random_row)+random_column) = -1;
                        counter_mines--;
                }
        }

        return;
}

void expert_level(int **minesweeper, char **minesweeper_closed, int mines, int row , int column)
{
        int i, j, random_row, random_column, counter_mines=mines;

        for(i=0; i <= row; i++)
                for(j=0; j <= column; j++)
                {
                        *(*(minesweeper+i)+j) = 0;
                        *(*(minesweeper_closed+i)+j) = '#';
                }

        while(counter_mines)
        {
                random_row = 1 + rand() % row;
                random_column = 1 + rand() % column;
                if((*(*(minesweeper+random_row)+random_column)) != -1)
                {
                        *(*(minesweeper+random_row)+random_column) = -1;
                        counter_mines--;
                }
        }

        return;
}

void show_table(char **minesweeper_closed, int row, int column)
{
	int i, j;

	printf("\n");
	printf("   ");

	for(i=1; i <= column; i++)
	{
		if(i < 10)
			printf(" %d ", i);
		else
			printf(" %d", i);
	}

	printf("\n");
	printf("---");

	for(i=1; i <= column; i++)
		printf("---");

	printf("\n");

	for(j=1; j <= row; j++)
	{
			if(j < 10)
				printf(" %d|", j);
			else
				printf("%d|", j);

		for(i=1; i <= column; i++)
			printf(" %c ", *(*(minesweeper_closed+j)+i));
		printf("\n");
	}

	printf("\n");

	return;
}

int counter_open_blocks(int **minesweeper, char **minesweeper_closed, int row, int column)
{
        int i, j, count=0;

        for(i=1; i <= row; i++)
                for(j=1; j <= column; j++)
                        if(((*(*(minesweeper+i)+j)) == 1) || ((*(*(minesweeper_closed+i)+j)) == '.'))
                                count++;

        return count;
}

void reveal_blocks(int **minesweeper, char **minesweeper_closed, int row, int column, int block1, int block2)
{
	int i, j, counter, assistant_block1, assistant_block2;

	if((block1 < 0) || (block1 > row) || (block2 < 0) || (block2 > column) || (*(*(minesweeper_closed+block1)+block2)) == '.')
		return;

	if((*(*(minesweeper_closed+block1)+block2)) == '@')
		return;

	counter = neighbor_mines(minesweeper, minesweeper_closed, row, column, block1, block2);

	if(counter)
		return;
	else
	{
		*(*(minesweeper_closed+block1)+block2) = '.';
		for(i=-1; i <= 1; i++)
			for(j=-1; j <= 1; j++)
				reveal_blocks(minesweeper, minesweeper_closed, row, column, block1+i, block2+j);
	}
}

int neighbor_mines(int **minesweeper, char **minesweeper_closed, int row, int column, int block1, int block2)
{
	int i, j, counter=0, assistant_block1, assistant_block2;

	for(i=-1; i <= 1; i++)
		for(j=-1; j <= 1; j++)
		{
			assistant_block1 = block1 + i;
			assistant_block2 = block2 + j;
			if((assistant_block1 >=  0) && (assistant_block1 <= row) && (assistant_block2 >= 0) && (assistant_block2 <= column))
				if((*(*(minesweeper+assistant_block1)+assistant_block2)) == -1)
					counter++;
		}

	if(counter)
	{
		*(*(minesweeper_closed+block1)+block2) = counter + '0';
		*(*(minesweeper+block1)+block2) = 1;
	}

	return counter;
}