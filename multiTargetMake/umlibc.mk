# -----------------------------------------------------------------------------
# Local makefile for umlibc
# -----------------------------------------------------------------------------
# $Id$
# -----------------------------------------------------------------------------
# See Copyright Notice in ../make/LICENSE
# -----------------------------------------------------------------------------
# Revision History
# ----------+-----------------+------------------------------------------------
# 2017.01.28 rhempel           Original
# -----------------------------------------------------------------------------

#! [ModuleVariables]
# ----------------------------------------------------------------------------
# Module Level Variables
#
mod_name := umlibc

$(mod_name)_lib_name  := $(mod_name)
$(mod_name)_dlib_name := lib$(mod_name)
$(mod_name)_exe_name  := $(mod_name)

# --------------------------------------------------------------------------------------
# Where to put Lua libraries and shared source
#
#UMLIBC_FILEDIR     := umlibc
#! [ModuleVariables]
#
#! [ModuleDirectories]
# ----------------------------------------------------------------------------
# Module Level Directories
#
$(mod_name)_srcdir    := src/$(UMLIBC_VERSION)
$(mod_name)_objdir    := obj/$(PLATFORM)/$(PROJECT)/$(UMLIBC_VERSION)

$(mod_name)_incdirs   := $($(mod_name)_srcdir)/include
$(mod_name)_incdirs   +=

$(mod_name)_objdirs   := $($(mod_name)_objdir)
#! [ModuleDirectories]
#
#! [ModuleCFLAGS]
# ----------------------------------------------------------------------------
# Module Level CFLAGS, SYSLIBS, etc
#
ifeq "$(strip $(windows_platform))" "TRUE"
  $(mod_name)_cflags  :=
else ifeq "$(strip $(nxt_platform))" "TRUE"
  $(mod_name)_cflags  := 
else ifeq "$(strip $(embedded_platform))" "TRUE"
  $(mod_name)_cflags  := 
else
  $(mod_name)_cflags  :=
endif
#! [ModuleCFLAGS]
#
#! [ModuleSYSLIBS]
# --------------------------------------------------------------------------------------
# SYSLIBS is set in the platform specific makefile, but we can add to it here if
# necessary.

ifeq "$(strip $(windows_platform))" "TRUE"
  $(mod_name)_syslibs := $(SYSLIBS)
else ifeq "$(strip $(nxt_platform))" "TRUE"
  $(mod_name)_syslibs := $(SYSLIBS)
else
  $(mod_name)_syslibs := $(SYSLIBS)
endif
#! [ModuleSYSLIBS]
#
#! [ModuleLIBS]
# --------------------------------------------------------------------------------------
# Add any module specific libraries that should be included here

ifeq "$(strip $(windows_platform))" "TRUE"
  $(mod_name)_libs := 
else
  $(mod_name)_libs :=
endif
#! [ModuleLIBS]
#! [ModuleINSTALL]
# --------------------------------------------------------------------------------------
# Module specific install locations
# 
# Note, the Lua dynamic library has to go in the same directory as the executable
#       on the Windows platform

#INSTALL_LUA_BIN   := $(INSTALL_BIN)
#INSTALL_LUA_MAN   := $(INSTALL_MAN)
#INSTALL_LUA_INC   := $(INSTALL_INC)
#INSTALL_LUA_SHARE := $(INSTALL_SHARE)

ifeq "$(strip $(windows_platform))" "TRUE"
#  INSTALL_LUA_LIB   := $(INSTALL_BIN)
else
#  INSTALL_LUA_LIB   := $(INSTALL_LIB)
endif
#! [ModuleINSTALL]
# --------------------------------------------------------------------------------------
# Object file sub-module groups
# --------------------------------------------------------------------------------------

# libc ansi sub-module -----------------------------------------------------------

PREFIX_O := ansi

MODSRC_O := atof.o     isgraph.o   memchr.o     strcat.o    strlen.o   strstr.o     \
	    chartab.o  islower.o   memcmp.o     strchr.o    strncat.o  strtofloat.o \
	    errlist.o  isprint.o   memcpy.o     strcmp.o    strncmp.o  strtoflong.o \
	    isalnum.o  ispunct.o   memfind.o    strcoll.o   strncpy.o  strtok.o     \
	    isalpha.o  isspace.o   memmove.o    strcpy.o    strnlen.o  strtol.o     \
	    isascii.o  isupper.o   memset.o     strcspn.o   strpbrk.o  strxfrm.o    \
	    iscntrl.o  isxdigit.o  setjmp.o     strerror.o  strrchr.o  tolower.o    \
	    isdigit.o  locale.o    setlocale.o  stricmp.o   strspn.o   toupper.o

