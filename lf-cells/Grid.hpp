//
//  Grid.hpp
//  lf-cells
//
//  Created by Work on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include "Structs.hpp"
#include <array>


using namespace std;

class Grid{
private:
    array<array<GridCell, gridSize>, gridSize> grid;
    array<array<GridCell, gridSize>, gridSize> temporaryGrid;
    array<array<GridCell, gridSize>, gridSize> emptyGrid;
    
    void diffuseMatrixDegradingEnzyme();
    void activateMatrixDegradingEnzyme();
    void regenerateExtraCellularMatrix(int step);
public:
    void processChangesInEcmAndMde(int step);
    
    void removeFromPopulation(int x, int y);
    void addToPopulation(int x, int y);
    void addMdeAt(int x, int y);
    
    ChanceToMove getChanceToMoveUsingCoordinates(int x, int y);
    
    void moveMdeNorthFrom(int x, int y);
    void moveMdeEastFrom(int x, int y);
    void moveMdeSouthFrom(int x, int y);
    void moveMdeWestFrom(int x, int y);
    void mdeStaysAt(int x, int y);
    
    float getECMat(int x, int y);
    int getPopulation(int x, int y);
};


#endif /* Grid_hpp */
