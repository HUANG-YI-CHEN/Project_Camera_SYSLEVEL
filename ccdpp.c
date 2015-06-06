/* All Rights Reserved - 2000 */

/*--------------------------------------------------------------------------*/

#include <assert.h>
#include "ccd.h"
#include "ccdpp.h"

/*--------------------------------------------------------------------------*/

#define SZ_ROW      64
#define SZ_COL      128

/*--------------------------------------------------------------------------*/

static char buffer[SZ_ROW][SZ_COL];
static unsigned rowIndex;
static unsigned colIndex;

/*--------------------------------------------------------------------------*/

void CcdppInitialize() {
    
    rowIndex = -1;
    colIndex = -1;
}

/*--------------------------------------------------------------------------*/

void CcdppCapture(void) {
    
    char bias;
    
    CcdCapture();
    for(rowIndex=0; rowIndex<SZ_ROW; rowIndex++) {
        
        for(colIndex=0; colIndex<SZ_COL; colIndex++) {
            
            buffer[rowIndex][colIndex] = CcdPopPixel();
        }
        
        bias = (CcdPopPixel() + CcdPopPixel()) / 2;     
        for(colIndex=0; colIndex<SZ_COL; colIndex++) {
            
            buffer[rowIndex][colIndex] -= bias;
        }
    }
    rowIndex = 0;
    colIndex = 0;
}

/*--------------------------------------------------------------------------*/

char CcdppPopPixel(void) {
    
    char pixel;
    
    assert( rowIndex != -1 );
    assert( colIndex != -1 );
    
    pixel = buffer[rowIndex][colIndex];
    
    if( ++colIndex == SZ_COL ) {
        
        colIndex = 0;
        if( ++rowIndex == SZ_ROW ) {
            
            colIndex = -1;
            rowIndex = -1;
        }
    }
    return pixel;
}