ifeq "$(strip $(embedded_platform))" "TRUE"
  MODSRC_O := $(addsuffix thumb,$(MODSRC_O) )
else
endif

$(mod_name)_ansi_prefix  := $(PREFIX_O)
$(mod_name)_ansi_objects := $(addprefix $($(mod_name)_objdir)/,\
                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))

$(mod_name)_ansi_incdirs := 
$(mod_name)_ansi_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)

# libc math sub-module -----------------------------------------------------------

PREFIX_O := math

MODSRC_O := powl.o

ifeq "$(strip $(embedded_platform))" "TRUE"
  MODSRC_O := $(addsuffix thumb,$(MODSRC_O) )
else
endif

$(mod_name)_math_prefix  := $(PREFIX_O)
$(mod_name)_math_objects := $(addprefix $($(mod_name)_objdir)/,\
                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))

$(mod_name)_math_incdirs := 
$(mod_name)_math_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)

# libc mathf sub-module -----------------------------------------------------------

PREFIX_O := mathf

MODSRC_O := acosf.o   atan2f.o    cosf.o   floorf.o log10f.o  random.o sqrtf.o   \
            tanf.o    asincosf.o  atanf.o  expf.o   frexpf.o  logf.o   sincosf.o \
            asinf.o   ceilf.o     fabsf.o  ldexpf.o powf.o    sinf.o   tancotf.o

ifeq "$(strip $(embedded_platform))" "TRUE"
  MODSRC_O := $(addsuffix thumb,$(MODSRC_O) )
else
endif

$(mod_name)_mathf_prefix  := $(PREFIX_O)
$(mod_name)_mathf_objects := $(addprefix $($(mod_name)_objdir)/,\
                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))

$(mod_name)_mathf_incdirs := 
$(mod_name)_mathf_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)

# libc stdio sub-module -----------------------------------------------------------

PREFIX_O := stdio

MODSRC_O := fclose.o  fopen.o    fwrite.o   snprintf.o       vfprintf.o             \
	    feof.o    fprintf.o  iob.o      sprintf.o                               \
	    ferror.o  fputc.o    printf.o   sscanf.o                                \
	    fgetc.o   fputs.o    putchar.o                   vfscanf.o              \
	    fgets.o   fread.o    puts.o     ungetc.o

ifeq "$(strip $(embedded_platform))" "TRUE"
  MODSRC_O := $(addsuffix thumb,$(MODSRC_O) )
else
endif

$(mod_name)_stdio_prefix  := $(PREFIX_O)
$(mod_name)_stdio_objects := $(addprefix $($(mod_name)_objdir)/,\
                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))

$(mod_name)_stdio_incdirs := 
$(mod_name)_stdio_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)


#! [SubModule]
# lua aux sub-module -----------------------------------------------------------
#
#PREFIX_O := src/.
#
#MODSRC_O :=     lauxlib.o       lbaselib.o      lbitlib.o       lcorolib.o      \
#                ldblib.o        linit.o         liolib.o        lmathlib.o      \
#                loadlib.o       loslib.o        lstrlib.o       ltablib.o       \
#                    
#ifeq "$(strip $(nxt_platform))" "TRUE"
#  MODSRC_O := $(filter-out liolib.o   \
#	                   lmathlib.o \
#	                   loslib.o,     $(MODSRC_O) )
#  MODSRC_O := $(addsuffix thumb, $(MODSRC_O) )
#else
#endif
#
#$(mod_name)_aux_prefix  := $(PREFIX_O)
#$(mod_name)_aux_objects := $(addprefix $($(mod_name)_objdir)/,\
#                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))
#
#$(mod_name)_aux_incdirs := 
#$(mod_name)_aux_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)
#! [SubModule]

