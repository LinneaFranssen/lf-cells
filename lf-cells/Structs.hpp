//
//  Structs.hpp
//  lf-cells
//
//  Created by Work on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#ifndef Structs_hpp
#define Structs_hpp

#include <stdio.h>
#include "Settings.hpp"


struct Coordinates { int x, y; };
struct ChanceToMove { float north, east, south, west; };
struct GridCell {
    float extraCellularMatrixDensity = initialECMDensity;
    int matrixDegradingEnzymeConcentration = 0;
    int population = 0;
};
struct CellState {bool alive, reproduce; Coordinates coordinates; };

#endif /* Structs_hpp */
