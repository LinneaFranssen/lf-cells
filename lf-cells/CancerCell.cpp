//
//  CancerCell.cpp
//  lf-cells
//
//  Created by Work on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#include "CancerCell.hpp"
#include "Structs.hpp"
#include "Settings.hpp"
#include "Grid.hpp"

#include <iostream>
using namespace std;

CancerCell::CancerCell(int x, int y, Grid &myGrid){
//This function, when called, creates a new cancerCell, with the given coordinates, and otherwise default attributes.
    cancerCellCoordinates = {x, y};
    cancerCellLifeSpan = defaultCancerCellLifeSpan;
    cancerCellAge = 0;
    myGrid.addToPopulation(x, y);
}


CellState CancerCell:: processStep(Grid &myGrid){
//This Function processes one time step in the cancerCell's life.
    
    myGrid.addMdeAt(cancerCellCoordinates.x, cancerCellCoordinates.y);
    //Secrete MDE.
    
    myGrid.removeFromPopulation(cancerCellCoordinates.x, cancerCellCoordinates.y);
    //As we're about to move - remove ourseles from the census.
    
    if ( cancerCellAge == cancerCellLifeSpan ) {
    //If cancerCell has reached the end of its lifespan...
        return {false, false, Coordinates()};
        //Report that it's no longer alive.
    }
    else {
    //If cancerCell is not dead...
        
        ChanceToMove chanceToMove = myGrid.getChanceToMoveUsingCoordinates(cancerCellCoordinates.x, cancerCellCoordinates.y);
        //Ask the grid for the cancerCell's chance to move in any given direction.
        //Chances returend are accumulative.
        //E.g. 0-0.1 moves north, 0.1-0.3 moves east, 0.3-0.3 moves south (no chance),
        //0.3-0.5 moves west, 0.5+ doesn't move.
        
        float randomNumber = ((float) rand() / (RAND_MAX));
        if (randomNumber < chanceToMove.north) { moveNorth(); }
        else if (randomNumber < chanceToMove.east) { moveEast(); }
        else if (randomNumber < chanceToMove.south) { moveSouth(); }
        else if (randomNumber < chanceToMove.west) { moveWest(); }
        //Generate a random number between 0 and 1.
        //Move accordingly.
        
        myGrid.addToPopulation(cancerCellCoordinates.x, cancerCellCoordinates.y);
        //having moved, report new location to census.
        
        cancerCellAge++;
        //Having lived for one time step, increment age.
        
        if (cancerCellAge % defaultCancerCellReproductionAge == 0 ){
        //If cancerCell has reached reproduction age - report that a new cancerCell should be created.
            return {true, true, Coordinates() = { cancerCellCoordinates.x, cancerCellCoordinates.y}};
        }
        else{
        //Otherwise, simply report that cell is still alive.
            return {true, false, Coordinates()};
        }
        //In both cases, the cancerCell's new coordinates are also reported.
    }
}

Coordinates CancerCell::get_cancerCellCoordinates(){
//This function returns the coordinates of the cancerCell.
    return cancerCellCoordinates;
}

//cancerCell movement functions below: Simply updates appropriate coordinate value.
void CancerCell::moveNorth(){cancerCellCoordinates.y++; }
void CancerCell::moveEast(){cancerCellCoordinates.x++; }
void CancerCell::moveSouth(){cancerCellCoordinates.y--; }
void CancerCell::moveWest(){cancerCellCoordinates.x--; }