# lua executables sub-module ---------------------------------------------------
#
#PREFIX_O := src/./.
#
#MODSRC_O :=     lua.o
#
#$(mod_name)_exe_prefix  := $(PREFIX_O)
#$(mod_name)_exe_objects := $(addprefix $($(mod_name)_objdir)/,\
#                                $(addprefix $(PREFIX_O)/,$(MODSRC_O)))
#
#$(mod_name)_exe_incdirs := 
#$(mod_name)_exe_objdirs := $($(mod_name)_objdir)/$(PREFIX_O)
#
##! [ModulePHONYTargets]
# --------------------------------------------------------------------------------------
# PHONY Targets and dependencies
# 
#.PHONY: EXELUA DLIBLUA LIBLUA INSTALLLUA
.PHONY: LIBUMLIBC

#EXELUA     : $($(mod_name)_objdir)/$($(mod_name)_exe_name)$(EXE_EXT)

#DLIBLUA    : $($(mod_name)_objdir)/$($(mod_name)_dlib_name)$(DLIB_EXT)

LIBUMLIBC    : $($(mod_name)_objdir)/$($(mod_name)_lib_name)$(LIB_EXT)

#INSTALLLUA : $(INSTALL_LUA_BIN)/$($(mod_name)_exe_name)$(EXE_EXT)    \
#             $(INSTALL_LUA_LIB)/$($(mod_name)_dlib_name)$(DLIB_EXT)  \
#             $(INSTALL_LUA_MAN)/lua.1                                \
#             $(INSTALL_LUA_MAN)/luac.1                               \
#             $(INSTALL_LUA_INC)/lua.h                                \
#             $(INSTALL_LUA_INC)/luaconf.h                            \
#             $(INSTALL_LUA_INC)/lualib.h                             \
#             $(INSTALL_LUA_INC)/lauxlib.h                            \
#             $(INSTALL_LUA_INC)/lua.hpp
#! [ModulePHONYTargets]
#! [ModuleINSTALLdependencies]
# --------------------------------------------------------------------------------------
# Install file dependencies
#

#$(INSTALL_LUA_BIN)/$($(mod_name)_exe_name)$(EXE_EXT)   : $($(mod_name)_objdir)/$($(mod_name)_exe_name)$(EXE_EXT)

#$(INSTALL_LUA_LIB)/$($(mod_name)_dlib_name)$(DLIB_EXT) : $($(mod_name)_objdir)/$($(mod_name)_dlib_name)$(DLIB_EXT)

# $(INSTALL_LUA_LIB)/$($(mod_name)_lib_name)$(LIB_EXT)   : $($(mod_name)_objdir)/$($(mod_name)_lib_name)$(LIB_EXT)
#! [ModuleINSTALLdependencies]
#! [ModuleBuild]
# --------------------------------------------------------------------------------------
# From here on down, we're just setting up the build variables and running the build
# for:
#
# Installation
# Executables
# Dynamic Libraries
# Static Libraries
# Objects
#
# --------------------------------------------------------------------------------------
# Build the installation

#local_libdir   := $($(mod_name)_objdir)
#local_mandir   := $($(mod_name)_srcdir)/doc
#local_incdir   := $($(mod_name)_srcdir)/src
#local_etcdir   := $($(mod_name)_srcdir)/etc
#local_sharedir := $($(mod_name)_srcdir)/src
#
#dest_libdir    := $(INSTALL_LUA_LIB)
#dest_sharedir  := $(INSTALL_LUA_SHARE)/$(LUA_FILEDIR)

#include ./make/build/build_install.mk

# --------------------------------------------------------------------------------------
# Build the executables

#local_objdir   := $($(mod_name)_objdir)
#local_exename  := $($(mod_name)_exe_name)
#local_libs     := $($(mod_name)_libs)
#local_syslibs  := $($(mod_name)_syslibs)
#local_object   := $(local_objdir)/$($(mod_name)_exe_prefix)/lua$(OBJ_EXT)
#local_ldlib    := $($(mod_name)_objdir)/$($(mod_name)_dlib_name)$(DLIB_EXT)

#ifeq "$(strip $(nxt_platform))" "TRUE"
#else
#  include ./make/build/build_exe.mk
#endif
#
#OBJDIRS               += $($(mod_name)_objdirs)

# --------------------------------------------------------------------------------------
# Build the dynamic library

