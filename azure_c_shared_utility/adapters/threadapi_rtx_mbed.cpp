// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/xlogging.h"
#include "rtos.h"

DEFINE_ENUM_STRINGS(THREADAPI_RESULT, THREADAPI_RESULT_VALUES);

#define MAX_THREADS 4
#define STACK_SIZE  0x4000

typedef struct _thread
{
    Thread*       thrd;
    osThreadId    id;
    Queue<int, 1> result;
} mbedThread;
static mbedThread threads[MAX_THREADS] = { 0 };

typedef struct _create_param
{
    THREAD_START_FUNC func;
    const void* arg;
    mbedThread *p_thread;
} create_param;


THREADAPI_RESULT ThreadAPI_Create(THREAD_HANDLE* threadHandle, THREAD_START_FUNC func, void* arg)
{
    THREADAPI_RESULT result;
    if ((threadHandle == NULL) ||
        (func == NULL))
    {
        result = THREADAPI_INVALID_ARG;
        LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
    }
    else
    {
        size_t slot;
        for (slot = 0; slot < MAX_THREADS; slot++)
        {
            if (threads[slot].id == NULL)
                break;
        }

        if (slot < MAX_THREADS)
        {
            Thread *thrd = new Thread(osPriorityNormal, STACK_SIZE);
            if (thrd != NULL)  {
                osStatus status = thrd->start(callback(func, arg));
                if (status == osOK) {
                    threads[slot].thrd = thrd;
                    *threadHandle = (THREAD_HANDLE)(threads + slot);
                    result = THREADAPI_OK;
                }
                else {
                    result = THREADAPI_NO_MEMORY;
                    LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
                }
            }
            else {
                result = THREADAPI_NO_MEMORY;
                LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
            }
        }
        else {
            result = THREADAPI_NO_MEMORY;
            LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
        }
    }

    return result;
}

THREADAPI_RESULT ThreadAPI_Join(THREAD_HANDLE thr, int *res)
{
    THREADAPI_RESULT result = THREADAPI_OK;
    mbedThread* p = (mbedThread*)thr;
    if (p)
    {
        osEvent evt = p->result.get();
        if (evt.status == osEventMessage) {
            Thread* t = p->thrd;
            if (res)
            {
                *res = (int)evt.value.p;
            }
            (void)t->terminate();
        }
        else
        {
            result = THREADAPI_ERROR;
            LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
        }
    }
    else
    {
        result = THREADAPI_INVALID_ARG;
        LogError("(result = %s)", ENUM_TO_STRING(THREADAPI_RESULT, result));
    }
    return result;
}

void ThreadAPI_Exit(int res)
{
    mbedThread* p;
    for (p = threads; p < &threads[MAX_THREADS]; p++)
    {
        if (p->id == Thread::gettid())
        {
            p->result.put((int*)res);
            break;
        }
    }
}

void ThreadAPI_Sleep(unsigned int millisec)
{
    //
    // The timer on mbed seems to wrap around 65 seconds. Hmmm.
    // So we will do our waits in increments of 30 seconds.
    //
    const int thirtySeconds = 30000;
    int numberOfThirtySecondWaits = millisec / thirtySeconds;
    int remainderOfThirtySeconds = millisec % thirtySeconds;
    int i;
    for (i = 1; i <= numberOfThirtySecondWaits; i++)
    {
        Thread::wait(thirtySeconds);
    }
    Thread::wait(remainderOfThirtySeconds);
}
