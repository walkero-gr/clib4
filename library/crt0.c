/*
 * $Id: crt0.c,v 1.0 2022-10-28 12:04:22 clib2devs Exp $
*/

#include "stdlib_headers.h"
#include "stdio_headers.h"
#include "unistd_headers.h"
#include "debug_headers.h"

extern int _main(struct ExecBase *sysBase);
extern int main(int arg_c, char **arg_v);
extern struct Library *__ElfBase;
extern struct ElfIFace *__IElf;
extern jmp_buf NOCOMMON __exit_jmp_buf;

int _start(char *args, int arglen, struct ExecBase *sysBase);
BOOL open_libraries(void);

#define MIN_OS_VERSION 52

BOOL
open_libraries(void) {
    BOOL success = FALSE;

    /* Open the minimum required libraries. */
    DOSBase = (struct Library *) OpenLibrary("dos.library", MIN_OS_VERSION);
    if (DOSBase == NULL)
        goto out;

    __UtilityBase = OpenLibrary("utility.library", MIN_OS_VERSION);
    if (__UtilityBase == NULL)
        goto out;

    /* Obtain the interfaces for these libraries. */
    IDOS = (struct DOSIFace *) GetInterface(DOSBase, "main", 1, 0);
    if (IDOS == NULL)
        goto out;

    __IUtility = (struct UtilityIFace *) GetInterface(__UtilityBase, "main", 1, 0);
    if (__IUtility == NULL)
        goto out;

    /* We need elf.library V52.2 or higher. */
    __ElfBase = OpenLibrary("elf.library", 0);
    if (__ElfBase == NULL || (__ElfBase->lib_Version < MIN_OS_VERSION) ||
        (__ElfBase->lib_Version == MIN_OS_VERSION && __ElfBase->lib_Revision < 2))
        goto out;

    __IElf = (struct ElfIFace *) GetInterface(__ElfBase, "main", 1, NULL);
    if (__IElf == NULL)
        goto out;

    success = TRUE;

out:

    return (success);
}

int _start(char *args, int arglen, struct ExecBase *sysBase) {
    (void) args;
    (void) arglen;
    (void) sysBase;
    int result = ERROR;

    IExec = (struct ExecIFace *) ((struct ExecBase *) sysBase)->MainInterface;

    if (CANNOT open_libraries()) {
        const char *error_message;

        /* If available, use the error message provided by the client. */
        error_message = __minimum_os_lib_error;

        if (error_message == NULL)
            error_message = "This program requires AmigaOS 4 (52.2) or higher.";

        __show_error(error_message);
        goto out;
    }

    reent_init();

    /* This plants the return buffer for _exit(). */
    if (setjmp(__exit_jmp_buf) != 0) {
        goto out;
    }

    SHOWMSG("now invoking the constructors");
    /* Go through the constructor list */
    _init();

    result = _main(sysBase);

out:
    return result;
}