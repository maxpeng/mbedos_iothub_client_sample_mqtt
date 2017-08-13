#include "azure_retarget.h"


#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
    int errno;
#endif
