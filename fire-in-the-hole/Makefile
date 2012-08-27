################################################################################
#                                                                              #
# A recursive Makefile ;)                                                      #
#                                                                              #
# Author: pablin                                                               #
# Created: 2009/04/18                                                          #
#                                                                              #
# Copyleft 2009 - Released under the GPL license (http://www.gnu.org)          #
#                                                                              #
################################################################################


##### BASIC CONFIGURATION ######################################################


# Targets' names.
gui = gui

# Targets to build.
targets = $(gui)

# Language: C or C++
language = C++

# Common source file directories. Make will search recursively into theese for
# source files to build.  
common_src_dirs = src

# Common header directories. Will be included with -I option.
include_dirs = include

# Target-specific directories. Variable names must be <target name>_src_dirs
$(gui)_src_dirs = 

# Target-scpecific LDFLAGS. (CFLAGS are global... sorry)
$(gui)_ldflags =

# Uncomment to make a static compilation (all linked libraries are included into
# the target). Only works if target is not a library.
#static = yes


# Uncomment to use math.h functions.
math = yes

# Uncomment to use GTK+.
#gtk = yes

#pthreads = yes

# Uncomment to use GTKmm.
gtkmm = yes

xml = yes

# Uncomment to use curses (ncurses in Linux and pdcurses in Windows).
#curses = yes

# Uncomment to use SDL
#sdl = yes

# Uncomment to make the compilation process more verbose.
#verbose = yes


##### ADVANCED CONFIGURATION ###################################################

# To make the compiler more strict.
CFLAGS = -Wall -pedantic-errors

# Linker options.
#LDFLAGS =


##### VARIABLES CALCULATED FROM CONFIGURATION ##################################

# Debug CFLAGS.
debug_cflags = -ggdb -DDEBUG -DNO_COMMONS_DEBUG -O0

# Release CFLAGS.
release_cflags = -DNDEBUG  -O3

ifdef xml
CFLAGS += $(shell xml2-config --cflags )
LDFLAGS += $(shell xml2-config --libs )
endif

# GTK+ flags and libraries.
ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# GTKmm flags and libraries.
ifdef gtkmm
CFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
LDFLAGS += $(shell pkg-config --libs gtkmm-2.4)
endif

# Curses library.
ifdef curses
LDFLAGS += -lcurses
endif

# SDL library.
ifdef sdl
LDFLAGS += -lSDLmain -lSDL
endif

# Links with libm.
ifdef math
LDFLAGS += -lm
endif

# Adds the -static flag if specified.
ifdef static
LDFLAGS += -static
endif

# All src and include dirs.
all_src_dirs = $(common_src_dirs) \
	$(foreach var,$(patsubst %,%_src_dirs,$(targets)),$($(var)))

# Adds every directory in include_dirs to the CFLAGS to search for .h files.
CFLAGS += $(patsubst %,-I%,$(include_dirs))


# C flags go for C++ too.
CXXFLAGS += $(CFLAGS)


# Configures source file extensions and linker depending on language.
ifeq ($(language), C++)
src_extension = .cpp
LD = $(CXX)
else
src_extension = .c
LD = $(CC)
endif

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif

# Varieble/function to find all source files in a given list of directories.
find_src_files = \
	$(foreach dir, $(1), \
		$(shell find $(dir) -name '*$(src_extension)'))

all_src_files = $(call find_src_files,$(all_src_dirs))


# Creates the object files names by changing the extension on the source files.
debug_obj_files   = $(patsubst %$(src_extension),debug/%.o,  $(all_src_files))
release_obj_files = $(patsubst %$(src_extension),release/%.o,$(all_src_files))

# Creates the dependency files names by substituting the object files extension.
debug_deps_files =   $(patsubst %$(src_extension),debug/%.d,  $(all_src_files))
release_deps_files = $(patsubst %$(src_extension),release/%.d,$(all_src_files))

# "Real" targets.
debug_targets   = $(patsubst %,debug/%,$(targets))
release_targets = $(patsubst %,release/%,$(targets))




##### RULES ####################################################################

# PHONY rules: Are not associated to a file.
.PHONY: all clean debug release

all :
	@echo "Use make <target=(debug|release|clean)>"


# Generates the dependency files using gcc.
debug/%.d : %$(src_extension) Makefile
	@mkdir -p $(dir $@)
	@$(old) -MM -MF $@ -MP -MT debug/$*.o $(CFLAGS) $(debug_cflags) $<

release/%.d : %$(src_extension) Makefile
	@mkdir -p $(dir $@)
	@$(old) -MM -MF $@ -MP -MT release/$*.o $(CFLAGS) $(release_cflags) $<

# Includes the dependecy files.
-include $(debug_deps_files)
-include $(release_deps_files)


# Rule to make the object files. The dependencies are specified in the .d files
# NOTE: The second command of this rule, that compiles the .o file, depends on 
# the first dependency being source file asociated with the .o file.
debug/%.o :
	@mkdir -p $(dir $@)
	$(CXX) $< -c $(CFLAGS) $(debug_cflags) -o $@

release/%.o :
	@mkdir -p $(dir $@)
	$(CXX) $< -c $(CFLAGS) $(release_cflags) -o $@

debug : $(debug_targets)

release : $(release_targets) 


get_obj_files = $(patsubst %$(src_extension),$(dir $(1))%.o,\
	$(call find_src_files,$(common_src_dirs) $($(notdir $(1))_src_dirs)))

get_ldflags = $($(notdir $(1))_ldflags)

# Builds the targets.
$(debug_targets) : $(debug_obj_files) Makefile
	$(LD) $(call get_obj_files,$@) $(LDFLAGS) $(call get_ldflags,$@) -o $@

$(release_targets) : $(release_obj_files) Makefile
	$(LD) $(call get_obj_files,$@) $(LDFLAGS) $(call get_ldflags,$@) -o $@


# Deletes all object and dependency files as well as the targets. 
clean:
	$(RM) -r debug release

