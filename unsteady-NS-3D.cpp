//My Navier Stokes solution with Two phase VOF solver


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<math.h>
#include <algorithm>
#include <cstring>
#include"source/variables/variables.h"
#include"unsteady_NS3D.h"

int main()
{

	defaultInput(); 	   	//Inputting the values required

	dynamicAllocate();		//dynamically allocates the arrays

	zeroTimeValues();   	//Gives initial values to all the variables and fields at time 0

	stepSize();

	createMesh();

	startCPUClock();

	setting_velocity();
	
	setting_Temperature();

	definePhaseField();

	createFields();
	
	createBlocks();


	while(simulationTime<=endTime)         	//time loop
 	{
	  initialize();

	  syncBufferArrays();
	  
	  if(fixedAdvectionVelocity==1)
	  	fixedVelocity();

	  multiPhase();						//VOF solver

          if(fixedAdvectionVelocity!=1)
	  	simple(); 

	  if(t % writeOutputSteps == 0)
	  writeOutput();           		 		//Outputs values to files

	  shift();		    					//shifts the values to l=0

	  courantNumber();	    				//calculates courant number

	  incrementTime();	    				//increments time variables

	  finalize();

	}


}
