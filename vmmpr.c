//==============================================================================
// Author      : Zhenia Steger
// Purpose     : Demonstrate function of page replacement algorithms.
// =============================================================================

// INCLUDE FILES
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// GLOBAL VARIABLE DECLARATIONS
int pageTable[4] = {0,0,0,0};     // ARRAY TO STORE THE PAGE NUMBERS
int inputString[40];              // ARRAY TO HOLD THE INPUT STRING

// PROTOTYPE FUNCTIONS
int FIFO(int pages[], int totalPgs);
int LRU(int pages[], int totalPgs);
int optimalPR(int pages[], int totalPgs);

// MAIN METHOD RUNS THE PROGRAM
int main(int argc, char *argv[]) {

  /* ERROR CHECKING */
  if (argc !=2)
  {
    fprintf(stderr, "Error. Incorrect number of arguments (Needed 1)\n"),
    exit(0);
  }
  /* END ERROR CHECKING */

  // LOCAL VARIABLE DECLARATIONS
  int pageFaultsFIFO = 0;
  int pageFaultsLRU = 0;
  int pageFaultsOPT = 0;

  // PARSING THE INPUT STRING FROM 'argv[1]' TO ARRAY 'inputString'
  char* token;
  int var;
  int i = 0, totalPages = 0;
  char seps[] = ", ";
  token = strtok(argv[1], seps);
  while(token != NULL)
  {
    sscanf(token, "%d", &var);
    inputString[i++] = var;
    token = strtok(NULL, seps);
    totalPages++;
  }

  // CALLING THE FUCNTIONS
  pageFaultsFIFO = FIFO(inputString, totalPages);
  pageFaultsLRU = LRU(inputString, totalPages);
  pageFaultsOPT = optimalPR(inputString, totalPages);

  // OUTPUT
  printf("Page faults with FIFO: %i\n", pageFaultsFIFO);
  printf("Page faults with LRU: %i\n", pageFaultsLRU);
  printf("Page faults with optimal: %i\n", pageFaultsOPT);
} // END OF MAIN

// FIRST IN FIRST OUT REPLACEMENT ALGORITHM
int FIFO(int pages[], int totalPgs)
{
  int pageTable[4] = {0,0,0,0};
  int pageFaultsFIFO = 0; int i, j;
  bool fault = false;
  int index = 0;

  for(i = 0; i<totalPgs; i++)
  {
    for(j = 0; j<4; j++)
    {
      if(pages[i] == pageTable[j])
      {
        fault = false; break;
      }
      else fault = true;
    }
    if(fault == true)
    {
      pageFaultsFIFO++;
      pageTable[index] = pages[i];
      index++;
      index = index % 4;
    }
  }
  return pageFaultsFIFO;
}

// LEAST RECENTLY USED ALGORITHM
int LRU(int pages[], int totalPgs)
{
  int pageTable[4] = {0,0,0,0};
  int usedTime[4] = {0,0,0,0};
  int pageFaultsLRU = 0; int i, j, k, l, max;
  bool fault = false;
  int index = 0;

  pageTable[0]=pages[0];
  for(i = 0; i<totalPgs; i++)
  {
    for(j = 0; j<4; j++)
    {
      if(pages[i] == pageTable[j])
      {
        fault = false;
        for(k=0;k<4;k++)
        {
          usedTime[k]++;
        }
        usedTime[j] = 0;
        break;
      }
      else fault = true;
    }

    if(fault == true)
    {
      pageFaultsLRU++;

      for(l=0; l<4;l++)
      {
        if(usedTime[l]>max)
        {
          max = l;
        }
      }
      pageTable[max] = pages[i];
    }
  }
  return pageFaultsLRU;
}

// OPTIMAL PAGE REPLACEMENT ALGORITHM
int optimalPR(int pages[], int totalPgs)
{
  int pageTable[4] = {0,0,0,0};
  int pageFaultsPR = 0; int i, j, k, l;
  bool fault = false;
  int index = 0;
  int counter = 0;
  int temp = 0;

  for(i = 0; i<totalPgs; i++)
  {
    for(j = 0; j<4; j++)
    {
        if(pages[i] == pageTable[j])
        {
          fault = false; break;
        }
        else fault = true;
    }
    if(fault == true)
    {
      pageFaultsPR++;
      for(k=0;k<4;k++)
      {
        counter = 0;
        for(l=i;l<totalPgs;l++)
        {
          if(pages[l]==pageTable[k])
          {
            break;
          }
          else {
            counter++;
          }
        }
        if(counter > temp)
        {
          index = k;
          temp = counter;
        }
      }
      pageTable[temp] = pages[k];
    }
  }
  return pageFaultsPR;
}
// END OF PROGRAM
