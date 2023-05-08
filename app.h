//
// Created by sasha on 08.05.2023.
//

#ifndef VISUALSVNTASK_APP_H
#define VISUALSVNTASK_APP_H

#include <stdlib.h>
#include <stdio.h>
#include "exception_s.h"

enum app_errors {
    NULL_POINTER_ERROR = 0x0fff
};

int app_start(char *in_name, char *out_name, exception_s *exception);

#endif //VISUALSVNTASK_APP_H
