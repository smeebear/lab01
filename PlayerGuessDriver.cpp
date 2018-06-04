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
   randomInit();
   int random = getRandomInt(range[0],range[1]);

   return random;
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
   String* guess = readString("Guess a number: ");
   int guessedNum = a_to_i(guess);

   if (guessedNum < range[0] || guessedNum > range[1])
   {
      guess = readString("That's not in the accepted range. \nGuess a different number: ");
      guessedNum = a_to_i(guess);
   }

   return guessedNum;
}

GuessEnum processGuess(int guess, int secret)
{
   String* output = new String;
   if (guess == secret)
   {
      output = createString("You got it! Good job!\n");
      displayString(output);
      destroyString(output);
      return EXACT;
   }
   else if (guess < secret)
   {
      output = createString("Too low!\n");
      displayString(output);
      destroyString(output);
      return TOO_LOW;
   }
   else 
   {
      output = createString("Too high!\n");
      displayString(output);
      destroyString(output);
      return TOO_HIGH;
   }
}

int play(int* range, int secret)
{
   int total_guess = 0;
   GuessEnum enumGuess;
   do
   {
      int guess = getGuess(range);
      enumGuess = processGuess(guess, secret);
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

      cout << "You got it in " << total_guess << " guesses!" << endl;
      cin.ignore();
      ready_str = readString("Are you ready to play again? (y/n) ");
   }

   destroyString(ready_str);
   destroyString(n);
   return 0;
}
