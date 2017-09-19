//
//  CancerCell.hpp
//  lf-cells
//
//  Created by Work on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#ifndef CancerCell_hpp
#define CancerCell_hpp

#include <stdio.h>
#include "Structs.hpp"
#include "Grid.hpp"

class CancerCell {
private:
    Coordinates cancerCellCoordinates;
    bool cancerCellIsAlive;
    int cancerCellLifeSpan;
    int cancerCellAge;
public:
    CancerCell(int x, int y, Grid &myGrid);
    
    CellState processStep(Grid &myGrid);
    
    Coordinates get_cancerCellCoordinates();
    
    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();
};

#endif /* CancerCell_hpp */