#local_objdir   := $($(mod_name)_objdir)
#local_dlibname := $($(mod_name)_dlib_name)
#local_libs     := $($(mod_name)_libs)
#local_syslibs  := $($(mod_name)_syslibs)
#local_objects  := $($(mod_name)_core_objects) \
#                  $($(mod_name)_aux_objects)
#
#ifeq "$(strip $(nxt_platform))" "TRUE"
#else
#  include ./make/build/build_dlib.mk
#endif

# --------------------------------------------------------------------------------------
# Build the static library

local_objdir   := $($(mod_name)_objdir)
local_libname  := $($(mod_name)_lib_name)
local_arflags  := 
local_objects  := $($(mod_name)_ansi_objects) \
                  $($(mod_name)_math_objects) \
                  $($(mod_name)_mathf_objects) \
                  $($(mod_name)_stdio_objects) \

include ./make/build/build_lib.mk

# --------------------------------------------------------------------------------------
# Build the ansi sub-module objects

OBJDIRS        += $($(mod_name)_ansi_objdirs)

local_prefix   := $($(mod_name)_ansi_prefix)
local_objdir   := $($(mod_name)_objdir)
local_srcdir   := $($(mod_name)_srcdir)
local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_ansi_incdirs)
local_cflags   := $($(mod_name)_cflags) 

include ./make/build/build_objects.mk 

sinclude $(subst .o,.d,$($(mod_name)_ansi_objects))

# --------------------------------------------------------------------------------------
# Build the math sub-module objects

OBJDIRS        += $($(mod_name)_math_objdirs)

local_prefix   := $($(mod_name)_math_prefix)
local_objdir   := $($(mod_name)_objdir)
local_srcdir   := $($(mod_name)_srcdir)
local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_math_incdirs)
local_cflags   := $($(mod_name)_cflags) 

include ./make/build/build_objects.mk 

sinclude $(subst .o,.d,$($(mod_name)_math_objects))

# --------------------------------------------------------------------------------------
# Build the mathf sub-module objects

OBJDIRS        += $($(mod_name)_mathf_objdirs)

local_prefix   := $($(mod_name)_mathf_prefix)
local_objdir   := $($(mod_name)_objdir)
local_srcdir   := $($(mod_name)_srcdir)
local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_mathf_incdirs)
local_cflags   := $($(mod_name)_cflags) 

include ./make/build/build_objects.mk 

sinclude $(subst .o,.d,$($(mod_name)_mathf_objects))

# --------------------------------------------------------------------------------------
# Build the stdio sub-module objects

OBJDIRS        += $($(mod_name)_stdio_objdirs)

local_prefix   := $($(mod_name)_stdio_prefix)
local_objdir   := $($(mod_name)_objdir)
local_srcdir   := $($(mod_name)_srcdir)
local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_stdio_incdirs)
local_cflags   := $($(mod_name)_cflags) 

include ./make/build/build_objects.mk 

sinclude $(subst .o,.d,$($(mod_name)_stdio_objects))

$(info OBJ: $(local_objdir)/$(local_prefix)/foo.othumb)
$(info SRC: $(local_srcdir)/$(local_prefix)/foo.c)

# --------------------------------------------------------------------------------------
# Build the aux sub-module objects
#
#OBJDIRS        += $($(mod_name)_aux_objdirs)
#
#local_prefix   := $($(mod_name)_aux_prefix)
#local_objdir   := $($(mod_name)_objdir)
#local_srcdir   := $($(mod_name)_srcdir)
#local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_aux_incdirs)
#local_cflags   := $($(mod_name)_cflags) 
#
#include ./make/build/build_objects.mk 
#
#sinclude $(subst .o,.d,$($(mod_name)_aux_objects))
#
# --------------------------------------------------------------------------------------
# Build the exe sub-module objects
#
#OBJDIRS        += $($(mod_name)_exe_objdirs)
#
#local_prefix   := $($(mod_name)_exe_prefix)
#local_objdir   := $($(mod_name)_objdir)
#local_srcdir   := $($(mod_name)_srcdir)
#local_incdirs  := $($(mod_name)_incdirs) $($(mod_name)_exe_incdirs)
#local_cflags   := $($(mod_name)_cflags) 
#
#include ./make/build/build_objects.mk 
#
#sinclude $(subst .o,.d,$($(mod_name)_exe_objects))
#
# --------------------------------------------------------------------------------------
#! [ModuleBuild]
