/* All Rights Reserved - 2000 */

/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <assert.h>

/*--------------------------------------------------------------------------*/

static FILE *outputFileHandle;

/*--------------------------------------------------------------------------*/

void UatInitialize(const char *outputFileName) {
    
    assert( outputFileName );
    outputFileHandle = fopen(outputFileName, "w");
    assert( outputFileHandle );
}

/*--------------------------------------------------------------------------*/

void UatSend(char d) {
    
    assert( outputFileHandle);
    fprintf(outputFileHandle, "%i\n", (int)d);
}
