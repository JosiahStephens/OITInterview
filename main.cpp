#include <iostream>
#include <vector>
#include <set>

char GetCharInput();
void DisplayBlanks(std::vector<char> charVector);
void DisplayGuessedLetters(std::set<char> letters);
void PlayHangman(std::string word);
bool WordIsSolved(std::vector<char> charVector);
std::set<unsigned int> CheckForLetterInWord(std::string word, char guessedLetter);

int main() {
   // Words for hangman. All words have different lengths.
   std::string words[10] = {"new", "seal", "brick", "cactus", "diagram", "pleasure",
                            "abhorrent","historical", "encouraging", "enthusiastic"};
   // seed the random numbers to be different every time the program is run
   srand(time(nullptr));

   std::cout << "Welcome to hangman!" << std::endl;
   bool playAgain = true;
   while (playAgain) {
      // Randomly select word
      std::string word = words[rand() % 10];
      std::cout << "This time you have a " << word.size() << " letter word." << std::endl;
      PlayHangman(word);

      // See if the user would like to play again. If so, set play again to true.
      playAgain = false;
      std:: cout << "Would you like to play again? (y for yes, other characters for no)\n";
      if (GetCharInput() == 'y') {
         playAgain = true;
      }
   }

   std::cout << "\n\nThanks for playing!";

   return 0;
}

// gets string input from user
char GetCharInput() {
   std::string input;
   char inputChar;
   std::getline(std::cin, input);
   // Basic input checking for only a character
   if (input.size() != 1) {
      std::cout << "Please only type one character! Try again:\n";
      input = GetCharInput();
   }
   inputChar = tolower(input.at(0));
   return inputChar;
}

// Displays the letters and blanks of the word
void DisplayBlanks(std::vector<char> charVector) {
   std::cout << "Word:\n";
   for(char i : charVector) {
      std::cout << i << " ";
   }
   std::cout << "\n\n";
}

// Displays the letters that have been previously guessed
void DisplayGuessedLetters(std::set<char> letters) {
   std::cout << "Already guessed letters:\n";
   for (const char &letter : letters) {
      std::cout << letter << " ";
   }
   std::cout << "\n";
}

// Plays one hangman game
void PlayHangman(std::string word) {
   // This vector will be used to store the letters that are guessed in the word
   std::vector<char> blanks;
   for (unsigned int i = 0; i < word.size(); i++) {
      blanks.push_back('_');
   }
   // counters
   int correctGuesses = 0;
   int incorrectGuesses = 0;
   // This set will contain every letter guess
   std::set<char> guesses;

   DisplayBlanks(blanks);
   while(!WordIsSolved(blanks)) {
      std::cout << "\n*******\nGuess a letter: ";
      char letter = GetCharInput();
      std::cout << "\n";
      // character is not a letter
      if (!isalpha(letter)) {
         std::cout << "You must enter a letter!" << std::endl;
      }
      // the letter has already been guessed
      else if (guesses.find(letter) != guesses.end()) {
         std::cout << "You've already guessed " << letter << ".\n";
      }
      // the player guesses a new letter
      else {
         guesses.insert(letter);
         std::set<unsigned int> indicesInWord = CheckForLetterInWord(word, letter);
         if (indicesInWord.size() > 0) {
            // change blank for each index in the word that has the letter that was guessed
            for(const unsigned int &index : indicesInWord) {
               blanks.at(index) = letter;
            }
            correctGuesses++;
         }
         else {
            incorrectGuesses++;
         }
         // Display info
         DisplayBlanks(blanks);
         DisplayGuessedLetters(guesses);
         std::cout << "Correct Guesses: " << correctGuesses <<
            "\tIncorrect Guesses: " << incorrectGuesses;
      }
   }
   int totalGuesses = incorrectGuesses + correctGuesses;
   std::cout << "\nWell done! — Number of guesses it took: " << totalGuesses << "\n";
}

// Sees if there are any letters left that haven't been guessed.
bool WordIsSolved(std::vector<char> charVector) {
   for (char i : charVector) {
      if (i == '_') {
         return false;
      }
   }
   return true;
}

// Sees if the letter is in the word. Returns a set of the indices that have that letter
std::set<unsigned int> CheckForLetterInWord(std::string word, char guessedLetter) {
   std::set<unsigned int> indices;
   for(unsigned int i = 0; i < word.size(); i++) {
      if (word.at(i) == guessedLetter) {
         indices.insert(i);
      }
   }
   return indices;
}
