//
//  Settings.hpp
//  lf-cells
//
//  Created by Work on 14/09/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#ifndef Settings_h
#define Settings_h

//Settings
const float initialECMDensity = 0.5;            //Should be set between 0 and 1.
const int gridSize = 100;                       //Grid is a square of size gridSize x gridSize
const int initialNumberOfCancerCells = 100;
const int thousandsOfStepsToSimulate = 1;       //Note - Thousands of steps. Not number of steps.

const int defaultCancerCellLifeSpan = 100;
const int defaultCancerCellReproductionAge = 100;
const float chanceCancerCellWillMove = 0.1;     //Assuming perfect conditions. Should be set between 0 & 1;

const float chanceMdeWillMoveByDefusion = 0.1;  //Should be set between 0 and 1;
const float ecmRegenerationPerStep = 0.005;     //Currently linear. ECM density will increase by 0.005 each step, to a maximum of 1
const int stepsPerMdeDegredation = 20;          //Currently gridCell dependant, not mdeDependant. With value 10, each gridCell will delete one resident MDE per 10 steps.
const int imageDepth = 100;                       //Bitdepth of images generated. This will not be the final visual output - it's simply the easiest to implement for testing.
const float rateAtWhichMdeEffectsECM = 0.99;    //Each step, each gridCell will: ECM = ECM * thisValue^MDEConcentration
const int maxPopulation = 1000;                   //Maximum number of cancerCells in one grid square.


//Derived settings for readibility.
//THESE SETTINGS SHOULD NOT BE CHANGED.
const int gridWidth = gridSize;
const int gridHeight = gridSize;
const int middleOfGrid = gridSize/2;
//THESE SETTINGS SHOULD NOT BE CHANGED.
const int numberOfStepsToSimulate = thousandsOfStepsToSimulate * 1000;
const int percentOfSteps = numberOfStepsToSimulate / 100;
//THESE SETTINGS SHOULD NOT BE CHANGED.
const int imageWidth = gridSize;
const int imageHeight = gridSize * 2;
const int stepsBetweenFrames = thousandsOfStepsToSimulate;
//THESE SETTINGS SHOULD NOT BE CHANGED.
const float chanceCancerCellWillMoveInOneDirection = chanceCancerCellWillMove / 4;
const int mdeMovementChance = (1/chanceMdeWillMoveByDefusion)*4;
//THESE SETTINGS SHOULD NOT BE CHANGED.

#endif /* Settings_h */
