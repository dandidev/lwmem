#include "lwmem/lwmem.h"
#include <stdio.h>

/* Define single region */
uint8_t region_data[1024];
lwmem_region_t region = {
    .start_addr = region_data,
    .size = sizeof(region_data)
};

/* Thread declaration */
static int thread_func(void* arg);

int
main(void) {
    /* Initialize default LwMEM instance with single region */
    if (!lwmem_assignmem(&region, 1)) {
        printf("Could not initialize LwMEM!");
        return -1;
    }
    printf("LwMEM initialized and ready to use!\r\n");

    /* Create multiple threads */
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread_func, NULL, 0, NULL);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread_func, NULL, 0, NULL);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread_func, NULL, 0, NULL);

    /* Sleep to let threads to finish */
    Sleep(1000);
    return 0;
}

/**
 * \brief           Thread function, multiple instances of same thread are executed
 *                  in paralled and created with CreateThread function from OS
 */
static int
thread_func(void* arg) {
    void* ptr, * ptr2;

    /* Allocate memory */
    ptr = lwmem_malloc(24);
    if (ptr == NULL) {
        printf("Could not allocate memory!\r\n");
        return -1;
    }
    printf("Memory allocated at address 0x%p!\r\n", ptr);

    /* Increase its size */
    ptr2 = lwmem_realloc(ptr, 48);
    if (ptr2 == NULL) {
        printf("Could not reallocate existing ptr\r\n");
    } else {
        printf("Memory reallocated at address 0x%p!\r\n", ptr2);
        ptr = ptr2;
        ptr2 = NULL;
    }

    /* Free memory after */
    lwmem_free(ptr);

    return 0;
}
