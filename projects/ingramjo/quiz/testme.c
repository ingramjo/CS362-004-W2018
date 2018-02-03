#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    	//Creates random character variable
	char random_character;

	//Generates the randpm character with the ASCII range 0 - 255
	random_character = (char)rand() % 256;
	return random_character;
}

char *inputString()
{
	//Create iterator
	int iter = 0;

	//Create char array that will store random string
	static char random_string[6];

	//Create temporary string that has all characters used
	char temp_string[] = "[({ax})]reset";

	//Initialize random string to Null
	memset(random_string, '\0', sizeof(random_string));

	while(iter < 5){
	//Populate random string 
		random_string[iter++] = temp_string[rand() % 13];
	}

	return random_string;
}

void testme()
{
  	int tcCount = 0;
  	char *s;
  	char c;
  	int state = 0;
  	while (1)
  	{
    		tcCount++;
    		c = inputChar();
    		s = inputString();
    		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    		if (c == '[' && state == 0) state = 1;
    		if (c == '(' && state == 1) state = 2;
    		if (c == '{' && state == 2) state = 3;
    		if (c == ' ' && state == 3) state = 4;
    		if (c == 'a' && state == 4) state = 5;
    		if (c == 'x' && state == 5) state = 6;
    		if (c == '}' && state == 6) state = 7;
    		if (c == ')' && state == 7) state = 8;
    		if (c == ']' && state == 8) state = 9;
    		if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
    		{
      			printf("error ");
      			exit(200);
    		}
  	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
