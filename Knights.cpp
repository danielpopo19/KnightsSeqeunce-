/* 
Daniel Polinski
Decemeber 14, 2018 
*/

#include <vector>
#include <map>
#include <iostream>
using namespace std;

/* 
Here I created a map to store: 
1) the Key 
2) The valid combinations of the Key corresponding to the Knights moves on the keyPad
*/

map<char,vector<char>> Combos =
{
    {'A',{'H', 'L'}},        
    {'B',{'I', 'K', 'M'}},     
    {'C',{'F','J','L','N'}}, 
    {'D',{'G', 'M', 'O'}},     
    {'E',{'H', 'N'}},          
    {'F',{'C','M','1'}},     
    {'G',{'D','N','2'}},     
    {'H',{'A','E','K','O','1','3'}},
    {'I',{'B','L','2'}},     
    {'J',{'C','M','3'}},     
    {'K',{'B','H','2'}},     
    {'L',{'A','C','I','3'}}, 
    {'M',{'B','D','F','J'}}, 
    {'N',{'C','E','G','1'}}, 
    {'O',{'D','H','2'}},     
    {'1',{'F','H','N'}},     
    {'2',{'G','I','K','O'}},
    {'3',{'H','J','L'}}      
};


/* 
This function checks to see if the current characters is a vowel(1) or not(0) 
*/

int isVowel(char temp)
{
  if (temp == 'A' || temp == 'I' || temp == 'O' || temp == 'E') return 1;
  return 0;
} 

/* 
Here we traverse the map until we have dont have anymore digits remaining in our 10-digit sequence. We use a Top-down recursion model and our base case is = 1 when we hit out 10-digit sequence.
*/ 

int findCombos(int clicksRemaining, int VowelsRemaining, vector<char> charCombos){
  int finalResult = 0;
  if (clicksRemaining > 0)
  {
    clicksRemaining = clicksRemaining - 1;
    /* Traverse the vector of the corresponding combos for the selected char */
    for (auto i = charCombos.begin(); i != charCombos.end(); i++)
    {
      int numOfPaths = 0;
      /* 
      Here we check our two conditions:
      1) No vowels remaining OR
      2) The current char is not a vowel and does not affect the sequence. There are times when we have reached the max number of vowels, but the next seqeuence of characters may not include another vowel, still making the 10-digit sequence valid.
      */
      if (VowelsRemaining > 0 || (isVowel(*i) == 0))
      {
        if (clicksRemaining != 0)
          // Recurisvely call the function again with click-1 and Vowels-1 if its a vowel 
          numOfPaths = findCombos(clicksRemaining, VowelsRemaining-isVowel(*i),Combos[*i]);
        else
         /* No more clicks, therefore valid 10-digit sequence */
          numOfPaths= 1;
      }
      finalResult += numOfPaths;
    }
  }
return finalResult;
}

/* Here we iterate through the entire keypad, and pass the corresponding valid combos for the charcters selected */

int findCombos(int clicksRemaining, int VowelsRemaining)
{
  int answer = 0;
  int prev = 0;
  for (auto i = Combos.begin(); i != Combos.end(); ++i)
  {
    answer += findCombos(clicksRemaining-1, VowelsRemaining-isVowel(i->first), Combos[i->first]);
    cout << "All the possible Combos starting at " << i->first << " are " << answer - prev << endl;
    prev = answer;
  }
  return answer;
}

int main()
{
    cout << findCombos(10,2);
    return 0;
}
