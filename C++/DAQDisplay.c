########################################
##  Authored by Sathya Anand (c) 2020 ##
########################################
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "float.h"
# include "windows.h"
# include "conio.h"

#define Annular 1
#define Bundle 2
#define Tubular 3
#define Width 168 // 168 /8 = 21 spacings (8 Coloumns)
#define Length 56 // 56 / 8 = 11 spacings (8 rows )
#define firstline 1 // indention from top
#define Width 168  // 168 /8 = 21 spacings (8 Coloumns)
#define Length (56 ) // 56 / 8 = 11 spacings (8 rows )
#define DAQ1Outputs 10
#define DAQ2AOutputsWall 6
#define DAQ2AOutputsangle 4
#define DAQ2BOutputsRods 21
#define DAQ2TOutputs 18 
#define DAQ3BOutputsWall 10
#define DAQ4Outputs 10

int TSTopt, DAQ1Disp[DAQ1Outputs][2] = { 0 }, DAQ4Disp[DAQ4Outputs][2] = { 0 }, DAQ2Disp[DAQ2TOutputs][2],
DAQ2Disp1[DAQ2AOutputsWall][2], DAQ2Disp2[DAQ2AOutputsangle][2], DAQ2DispB[DAQ2BOutputsRods][2], DAQ3Disp[DAQ3BOutputsWall][2];

void gotoxy(int x, int y)//rehash of conio.h (DOS only) gotoxy function from http://cboard.cprogramming.com/cplusplus-programming/93806-conio-h-functions-mingw.html

{

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void GetXY(int *x, int *y)//rehash of conio.h (DOS only) getxy function from http://cboard.cprogramming.com/cplusplus-programming/93806-conio-h-functions-mingw.html

{

	CONSOLE_SCREEN_BUFFER_INFO  csbInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);

	*x = csbInfo.dwCursorPosition.X;

	*y = csbInfo.dwCursorPosition.Y;

}

void ConsoleSize()
{
	HANDLE wHnd;    // Handle to write to the console.
	HANDLE rHnd;    // Handle to read from the console.
	// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	// Set up the required window size: (start at 0,0 end at 1366 x 768)
	SMALL_RECT windowSize = { 0, 0, 100, 100 };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	// Change the console window size:
	// Create a COORD to hold the buffer size:
	COORD bufferSize = { Width, Length };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}

void	TestSetup()
{
	system("cls");
	/* -------------------------------------------------------- */
	/*	Subroutine that guides the user to setup the test to	*/
	/*		carry out and data to acquire. It outputs the test	*/
	/*		section  option chosen and type of run option		*/
	/* -------------------------------------------------------- */

	printf("\n                           R-134a Test section setup: \n");

	printf(" Test Section Option: \n\n");

	printf(" Annular Test Section ................................................ (1) \n\n");

	printf(" Bundle Test Section ................................................. (2) \n\n");

	printf(" Tubular Test Section ................................................ (3) \n\n");

	printf(" Exit ................................................................ (0) \n\n");

	printf(" ................................................  Enter Selection ==>  ");
TST1:
	scanf("%d", &TSTopt);
	fflush(stdin);

	if (TSTopt != Tubular && TSTopt != Annular && TSTopt != Bundle)
	{
		if (TSTopt == 0)
		{
			exit(1);
		}
		else {
			printf("\n .......................................  Error Re-enter Selection ==>  ");
			goto TST1;
		}
	}
	else {
		system("cls");
	}
}

