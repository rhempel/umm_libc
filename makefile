# ----------------------------------------------------------------------------
# libc makefile
# (c)2006 by Ralph Hempel, Owen Sound, Canada
# rhempel@hempeldesigngroup.com
#
# This is designed to be included as part of a make system designed
# to be expandable and maintainable using techniques found in:
#
# Managing Projects with GNU Make - Robert Mecklenburg - ISBN 0-596-00610-1
# ----------------------------------------------------------------------------

MODULE_PATH := libc
MODULE      := libc

# ----------------------------------------------------------------------------
# Make sure that we have source files to support the MCU, MCUVAR, and BOARD

SUPPORTED_MCU    := arm7tdmi
SUPPORTED_MCUVAR := AT91SAM7S256
SUPPORTED_BOARD  := NXT

$(call check-module-support,MCU,$(SUPPORTED_MCU))
$(call check-module-support,MCUVAR,$(SUPPORTED_MCUVAR))
$(call check-module-support,BOARD,$(SUPPORTED_BOARD))

# ----------------------------------------------------------------------------
# Source file lists go here
# C dependencies are automatically generated
# Use file-extension c for c-only-files
# ----------------------------------------------------------------------------

SRC_THUMB :=  

SRC_THUMB += ansi/chartab.c
SRC_THUMB += ansi/errlist.c
SRC_THUMB += ansi/isxdigit.c
SRC_THUMB += ansi/isalnum.c
SRC_THUMB += ansi/isalpha.c
SRC_THUMB += ansi/isascii.c
SRC_THUMB += ansi/iscntrl.c
SRC_THUMB += ansi/isdigit.c
SRC_THUMB += ansi/isgraph.c
SRC_THUMB += ansi/islower.c
SRC_THUMB += ansi/isprint.c
SRC_THUMB += ansi/ispunct.c
SRC_THUMB += ansi/isspace.c
SRC_THUMB += ansi/isupper.c 
SRC_THUMB += ansi/locale.c 
SRC_THUMB += ansi/memchr.c
SRC_THUMB += ansi/memcmp.c
SRC_THUMB += ansi/memcpy.c
SRC_THUMB += ansi/memmove.c
SRC_THUMB += ansi/memset.c
SRC_THUMB += ansi/setjmp.S 
SRC_THUMB += ansi/strcat.c
SRC_THUMB += ansi/strchr.c
SRC_THUMB += ansi/strcmp.c
SRC_THUMB += ansi/stricmp.c
SRC_THUMB += ansi/strcoll.c
SRC_THUMB += ansi/strcpy.c
SRC_THUMB += ansi/strcspn.c
SRC_THUMB += ansi/strerror.c
SRC_THUMB += ansi/strlen.c
SRC_THUMB += ansi/strncat.c
SRC_THUMB += ansi/strncmp.c
SRC_THUMB += ansi/strncpy.c
SRC_THUMB += ansi/strnlen.c 
SRC_THUMB += ansi/strpbrk.c
SRC_THUMB += ansi/strrchr.c
SRC_THUMB += ansi/strspn.c
SRC_THUMB += ansi/strstr.c
SRC_THUMB += ansi/strtofloat.c
SRC_THUMB += ansi/strtok.c
SRC_THUMB += ansi/strtol.c
SRC_THUMB += ansi/strxfrm.c
SRC_THUMB += ansi/toupper.c
SRC_THUMB += ansi/tolower.c
   
SRC_THUMB += stdio/vfprintf.c
SRC_THUMB += stdio/fclose.c
SRC_THUMB += stdio/feof.c
SRC_THUMB += stdio/ferror.c
SRC_THUMB += stdio/fgetc.c
SRC_THUMB += stdio/fgets.c
SRC_THUMB += stdio/fopen.c
SRC_THUMB += stdio/fprintf.c
SRC_THUMB += stdio/fputc.c
SRC_THUMB += stdio/fputs.c
SRC_THUMB += stdio/fread.c
SRC_THUMB += stdio/fwrite.c
SRC_THUMB += stdio/iob.c
SRC_THUMB += stdio/printf.c
SRC_THUMB += stdio/putchar.c
SRC_THUMB += stdio/puts.c
SRC_THUMB += stdio/sprintf.c
SRC_THUMB += stdio/snprintf.c
SRC_THUMB += stdio/ungetc.c
SRC_THUMB += stdio/vfscanf.c
SRC_THUMB += stdio/sscanf.c

SRC_THUMB += math/powl.c

SRC_THUMB += mathf/acosf.c
SRC_THUMB += mathf/asincosf.c
SRC_THUMB += mathf/asinf.c
SRC_THUMB += mathf/atan2f.c
SRC_THUMB += mathf/atanf.c
SRC_THUMB += mathf/ceilf.c
SRC_THUMB += mathf/cosf.c
SRC_THUMB += mathf/expf.c
SRC_THUMB += mathf/fabsf.c
SRC_THUMB += mathf/floorf.c
SRC_THUMB += mathf/frexpf.c
SRC_THUMB += mathf/ldexpf.c
SRC_THUMB += mathf/log10f.c
SRC_THUMB += mathf/logf.c
SRC_THUMB += mathf/powf.c
SRC_THUMB += mathf/random.c
SRC_THUMB += mathf/sincosf.c
SRC_THUMB += mathf/sinf.c
SRC_THUMB += mathf/sqrtf.c
SRC_THUMB += mathf/tancotf.c
SRC_THUMB += mathf/tanf.c
                                      
SRC_THUMB += misc/xmodem.c
SRC_THUMB += misc/checksums.c
SRC_THUMB += misc/umm_malloc.c

# ----------------------------------------------------------------------------
# These objects must be compiled with -O2 so that the copmiler does not get
# too aggressive

SRC_THUMB_O2 :=

# ----------------------------------------------------------------------------
# List object files that must be compiled in ARM mode here

SRC_ARM :=

# ----------------------------------------------------------------------------
# Set up the module level specifics for the source, include, and object paths

$(MODULE)_SRCPATH :=
$(MODULE)_SRCPATH += $(MODULE)/ansi
$(MODULE)_SRCPATH += $(MODULE)/math
$(MODULE)_SRCPATH += $(MODULE)/mathf
$(MODULE)_SRCPATH += $(MODULE)/stdio
$(MODULE)_SRCPATH += $(MODULE)/misc

$(MODULE)_INCPATH := $(MODULE)/include
$(MODULE)_INCPATH += $(MODULE)/math
$(MODULE)_INCPATH += $(MODULE)/mathf
$(MODULE)_INCPATH += $(MODULE)/stdio
$(MODULE)_INCPATH += $(MODULE)/misc

$(MODULE)_INCPATH += nxtFirmware/$(MCUVAR)/Source

$(MODULE)_CDEFS :=
$(MODULE)_CDEFS +=
# ----------------------------------------------------------------------------
# The following includes are done to do stuff like specify the library
# to build for this module...

include $(SRC_PATH)/makeinc/module_objects.mak
include $(SRC_PATH)/makeinc/module_library.mak
# ----------------------------------------------------------------------------
