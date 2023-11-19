# ----------------------------------------------------------------------------
# umm_libc makefile
# (c)2006-2023 by Ralph Hempel, Owen Sound, Canada
# rhempel@hempeldesigngroup.com
#
# This is designed to be included as part of a make system designed
# to be expandable and maintainable using techniques found in:
#
# Managing Projects with GNU Make - Robert Mecklenburg - ISBN 0-596-00610-1
# ----------------------------------------------------------------------------

MODULE := umm_libc

MODULE_PATH := $(call make_current_module_path)
# $(info MODULE_PATH is $(MODULE_PATH))

$(MODULE)_PATH := $(MODULE_PATH)
# $(info $(MODULE)_PATH is $($(MODULE)_PATH))

# ----------------------------------------------------------------------------
# Source file lists go here, C dependencies are automatically generated
# by the compiler using the -m option
#
# You can set up a common source path late in the file
#
# Note that each module gets its own, privately scoped variable for building
# ----------------------------------------------------------------------------

# We need both else a previous definition is used :-) Can we make this an include?

SRC_C :=  
SRC_ASM :=  

SRC_C += ansi/chartab.c
SRC_C += ansi/errlist.c
SRC_C += ansi/isxdigit.c
SRC_C += ansi/isalnum.c
SRC_C += ansi/isalpha.c
SRC_C += ansi/isascii.c
SRC_C += ansi/iscntrl.c
SRC_C += ansi/isdigit.c
SRC_C += ansi/isgraph.c
SRC_C += ansi/islower.c
SRC_C += ansi/isprint.c
SRC_C += ansi/ispunct.c
SRC_C += ansi/isspace.c
SRC_C += ansi/isupper.c 
SRC_C += ansi/locale.c 
SRC_C += ansi/memchr.c
SRC_C += ansi/memcmp.c
SRC_C += ansi/memcpy.c
SRC_C += ansi/memmove.c
SRC_C += ansi/memset.c
SRC_ASM += ansi/setjmp.S 
SRC_C += ansi/strcat.c
SRC_C += ansi/strchr.c
SRC_C += ansi/strcmp.c
SRC_C += ansi/stricmp.c
SRC_C += ansi/strcoll.c
SRC_C += ansi/strcpy.c
SRC_C += ansi/strcspn.c
SRC_C += ansi/strerror.c
SRC_C += ansi/strlen.c
SRC_C += ansi/strncat.c
SRC_C += ansi/strncmp.c
SRC_C += ansi/strncpy.c
SRC_C += ansi/strnlen.c 
SRC_C += ansi/strpbrk.c
SRC_C += ansi/strrchr.c
SRC_C += ansi/strspn.c
SRC_C += ansi/strstr.c
SRC_C += ansi/strtofloat.c
SRC_C += ansi/strtok.c
SRC_C += ansi/strtol.c
SRC_C += ansi/strxfrm.c
SRC_C += ansi/toupper.c
SRC_C += ansi/tolower.c
   
SRC_C += stdio/vfprintf.c
SRC_C += stdio/fclose.c
SRC_C += stdio/feof.c
SRC_C += stdio/ferror.c
SRC_C += stdio/fgetc.c
SRC_C += stdio/fgets.c
SRC_C += stdio/fopen.c
SRC_C += stdio/fprintf.c
SRC_C += stdio/fputc.c
SRC_C += stdio/fputs.c
SRC_C += stdio/fread.c
SRC_C += stdio/fwrite.c
SRC_C += stdio/iob.c
SRC_C += stdio/printf.c
SRC_C += stdio/putchar.c
SRC_C += stdio/puts.c
SRC_C += stdio/sprintf.c
SRC_C += stdio/snprintf.c
SRC_C += stdio/ungetc.c
SRC_C += stdio/vfscanf.c
SRC_C += stdio/sscanf.c

SRC_C += math/powl.c

SRC_C += mathf/acosf.c
SRC_C += mathf/asincosf.c
SRC_C += mathf/asinf.c
SRC_C += mathf/atan2f.c
SRC_C += mathf/atanf.c
SRC_C += mathf/ceilf.c
SRC_C += mathf/cosf.c
SRC_C += mathf/expf.c
SRC_C += mathf/fabsf.c
SRC_C += mathf/floorf.c
SRC_C += mathf/frexpf.c
SRC_C += mathf/ldexpf.c
SRC_C += mathf/log10f.c
SRC_C += mathf/logf.c
SRC_C += mathf/powf.c
SRC_C += mathf/random.c
SRC_C += mathf/sincosf.c
SRC_C += mathf/sinf.c
SRC_C += mathf/sqrtf.c
SRC_C += mathf/tancotf.c
SRC_C += mathf/tanf.c
                                      
#SRC_C += misc/xmodem.c
#SRC_C += misc/checksums.c

# ----------------------------------------------------------------------------
# Set up the module level source and include paths

$(MODULE)_SRCPATH :=
$(MODULE)_SRCPATH += $(MODULE_PATH)/ansi
$(MODULE)_SRCPATH += $(MODULE_PATH)/math
$(MODULE)_SRCPATH += $(MODULE_PATH)/mathf
$(MODULE)_SRCPATH += $(MODULE_PATH)/stdio
$(MODULE)_SRCPATH += $(MODULE_PATH)/misc

$(MODULE)_INCPATH := $(MODULE_PATH)/include

# ----------------------------------------------------------------------------
# Set any module level compile time defaults here

$(MODULE)_CDEFS :=
$(MODULE)_CDEFS += _SYSTEM

$(MODULE)_CFLAGS :=
$(MODULE)_CFLAGS += -nostdinc -Wno-builtin-declaration-mismatch

# ----------------------------------------------------------------------------
# Include the adaptabuild library makefile - must be done for each module!

include $(ADAPTABUILD_PATH)/make/library.mak

# ----------------------------------------------------------------------------
