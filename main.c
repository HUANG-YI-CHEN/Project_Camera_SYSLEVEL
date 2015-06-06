/* All Rights Reserved - 2000 */

/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>
#include "uat.h"
#include "ccd.h"
#include "ccdpp.h"
#include "codec.h"
#include "cntrl.h"

/*--------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    
    char *uatOutputFileName = argc > 2 ? argv[2] : "uat_out.txt";
    char *imageFileName = argc > 3 ? argv[3] : "image.txt";
    
    /* initialize the models */
    UatInitialize(uatOutputFileName);
    CcdInitialize(imageFileName);
    CcdppInitialize();
    CodecInitialize();
    CntrlInitialize();
    
    /* simulate functionality */
    CntrlCaputreImage();
    CntrlCompressImage();
    CntrlSendImage();
}
