1) START
  
2) DECLARE
   int playerX, playerY, timeLimit, sweepCooldown, correctAnswer, trapPositionX, trapPositionY, sweepDuration, fakeDoorPositionX, fakeDoorPositionY, doorPositionX, doorPositionY;
   bool doorReached, trapDetected, sweepActive;

3) READ
   playerX = 0;
   playerY = 0;
   timeLimit = 300;      
   sweepCooldown = 12;   
   sweepActive = false;               
   doorReached = false;
   trapDetected = false;
   trapPositionX[] = {12, 45, 34, 67, 86, 43};
   fakeDoorPositionX[] = {62, 90};
   doorPositionX = 51;
   trapPositionY[] = {12, 45, 34, 67, 86, 43};
   fakeDoorPositionY[] = {62, 90};
   doorPositionY = 51;

4) LOOP BODY
   while (timeLimit > 0 && !doorReached) 
   {
       if ((playerX == trapPositionX) &&  (playerY == trapPositionY))
       {
           timeLimit -= 10;     
           trapDetected = true;
           cout << "-10 seconds";
       }

       // Check if player uses sweeper and cooldown is 0
       if (userInput == 'S' && sweepCooldown == 0) 
       {
           sweepActive = !sweepActive; // Toggle sweeper state
           if (sweepActive) 
           {
               sweepDuration = 2;                
               sweepCooldown = 12;
               cout << "Sweeper activated\n";
           } 
           else 
           {
               cout << "Sweeper is on cooldown\n";
           }
       }

       if (userInput == 'W') { playerY++; }
       else if (userInput == 'A') { playerX--; }
       else if (userInput == 'S') { playerY--; }
       else if (userInput == 'D') { playerX++; }
   
       if ((playerX == (doorPositionX || fakeDoorPositionX)) &&  (playerY == (doorPositionY || fakeDoorPositionY)))     {
           doorReached = true;
       }
       if (sweepCooldown > 0) 
       {
           sweepCooldown--;
       }
   }

5) CONDITIONAL STATEMENT
   if (doorReached) 
   {
       cout << "The question is 98 x 32 whats the answer?\n";
       correctAnswer = 3136;
       int playerAnswer;
       cin >> playerAnswer;

       if (playerAnswer == correctAnswer) 
           {
               if ((playerX == fakeDoorPositionX) && (playerY == fakeDoorPositionY)) 
               {
                   cout << "Thats a fake door\n";
                   playerX = 0;   // Reset player position
		   playerY = 0;
               } 
               else 
               {
                   cout << "Correct! You escaped! Proceed to the next level.\n";
               }
           } 
   } 
   else 
   {
       cout << "Game Over.\n";
   }

6) STOP
   return 0;
   }
