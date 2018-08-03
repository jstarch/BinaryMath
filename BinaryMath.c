/*	Jennifer Starcher
	jstarch
	ECE 2220
	Spring Semester 2017
	Program 1
	Purpose: Solve the entered binary equations of addition, subtraction, multiplication, and division until the user quits the program.
	Assumptions: The inputted binary numbers will be positive, contain only ones and zeros, have no decimal places, and have a larger number first when using the subtraction operation.
*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

// The Accepted function tests whether inputted binary numbers are valid.
int Accepted(char Op[], int Size)
{
	int Accepted = 0, Check = 0, C = 0; 
	for(C = 0; C <= Size; ++C)
	{
		if(Op[C] == '1' || Op[C] == '0')
		{
			++Check;
		}
	}
	if(Check != 0 && Size <= 31)
	{
		Accepted = 1;
	}
	return Accepted;
}

// The Conversion function converts binary numbers to a decimal number.
long Conversion(char Bin[], int SizeOf)
{
	long Num = 0, x = 0, y = 0;
	for(x = SizeOf - 1; x >= 0; x--)
	{
		if(Bin[x] == '1')
		{	
			Num = Num + pow(2, y);
		}
		y++;
	}
	return Num;
}

int main(void) 
{
	// Declaration of variables.
	char Op1[31];
	char Operation;
	char Op2[31];

	int Size1;
	int Size2;

	int Valid;

	long Num1;
	long Num2;
	double Answer;
	double Remainder;

	int Binary[63];
	int LengthBin;

	char Continue[10] = "Continue";
	int Length;
	int i;
	int j;

	// While loop to continue the program until the user enters quit.
	while(strcmp(Continue, "quit") != 0)
	{
		// Do-While loop to continue to ask the user for an input until it is valid.
		do
		{
			Valid = 0;
			Num1 = 0;
			Num2 = 0;

			// Input from the user.
			printf("\nEnter the Operand1 Operation Operand2: \n");
			scanf("%s", Op1);
			Size1 = strlen(Op1);
			scanf(" %c", &Operation);
			scanf("%s", Op2);
			Size2 = strlen(Op2);
	
			// Call to Accepted function to test the binary inputs.
			Valid = Valid + Accepted(Op1, Size1);
			Valid = Valid + Accepted(Op2, Size2);

			// If statement to test whether the inputted operator is valid.
			if(Operation == '+' || Operation == '-' || Operation == '*' || Operation == '/')
			{
				++Valid;
			}
			
			// If statement to print an error if the input is not valid.
			if(Valid != 3)
			{
				printf("\nERROR: Input Two binary numbers of less than 31 bits separated by a valid operator (+, -, *, or /).");
			}

		}while(Valid != 3);	
		
		// Call to Conversion function to convert the user's binary to decimal values.
		Num1 = Conversion(Op1, Size1);
		Num2 = Conversion(Op2, Size2);
		
		// Finds the maximum size of the two binary numbers for the outputted binary length 
		if(Size1 > Size2)
		{
			LengthBin = Size1;
		}
		else
		{
			LengthBin = Size2;
		}

		// Switch used to do the desired mathematical operation.
		switch(Operation)
		{
			case '+':
				Answer = Num1 + Num2; 
				break;
			case '-':
				Answer = Num1 - Num2;
				break;
			case '*':
				Answer = Num1 * Num2;
				LengthBin = Size1 + Size2 + 1; // In mulitplication the output will be larger bit-wise than the largest input size.
				break;
			case '/': 
				Answer = (double)Num1 / (double)Num2;
				break;
			default:
				Answer = 0;
				break;
		}

		// Finds the floating point of Answer and separates it for Answer to be used later.
		Remainder = Answer - (int)Answer;
		
		// Conversion of Answer from decimal to binary.
		for(i = LengthBin; i >= 0; i--)
		{
			j = (int) ((long)Answer % 2);
			Answer = Answer / 2;
			Binary[i] = j;
		}		
		
		// Ouput to the user.
		printf("= ");
		for(i = 0; i <= LengthBin; i++)
		{
			printf("%d", Binary[i]);
		}

		// Binary floating point values of Answer.
		if(Operation == '/')
		{			
			j = -1; // Binary after a decimal point starts at 2 to the power of -1.
			
			// For loop to find the binary values after the decimal point.
			for(i = LengthBin + 5; i > LengthBin + 1; i--)
			{
				if((Remainder / pow(2, j)) >= 1)
				{
					Binary[i] = 1;
					Remainder = Remainder - pow(2, j);
				}
				else
				{
					Binary[i] = 0;
				}
				j--;
			}

			// Output to the user.
			printf(".");
			for(i = LengthBin + 5; i > LengthBin + 1; i--)
			{
				printf("%d", Binary[i]);
			}
		}

		
		// Input from the user on whether to continue or quit.
		printf("\n\nContinue or Quit? ");
		scanf("%s", Continue);
		
		// For loop changes all of the user's entered to lower case, so it isn't case sense to the user.
		Length = strlen(Continue);
		for(i = 0; i <= Length; i++) 
		{
			Continue[i] = tolower(Continue[i]);
		}
		
		
	}
	
	printf("\nGoodbye.\n\n");
	
	return 0;
}