void ScreenFormat()
{
	/* Screen Format */
	int i = 0, j, k;

	int coloumn[9];

	for (i = 0; i < 9; i++)
	{
		coloumn[i] = i*(Width / 8);
	}


	ConsoleSize();
	gotoxy(0, firstline);

	int div = 5;


	for (i = 0; i < Width; i++)
	{
		printf("-");
	}

	gotoxy(coloumn[0], firstline + 1);
	printf("|");

	gotoxy(coloumn[2], firstline + 1);
	printf("|");

	gotoxy(coloumn[6], firstline + 1);
	printf("|");

	gotoxy(0, firstline + 2);

	for (i = 0; i < Width; i++)
	{
		printf("-");
	}

	for (i = 1; i < (Length - 3); i++)
	{
		gotoxy(0, firstline + 2 + i);
		printf("|");
		gotoxy(coloumn[2], firstline + 2 + i);
		printf("|");
		gotoxy(coloumn[6], firstline + 2 + i);
		printf("|");
	}

	/* Flow Monitoring */
	gotoxy((coloumn[1] + coloumn[0]) / 2, firstline + 1);
	printf(" Flow Monitoring Data ");
	FILE *f1 = fopen("DAQ1Display.txt", "r");
	char Line[32];
	char DAQ1Text[10][32];

	j = 0;

	while (!feof(f1))
	{
		fgets(Line, 32, f1);
		strcpy(DAQ1Text[j], Line);
		j++;
	}
	fclose(f1);

	for (i = 0; i < j; i++)
	{
		gotoxy(coloumn[0] + 2, firstline + 4 + 5 * i);
		printf("%s", DAQ1Text[i]);
	}

	// Assigning Display Arrays
	for (i = 0; i < j; i++)
	{
		DAQ1Disp[i][0] = coloumn[2] - 7;
		DAQ1Disp[i][1] = firstline + 4 + 5 * i;
	}

	/* Bundle Test Section Format */
	if (TSTopt == Bundle)
	{
		
		gotoxy((coloumn[7] + coloumn[6]) / 2, firstline + 1);
		printf("Wall Temperatures (C)");
		gotoxy((coloumn[1] + coloumn[6]) / 2 - 7, firstline + 1);
		printf("Bundle Test Section Thermocouple Data (C)");

		/* Bundle Rods */
		for (i = 1; i < 8; i++)
		{
			gotoxy(coloumn[2] + 4, (4 * i) + 3);
			printf(" ROD %i:", i);
		}

		for (i = 1; i <= 3; i++)
		{
			gotoxy(coloumn[i + 2], 4);
			printf(" Strand %i", i);
		}

		int cntr=0;
		for (i = 1; i < 8; i++)
		{
			for (k = 1; k < 4; k++)
			{
				DAQ2DispB[cntr][0] = coloumn[k + 2] + 4;
				DAQ2DispB[cntr][1] = (4 * i) + 3;
				cntr++;
			}
		}
		

		/* Wall Temperature  */
		gotoxy(coloumn[7] - 3, 1 + 3); printf("[Temp 7]");
		gotoxy(coloumn[7] - 1, 1 + 5); GetXY(&DAQ3Disp[6][0], &DAQ3Disp[6][1]);

		gotoxy((coloumn[6] + coloumn[7]) / 2 + 1, div * 1 + 3); printf("[Temp 2]");
		gotoxy((coloumn[6] + coloumn[7]) / 2 + 1, div * 1 + 5); GetXY(&DAQ3Disp[1][0], &DAQ3Disp[1][1]);

		gotoxy((coloumn[8] + coloumn[7]) / 2 - 7, div * 1 + 3); printf("[Temp 3]");
		gotoxy((coloumn[8] + coloumn[7]) / 2 - 5, div * 1 + 5); GetXY(&DAQ3Disp[2][0], &DAQ3Disp[2][1]);

		gotoxy(coloumn[6] + 5, div * 2 + 3); printf("[Temp 1]");
		gotoxy(coloumn[6] + 7, div * 2 + 5); GetXY(&DAQ3Disp[0][0], &DAQ3Disp[0][1]);

		gotoxy(coloumn[7] + 8, div * 2 + 3); printf("[Temp 4]");
		gotoxy(coloumn[7] + 10, div * 2 + 5); GetXY(&DAQ3Disp[3][0], &DAQ3Disp[3][1]);

		gotoxy((coloumn[6] + coloumn[7]) / 2 + 1, div * 3 + 3); printf("[Temp 6]");
		gotoxy((coloumn[6] + coloumn[7]) / 2 + 3, div * 3 + 5); GetXY(&DAQ3Disp[5][0], &DAQ3Disp[5][1]);

		gotoxy((coloumn[8] + coloumn[7]) / 2 - 7, div * 3 + 3); printf("[Temp 5]");
		gotoxy((coloumn[8] + coloumn[7]) / 2 - 5, div * 3 + 5); GetXY(&DAQ3Disp[4][0], &DAQ3Disp[4][1]);

		gotoxy(coloumn[7] - 3, div * 4 + 3); printf("[Temp 8]");
		gotoxy(coloumn[7] - 1, div * 4 + 5); GetXY(&DAQ3Disp[7][0], &DAQ3Disp[7][1]);

		gotoxy(coloumn[7] - 3, div * 5 + 3); printf("[Temp 10]");
		gotoxy(coloumn[7] - 1, div * 5 + 5); GetXY(&DAQ3Disp[9][0], &DAQ3Disp[9][1]);

		gotoxy(coloumn[7] - 3, div * 6 + 3); printf("[Temp 9]");
		gotoxy(coloumn[7] - 1, div * 6 + 5); GetXY(&DAQ3Disp[8][0], &DAQ3Disp[8][1]);


	} //Annular Test Section
	else if (TSTopt == Annular)
	{


		gotoxy((coloumn[7] + coloumn[6]) / 2, firstline + 1);
		printf("Wall Temperatures (C)");
		gotoxy((coloumn[1] + coloumn[6]) / 2 - 7, firstline + 1);
		printf("Annular Test Section Temperature Data (C)");

		/* Wall Temperatures */
		j = 0;
		for (i = 6; i > 0; i--)
		{
			gotoxy(coloumn[7] - 3, 5 * j + 1 + 5); printf("[Temp %i]", i);
			gotoxy(coloumn[7] - 1, 5 * j + 1 + 7); 
			GetXY(&DAQ2Disp1[i-1][0], &DAQ2Disp1[i-1][1]);
			j++;
		}

		/* Angular Temperature Data */

		gotoxy((coloumn[3] + coloumn[4]) / 2 + 1, 6 * 4 + 3);
		printf("[Temp at 0 degrees]"); 
		gotoxy((coloumn[3] + coloumn[4]) / 2 + 6, 6 * 4 + 5);
		GetXY(&DAQ2Disp2[0][0], &DAQ2Disp2[0][1]);

		gotoxy((coloumn[3] + coloumn[4]) / 2, 6 * 1);
		printf("[Temp at 180 degrees]");
		gotoxy((coloumn[3] + coloumn[4]) / 2 +6, 6 * 1 +2);
		GetXY(&DAQ2Disp2[2][0], &DAQ2Disp2[2][1]);

		gotoxy(coloumn[2] + 3, 6 * 2 + 4);
		printf("[Temp at 270 degrees]");
		gotoxy(coloumn[2] + 9, 6 * 2 + 6);
		GetXY(&DAQ2Disp2[3][0], &DAQ2Disp2[3][1]);

		gotoxy(coloumn[5] - 3, 6 * 2 + 4);
		printf("[Temp at 90 degrees]");
		gotoxy(coloumn[5] +3, 6 * 2 + 6);
		GetXY(&DAQ2Disp2[1][0], &DAQ2Disp2[1][1]);

	} // Tubular Test Section
	else if (TSTopt == Tubular)
	{
		gotoxy((coloumn[7] + coloumn[6]) / 2, firstline + 1);
		printf("");
		gotoxy((coloumn[1] + coloumn[6]) / 2 - 7, firstline + 1);
		printf("Tubular Test Section Temperature Data (C)");
		for (i = 1; i < 7; i++)
		{
			gotoxy(coloumn[2] + 3, 5 * i); printf("[Station %i]", (3 * i) - 2);
			//gotoxy(coloumn[2] + 3, 5 * i + 2), GetXY(&DAQ2Disp[(3 * i) - 2][0], &DAQ2Disp[(3 * i) - 2][1]);
			gotoxy((coloumn[2] + coloumn[5]) / 2 + 3, 5 * i); printf("[Station %i]", (3 * i) - 1);
			//gotoxy((coloumn[2] + coloumn[5]) / 2 + 5, 5 * i + 2), GetXY(&DAQ2Disp[(3 * i) - 1][0], &DAQ2Disp[(3 * i) - 1][1]);
			gotoxy(coloumn[5] + 4, 5 * i); printf("[Station %i]", 3 * i);
			//gotoxy(coloumn[5] + 6, 5 * i +2), GetXY(&DAQ2Disp[(3 * i)][0], &DAQ2Disp[(3 * i)][1]);
		}
		int cntr=0;

		for (i = 1; i < 7; i++)
		{
			for (k = 1; k < 4; k++)
			{
				if (k == 1){ DAQ2Disp[(cntr)][0] = coloumn[2] + 5;
				}
				else if (k == 2){ DAQ2Disp[(cntr)][0] = (coloumn[2] + coloumn[5]) / 2 + 5; }
				else if (k == 3){ DAQ2Disp[(cntr)][0] = (coloumn[5] + 6); }
				DAQ2Disp[(cntr)][1] = 5 * i + 2;
				cntr++;
				
			}
		}
	}


	/* Health Monitoring Tab */
	gotoxy((coloumn[1] + coloumn[6]) / 2, (firstline + 34));
	printf(" Health Monitoring Data ");
	for (i = 1; i < (Width*0.5); i++)
	{
		gotoxy(coloumn[2] + i, (firstline + 33));
		printf("-");
		gotoxy(coloumn[2] + i, (firstline + 35));
		printf("-");
	}

	FILE *f4 = fopen("DAQ4Display.txt", "r");
	char DAQ4Text[10][32];

	j = 0;

	while (!feof(f4))
	{
		fgets(Line, 32, f4);
		strcpy(DAQ4Text[j], Line);
		j++;
	}

	fclose(f4);

	// Room Temperature
	gotoxy(coloumn[2] + 2, (firstline + 35 + 1));
	printf("%s ", DAQ4Text[0]);
	DAQ4Disp[0][0] = (coloumn[3] + 1); DAQ4Disp[0][1] = (firstline + 35 + 1);

	for (i = 1; i < 4; i++)
	{
		// First Row
		gotoxy(coloumn[i + 1] + 8 * (i - 1) + 2, (firstline + 35 + 4 + 1));
		printf("%s ", DAQ4Text[i]);
		DAQ4Disp[i][0] = (coloumn[i + 1] + 10 * (i - 1) + 13); DAQ4Disp[i][1] = (firstline + 35 + 4 + 1);
		
		// Second Row
		gotoxy(coloumn[i + 1] + 8 * (i - 1) + 2, (firstline + 35 + 5 + 5));
		printf("%s ", DAQ4Text[3 + i]);
		DAQ4Disp[3 + i][0] = (coloumn[i + 1] + 10* (i - 1) + 13); DAQ4Disp[3 + i][1] = (firstline + 35 + 5 + 5);
		
		// Third Row
		gotoxy(coloumn[i + 1] + 8 * (i - 1) + 2, (firstline + 35 + 11 + 5));
		printf("%s ", DAQ4Text[6 + i]);
		DAQ4Disp[6 + i][0] = (coloumn[i + 1] + 10 * (i - 1) + 13); DAQ4Disp[6 + i][1] = (firstline + 35 + 11 + 5);
	}

	/* Message Box */
	for (i = 1; i < Width / 4; i++)
	{
		gotoxy((coloumn[6] + i), div * 7 + 2);
		printf("-");
		gotoxy((coloumn[6] + i), div * 7 + 4);
		printf("-");
	}

	gotoxy((coloumn[7] - 4), div * 7 + 3);
	printf("Message Box");
}

