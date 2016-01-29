#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"

typedef enum {
    NOT_PROCESSED = 0,
    IN_PROCESSING,
    PROCESSED,
} state ;
