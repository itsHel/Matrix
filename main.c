#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

const char soub[] = "C:\\k.txt";

void pmenu(int m)
{
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		printf("MENU\n");
		if (m == 1)
            SetConsoleTextAttribute(hConsole, 207);
		else
            SetConsoleTextAttribute(hConsole, 7);
        printf("water split");
        SetConsoleTextAttribute(hConsole, 7);
        printf(" ");
        if (m == 2)
            SetConsoleTextAttribute(hConsole, 207);
		else
            SetConsoleTextAttribute(hConsole, 7);
        printf("billiard");
        SetConsoleTextAttribute(hConsole, 7);
        printf(" ");
        if (m == 3)
            SetConsoleTextAttribute(hConsole, 207);
        else
            SetConsoleTextAttribute(hConsole, 7);
        printf("exit");
        SetConsoleTextAttribute(hConsole, 7);
}


int **inc(int x,int y)
{
    int **pole;
    pole = malloc(x * sizeof(int *));
        for (int i = 0; i < x; i++)
            pole[i] = malloc(y*sizeof(int));
    return pole;
}

void deinc(int **pole, int x)
{
    for (int i = 0; i < x; i++)
        free(pole[i]);
    free (pole);
    return;
}

void water(int **pole, int **pole2, int x, int y, int xmax, int ymax)
{
    pole2[x][y] = 0;
	for (int rr = -1; rr < 2; rr++)
		for (int ss = -1; ss < 2; ss++)
			if ( (!((ss == 0)&&(rr == 0))) && (!((x == 0)&&(ss == -1))) && (!((y == 0)&&(rr == -1))) && (!((x == xmax-1)&&(ss == 1))) && (!((y == ymax-1)&&(rr == 1))) && (pole2[x+ss][y+rr]!=0) )
				if (pole[x+ss][y+rr]  <= pole[x][y])
                    water(pole,pole2,x+ss,y+rr,xmax,ymax);
    return;
}

void billiard(int **pole, int *cil, int xb, int yb, int smer, int sila, int xmax, int ymax)
{
    int x,y,xs,ys;
    x=xb; y=yb;
    switch (smer) {
        case 1:xs = -1; ys = -1;
            break;
        case 2:xs = 0; ys = -1;
            break;
        case 3:xs = 1; ys = -1;
            break;
        case 4:xs = -1; ys = 0;
            break;
        case 5:xs = 1; ys = 0;
            break;
        case 6:xs = -1; ys = 1;
            break;
        case 7:xs = 0; ys = 1;
            break;
        case 8:xs = 1; ys = 1;
            break;
        default: printf("spatny smer");
    }
            return;
    for (int i = 0; i < sila; i++)
    {
        cil[i] = pole[x][y];
        x = x+xs; y = y+ys;
        if ((x == 0) && (xs == -1))
            xs = 1;
        if ((y == 0) && (ys == -1))
            ys = 1;
        if ((x == xmax-1) && (xs == 1))
            xs = -1;
        if ((y == ymax-1) && (ys == 1))
            ys = -1;
    }
    return;
}

int main(int argc, char *argv[])
{
    if (argc! = 4)
    {
        printf("wrong arguments");
        return 1;
    }

	int menu = 1;
    int znk,brea;

	FILE *file;
    file = fopen(argv[1],"r");
    char c;
    int cislo = 0,rady = 0;
    int **p, **pwater;
    int rad = 0, sl = 0, r = 0, s = 1;
    int vx, vy;
    char lin[256];
    while (fgets(lin, sizeof(lin), file))
        r++;
    vx = strlen(lin);
    for (int i = 0; i < vx; i++)
        if (lin[i] == ' ')
            s++;
    rewind(file);

    p = inc(r, s);

	do
    {
        rady++;
        c = fgetc(file);
        if (!(((c >= 48) && (c¨<= 57)) || (c != 32) || (c != '\n') || (c != EOF)))
        {
            printf("wrong input");
            return 1;
        }
        if (c == 32)
        {
            p[sl][rad] = cislo;
            sl++;
            rady = 0;
            cislo = 0;
            continue;
        }
        if ((c == '\n') || (c == EOF))
        {
            p[sl][rad] = cislo;
            sl = 0;
            rad++;
            rady = 0;
            cislo = 0;
            continue;
        }
        cislo = cislo+(c-48)*pow(10,(rady-1));
    } while (!feof(file));
	do
	{
    brea = 1;
	if (menu == 0)
		menu = 1;
	do
	{
	    pmenu(menu);
        znk = _getch();
		switch (znk) {
			case 13:
			    brea = 0;
				break;
			case 27:
				return 0;
			case 75:
				if (menu == 1)
					menu = 3;
				else
					menu--;
				break;
			case 77:
				if (menu == 3)
					menu = 1;
				else
					menu++;
            }
            system("cls");
	}
	while (brea != 0);

	if (menu == 3)
        return 0;

	if (menu == 1) {
	vx = atoi(argv[2]);
	vy = atoi(argv[3]);

    pwater = inc(s,r);
    for (int i = 0; i<r; i++)
        for (int o = 0; o<s; o++)
            pwater[i][o] = 1;

	water(p,pwater,vx,vy,s,r);

	for (int i = 0; i<r; i++) {
        for (int o = 0; o<s; o++)
            printf ("%d ",pwater[o][i]);
            printf("\n");
	}
	deinc(pwater,r);
	}

	if (menu == 2)
    {
        printf("\nchoose direction:");
        scanf("%d", &vx);
        printf("\nchoose power:");
        scanf("%d", &vy);
        int kpole[10];
        billiard(p, kpole, atoi(argv[2]), atoi(argv[3]), vx, vy, s, r);
        for (int i = 0; i < vy; i++)
            printf("%d ", kpole[i]);
    }
    deinc(p, r);
    printf("\npress any key to return to menu");
    _getch();
    system("cls");
	} while (1);
    return 0;
}


