//
//  Grid.cpp
//  lf-cells
//
//  Created by Work on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#include "Grid.hpp"
#include "Settings.hpp"
#include <iostream>
#include <cmath>

void Grid::processChangesInEcmAndMde(int step){
//This function is simply a call to the three following functions.
    regenerateExtraCellularMatrix(step);
    activateMatrixDegradingEnzyme();
    diffuseMatrixDegradingEnzyme();
}

void Grid::diffuseMatrixDegradingEnzyme(){
//This function visits every gridCell, then instructs each MDE to move depending on chance defined in settings.hpp
//The movements, along with the grid's other variables are stored in a temporary grid while calculating the movements.
//This will no longer be neccesary when MDE code is developed further.
    for (int x = 0; x < gridSize; x++){
        for (int y = 0; y < gridSize; y++){
            for (int mdeInCell = grid[x][y].matrixDegradingEnzymeConcentration; mdeInCell > 0; mdeInCell --){
                int randomNumber = rand()%mdeMovementChance;
                switch (randomNumber){
                    case 0: moveMdeNorthFrom(x, y); break;
                    case 1: moveMdeEastFrom(x, y); break;
                    case 2: moveMdeSouthFrom(x, y); break;
                    case 3: moveMdeWestFrom(x, y); break;
                    default: mdeStaysAt(x, y);
                }
            }
            temporaryGrid[x][y].extraCellularMatrixDensity = grid[x][y].extraCellularMatrixDensity;
            temporaryGrid[x][y].population = grid[x][y].population;
        }
    }
    grid = temporaryGrid;
    temporaryGrid = emptyGrid;
}

void Grid::regenerateExtraCellularMatrix(int step){
//This function regenerates ECM density in each gridCell once per step. This is currently linear.
//It also currently deletes one MDE per stepsPerMdeDegredation, as defined in settings.hpp
//This behaviour will change when MDE is developed further.
    for (int x = 0; x < gridSize; x++){
        for (int y = 0; y < gridSize; y++){
            if (grid[x][y].extraCellularMatrixDensity + ecmRegenerationPerStep <= 1) { grid[x][y].extraCellularMatrixDensity += ecmRegenerationPerStep;};
            if (grid[x][y].matrixDegradingEnzymeConcentration > 0 && step % stepsPerMdeDegredation == 0) { grid[x][y].matrixDegradingEnzymeConcentration --;};
        }
    }
}

void Grid::activateMatrixDegradingEnzyme(){
//This function, depending on the MDE concentration in each grid cell will degrade the ECM density by rateAtWhichMDEEffectsECM^(MDEConcetration).
    for (int x = 0; x < gridSize; x++){
        for (int y = 0; y < gridSize; y++){
            grid[x][y].extraCellularMatrixDensity *= pow(rateAtWhichMdeEffectsECM, grid[x][y].matrixDegradingEnzymeConcentration);
        }
    }
}

ChanceToMove Grid::getChanceToMoveUsingCoordinates(int x, int y){
//This function returns the likelihood of a cancerCell moving in a direction, based on ECM gradient, the overall chance to move in perfect conditions, and walls.
    float chanceToMoveNorth = 0, chanceToMoveEast = 0, chanceToMoveSouth = 0, chanceToMoveWest = 0;
    
    if (y+1 != gridSize && grid[x][y+1].population < maxPopulation) {
        chanceToMoveNorth = ( grid[x][y+1].extraCellularMatrixDensity - grid[x][y].extraCellularMatrixDensity + 1) / 2 * chanceCancerCellWillMoveInOneDirection;
    }
    if (x+1 != gridSize && grid[x+1][y].population < maxPopulation) {
        chanceToMoveEast  = chanceToMoveNorth + ( grid[x+1][y].extraCellularMatrixDensity - grid[x][y].extraCellularMatrixDensity + 1) / 2 * chanceCancerCellWillMoveInOneDirection;
    }
    if (y-1!= -1 && grid[x][y-1].population < maxPopulation) {
        chanceToMoveSouth = chanceToMoveEast  + ( grid[x][y-1].extraCellularMatrixDensity - grid[x][y].extraCellularMatrixDensity + 1) / 2 * chanceCancerCellWillMoveInOneDirection;
    }
    if (x-1!= -1 && grid[x-1][y].population < maxPopulation) {
        chanceToMoveWest  = chanceToMoveSouth + ( grid[x-1][y].extraCellularMatrixDensity - grid[x][y].extraCellularMatrixDensity + 1) / 2 * chanceCancerCellWillMoveInOneDirection;
    }
    
    return {chanceToMoveNorth, chanceToMoveEast, chanceToMoveSouth, chanceToMoveWest};
}

//The 5 following functions define the positions of MDE within the new grid's cells.
void Grid::moveMdeNorthFrom(int x, int y){ if( y + 1 != gridSize)   { temporaryGrid[x][y+1].matrixDegradingEnzymeConcentration ++; } }
void Grid::moveMdeEastFrom(int x, int y) { if( x + 1 != gridSize)   { temporaryGrid[x+1][y].matrixDegradingEnzymeConcentration ++; } }
void Grid::moveMdeSouthFrom(int x, int y){ if( y - 1 != 0)          { temporaryGrid[x][y-1].matrixDegradingEnzymeConcentration ++; } }
void Grid::moveMdeWestFrom(int x, int y) { if( x - 1 != 0)          { temporaryGrid[x-1][y].matrixDegradingEnzymeConcentration ++; } }
void Grid::mdeStaysAt(int x, int y)                                 { temporaryGrid[x][y].matrixDegradingEnzymeConcentration ++; }

//The 3 following functions are used by cancerCells to record their location, and to secrete MDE.
void Grid::removeFromPopulation(int x, int y){ grid[x][y].population --; }
void Grid::addToPopulation(int x, int y){ grid[x][y].population ++; }
void Grid::addMdeAt(int x, int y){ grid[x][y].matrixDegradingEnzymeConcentration += 1; }

//The 2 following functions are used by the printFrame function in main.cpp.
int Grid::getPopulation(int x, int y){ return grid[x][y].population; }
float Grid::getECMat(int x, int y){ return grid[x][y].extraCellularMatrixDensity; }
