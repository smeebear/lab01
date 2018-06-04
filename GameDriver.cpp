//	Read in the file in getRange()
//	call readLine()
// 	a_to_i the char array
// 	supply getSecret() with the range
//	Pull those in int getRandom(lower, upper), put into an int
//	main() call play() and loop until the user says 'n'
//	in play(), call getGuess() and processGuess() until processGuess() returns 'EXACT'
//	tell the user how many guesses and what the number was

#if !defined (GUESS_ENUM)
#define GUESS_ENUM
   enum GuessEnum {EXACT, TOO_LOW, TOO_HIGH};
#endif

#include "Text.h"
#include "ReadFile.h"
#include "Random.h"
#include "Keyboard.h"

#include <iostream>
using namespace std;

int getSecret(int* range)
{
   int secret;
   String* instructions = readString("Select a number: ");
   secret = a_to_i(instructions);
   cout << "Number is " << secret << endl;

   if (secret < range[0] || secret > range[1])
   {
   		instructions = readString("Not a valid number, try again: ");
   }

   return secret;
}

int* getRange()
{
   String* fileName = readString("What's the name of the range file?:  ");    //USE getText()!

   ReadFile* rf = createReadFile(getText(fileName));
   String* low = readLine(rf);
   String* high = readLine(rf);

   int lowNum = a_to_i(low);
   int highNum = a_to_i(high);

   int* range = new int[2];
   range[0] = lowNum;
   range[1] = highNum;


   destroyString(low);
   destroyString(high);
   destroyReadFile(rf);
   destroyString(fileName);

   return range;
}

int getGuess(int* range)
{
   int guessedNum = (range[0] + (range[1]-range[0]+1)/2);

   if (guessedNum == 2)
   	guessedNum = 1;

   return guessedNum;
}

GuessEnum processGuess(int guess, int secret)
{
   if (guess == secret)
   {
      return EXACT;
   }
   else if (guess < secret)
   {
      return TOO_LOW;
   }
   else 
   {
      return TOO_HIGH;
   }
}

int play(int* range, int secret)
{
	cout << "I'm in play" << endl;
   int total_guess = 0;
   GuessEnum enumGuess;
   do
   {
      int guess = getGuess(range);
      cout << "I guessed " << guess << endl;
      enumGuess = processGuess(guess, secret);

      if (enumGuess == TOO_HIGH)
      {
      		range[1] = guess;
      }
      else if (enumGuess == TOO_LOW)
      {
      		range[0] = guess;
      }

      total_guess++;
   } while (enumGuess != EXACT);
   return total_guess;
}

int main()
{
   String* n = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");

   while (compare(n, ready_str) != 0)
   {
      destroyString(ready_str);
      
      int* range = new int[2];
      range = getRange();

      int secretNum;
      secretNum = getSecret(range);

      int total_guess;
      total_guess = play(range, secretNum);
      
      delete [] range;

      cout << "I needed " << total_guess << " guesses." << endl;
      cin.ignore();
      ready_str = readString("Are you ready to play again? (y/n) ");
   }

   destroyString(ready_str);
   destroyString(n);
   return 0;
}