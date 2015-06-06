/* All Rights Reserved - 2000 */

/*--------------------------------------------------------------------------*/

#include <assert.h>
#include "uat.h"
#include "codec.h"
#include "ccdpp.h"
#include "cntrl.h"

/*--------------------------------------------------------------------------*/

#define SZ_ROW          64
#define SZ_COL          128
#define NUM_ROW_BLOCKS  (SZ_ROW / 8)
#define NUM_COL_BLOCKS  (SZ_COL / 8)

/*--------------------------------------------------------------------------*/

static short buffer[SZ_ROW][SZ_COL];

/*--------------------------------------------------------------------------*/

void CntrlInitialize(void) {
    
    assert( SZ_ROW % 8 == 0 );
    assert( SZ_COL % 8 == 0 );
}

/*--------------------------------------------------------------------------*/

void CntrlCaputreImage(void) {
    
    int i, j;
    
    CcdppCapture();
    for(i=0; i<SZ_ROW; i++) {
        
        for(j=0; j<SZ_COL; j++) {
            
            buffer[i][j] = CcdppPopPixel();
        }
    }   
}

/*--------------------------------------------------------------------------*/

void CntrlCompressImage(void) {
    
    const unsigned char QuantShiftTable[8][8] = {
        
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 2, 2 },
        { 2, 2, 2, 2, 2, 2, 2, 3 },
        { 3, 3, 3, 3, 3, 3, 3, 4 },
        { 4, 4, 4, 4, 4, 4, 5, 5 },
        { 5, 5, 5, 5, 6, 6, 6, 6 },
        { 6, 7, 7, 7, 7, 8, 8, 8 }
    };
    int i, j, k, l;
    
    /* part 1 - FDCT */
    for(i=0; i<NUM_ROW_BLOCKS; i++) {
        
        for(j=0; j<NUM_COL_BLOCKS; j++) {
            
            /* push the block and perform FDCT */
            for(k=0; k<8; k++) {
                
                for(l=0; l<8; l++) {
                    
                    CodecPushPixel((char)buffer[i * 8 + k][j * 8 + l]);
                }
            }
            CodecDoFdct();
            
            /* pop the block and store in in buffer */
            for(k=0; k<8; k++) {
                
                for(l=0; l<8; l++) {
                    
                    buffer[i * 8 + k][j * 8 + l] = CodecPopPixel();
                }
            }
        }
    }
    
    /* part 2 - quantization */ 
    for(i=0; i<NUM_ROW_BLOCKS; i++) {
        
        for(j=0; j<NUM_COL_BLOCKS; j++) {
            
            /* quantize the block in place */
            for(k=0; k<8; k++) {
                
                for(l=0; l<8; l++) {
                    
                    buffer[i * 8 + k][j * 8 + l] >>= QuantShiftTable[k][l];
                }
            }
        }
    }
}

/*--------------------------------------------------------------------------*/

void CntrlSendImage(void) {
    
    short temp;
    int i, j;
    
    for(i=0; i<SZ_ROW; i++) {
        
        for(j=0; j<SZ_COL; j++) {
            
            temp = buffer[i][j];
            
            UatSend(((char*)&temp)[0]);    /* send upper byte */
            UatSend(((char*)&temp)[1]);    /* send lower byte */
        }
    }   
}