void UpdateDisplay()
{
	int i = 0, j, k;
	float n=0;
	for (i = 0; i < DAQ1Outputs; i++)
	{
		gotoxy(DAQ1Disp[i][0], DAQ1Disp[i][1]);
		printf("%.2f", 21.22 + i);
	}

	for (i = 0; i < DAQ4Outputs; i++)
	{
		gotoxy(DAQ4Disp[i][0], DAQ4Disp[i][1]);
		printf("%.2f", 24.22 + i);
	}

	if (TSTopt == Annular)
	{
		for (i = 0; i < DAQ2AOutputsangle; i++)
		{
			gotoxy(DAQ2Disp2[i][0], DAQ2Disp2[i][1]);
			printf("%.2f", 11.11 + i);
		}
		for (i = 0; i < DAQ2AOutputsWall; i++)
		{
			gotoxy(DAQ2Disp1[i][0], DAQ2Disp1[i][1]);
			printf("%.2f",16.215+i);
		}
	}
	else if (TSTopt == Bundle)
	{
		for (i = 0; i < DAQ2BOutputsRods; i++)
		{
			gotoxy(DAQ2DispB[i][0], DAQ2DispB[i][1]);
			printf("%.2f", 67.11 + i);
		}
		for (i = 0; i < DAQ3BOutputsWall; i++)
		{
			gotoxy(DAQ3Disp[i][0], DAQ3Disp[i][1]);
			printf("%.2f", 29.23 + i);
		}
	}
	else if (TSTopt == Tubular)
	{
		for (i = 0; i < DAQ2TOutputs; i++)
		{
			gotoxy(DAQ2Disp[i][0], DAQ2Disp[i][1]);
			printf("%.2f",55.2+i);
		}
	}

}

void main()
{
	
	ConsoleSize();
	start:
	TestSetup();

	ScreenFormat();


	while (!kbhit())
	{
		/*gotoxy(166, 55);
		printf("");*/
		UpdateDisplay();
	}
	
	goto start;


	getch();
}

