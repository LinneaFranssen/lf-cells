//
//  main.cpp
//  lf-cells
//
//  Created by Jack Nichol on 29/08/2017.
//  Copyright © 2017 Jack Nichol. All rights reserved.
//

#include "main.hpp"
#include <fstream>

void printFrame(int i, Grid&theGrid);
//Initialise function to output one frame.

int main() {
    
    srand(uint(time(NULL)));
    //This line allows rand() to provide a 'more random' number.
    
    Grid theGrid;
    //Initialise the Grid, which the cancer cells will live in.
    
    vector<CancerCell> cancerCells;
    //Initialise a container for the cancer cells.
    
    cout << '[';
    
    for(int i = 0; i < initialNumberOfCancerCells; i++){
        cancerCells.push_back(CancerCell(middleOfGrid, middleOfGrid, theGrid));
    }
    //Create a cancerCell in the cancerCells container at position (middleOfGrid, MiddleOfGrid) on theGrid.
    //Do this initialNumberOfCancerCells times.
    
    for (int i = 0; i < numberOfStepsToSimulate; i++){
        //Loop for numberOfTimeStepsToSimulate.
        
        int offsetToAccountForDeaths = 0;
        //Some cancer cells will die in the following loop.
        //This will change the position of other cancer cells within the container.
        //This variable allows us to offset this discrepency, and target the intended cancer cell.
        
        CellState cellState;
        //This variable will allow us to store the state a cell, and then act accordingly.
        
        for (int cancerCell = 0; cancerCell < cancerCells.size(); cancerCell++){
        //For each cancerCell in the CancerCells container...
            
            cellState = cancerCells[cancerCell-offsetToAccountForDeaths].processStep(theGrid);
            //Process one step in a cancerCell's life. Store its state in cellState.
            
            if (cellState.alive){
                if (cellState.reproduce) {
                    cancerCells.push_back(CancerCell(cellState.coordinates.x, cellState.coordinates.y, theGrid));
                }
                //If cancerCell is still alive, and is ready to reproduce - create new cancerCell parent's coordinates.
            }
            else {
                cancerCells.erase(cancerCells.begin() + cancerCell - 1 - offsetToAccountForDeaths);
                offsetToAccountForDeaths ++;
                //If cancerCell is not alive, kill cancerCell, and adjust offset.
            }
        }
        
        theGrid.processChangesInEcmAndMde(i);
        //Regenerate ECM, activate MDE, defuse Mde.
        
        printFrame(i, theGrid);
        //Output one frame of cancerCell positions and ECM concentration.
        
        if (i % percentOfSteps == 0){
            cout << '-';
            if ((i/percentOfSteps + 1) % 20 == 0) { cout << ']' << (i/percentOfSteps+1)<< '%' << endl << '[';}
        }
        //Ouput completion percentage.
    }

    return 0;

}



void printFrame(int i, Grid &theGrid) {
    if (i % stepsBetweenFrames == 0){
        int data [imageWidth][imageHeight];
        for (int x = 0; x < gridWidth; x++){
            for (int y = 0; y < gridHeight; y++){
                data[x][y] = theGrid.getPopulation(x, y);
                if (data[x][y] > 0 ) data[x][y] += imageDepth/2;
                data[x][y+gridHeight] = int(theGrid.getECMat(x, y)*imageDepth);
            }
        }
        
        ofstream frame;
        frame.open ("frame_" + to_string(i/stepsBetweenFrames) + ".pgm");
        frame << "P2\n" + to_string(imageWidth) + ' ' + to_string(imageHeight) + '\n' + to_string(imageDepth) + '\n';
        for (int y = 0; y < imageHeight; y++){
            for (int x = 0; x < imageWidth; x++){
                frame << data[x][y] << ' ';
            }
            frame << '\n';
        }
        frame.close();
    }
}

