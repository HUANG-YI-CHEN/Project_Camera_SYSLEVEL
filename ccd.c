/* All Rights Reserved - 2000 */

/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>
#include "ccd.h"

/*--------------------------------------------------------------------------*/

#define SZ_ROW      64
#define SZ_COL      (128 + 2)

/*--------------------------------------------------------------------------*/

static FILE *imageFileHandle;
static char buffer[SZ_ROW][SZ_COL];
static unsigned rowIndex;
static unsigned colIndex;

/*--------------------------------------------------------------------------*/

void CcdInitialize(const char *imageFileName) {
    
    assert( imageFileName );
    
    imageFileHandle = fopen(imageFileName, "r");
    
    assert( imageFileHandle );
    
    rowIndex = -1;
    colIndex = -1;
}

/*--------------------------------------------------------------------------*/

void CcdCapture(void) {
    
    int pixel;
    
    assert( imageFileHandle );
    
    rewind(imageFileHandle);
    for(rowIndex=0; rowIndex<SZ_ROW; rowIndex++) {
        
        for(colIndex=0; colIndex<SZ_COL; colIndex++) {
            
            if( fscanf(imageFileHandle, "%i", &pixel) == 1 ) {
                
                assert( pixel >= -128 && pixel <= 127 );
                
                buffer[rowIndex][colIndex] = (char)pixel;
            }
            else {
                
                assert( 0 );
            }
        }
    }
    rowIndex = 0;
    colIndex = 0;
}

/*--------------------------------------------------------------------------*/

char CcdPopPixel(void) {
    
    char pixel;
    
    assert( imageFileHandle );
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