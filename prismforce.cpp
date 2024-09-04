
#include <iostream>
#include <vector>
using namespace std;

const int allEnemies = 11; // Total number of enemies in the chakravyuha

int initialPower; // Initial power of Abhimanyu

//  function to determine if Abhimanyu can pass the chakravyuha
bool canAbhimanyuPass(const vector<int> &enemyPower, int currentEnemy, int currentPower, int skip, int recharge, int enemyBeyond)
{
  // Base case: all enemies are defeated.
  if (currentEnemy == allEnemies)
  {
    return true;
  }

  // Handle enemy attacking from behind
  if (enemyBeyond > 0)
  {
    if (currentPower >= enemyBeyond)
    {
      currentPower -= enemyBeyond;
      enemyBeyond = 0;
    }
    else
    {
      return false; // Abhimanyu does not have enough power to defend against the enemy behind
    }
  }

  bool canPass = false;

  // Option 1: Recharge if available and beneficial
  if (recharge > 0 && currentPower < initialPower)
  {
    canPass = canAbhimanyuPass(enemyPower, currentEnemy, initialPower, skip, recharge - 1, enemyBeyond);
  }

  // Option 2: Skip the current enemy if skips are available
  if (!canPass && skip > 0)
  {
    canPass = canAbhimanyuPass(enemyPower, currentEnemy + 1, currentPower, skip - 1, recharge, enemyBeyond);
  }

  // Option 3: Fight the current enemy if power is sufficient
  if (!canPass && currentPower >= enemyPower[currentEnemy])
  {
    int newEnemyBehind = enemyBeyond; // Preserve current enemy behind state

    if (currentEnemy == 2 || currentEnemy == 6)
    {
      newEnemyBehind = enemyPower[currentEnemy] / 2; // Set up the enemy behind attack
    }

    canPass = canAbhimanyuPass(enemyPower, currentEnemy + 1, currentPower - enemyPower[currentEnemy], skip, recharge, newEnemyBehind);
  }

  return canPass;
}

int main()
{
  vector<int> enemyPower(allEnemies); // Powers of each enemy in the chakravyuha.

  for (int i = 0; i < allEnemies; i++)
  {
    cin >> enemyPower[i];
  }

  int maxSkips, maxRecharges; // Maximum skips and recharges available.
  cin >> initialPower >> maxSkips >> maxRecharges;

  // Ensure skips and recharges do not exceed the number of enemies.
  maxSkips = min(maxSkips, allEnemies);
  maxRecharges = min(maxRecharges, allEnemies);

  // Check if Abhimanyu can successfully cross the chakravyuha.
  if (canAbhimanyuPass(enemyPower, 0, initialPower, maxSkips, maxRecharges, 0))
  {
    cout << "Abhimanyu will be able to cross the chakrvyuha!" << endl;
  }
  else
  {
    cout << "Abhimanyu will not be able to  cross the chakravyuha!" << endl;
  }

  return 0;
}

// Test Case 1 :
// enemyPower=[ 1 2 5 2 1 3 5 8 8 2 1 ]
// power=10
// skip=2
// recharge=2

// output : Abhimanyu will be able to cross the chakrvyuha!

// Test Case 2 :
// enemyPower=[1 2 5 2 1 3 5 8 8 2 9]
// power=10
// skip=2
// recharge=2

// output : Abhimanyu will not be able to  cross the chakravyuha !

// Test Case 3 :
// enemyPower=[5, 7, 8, 4, 3, 6, 5, 9, 10, 4, 2]
// power=6
// skip=1
// recharge=1

// output : Abhimanyu will not be able to  cross the chakravyuha !