# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/ProjectR
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/ProjectR
  DEFINES   += -DDEBUG
  INCLUDES  += -Iinclude -Iinclude/ProjectR -Iinclude/ProjectR.Interfaces -Iinclude/ProjectR.Model -Iinclude/ProjectR.Logic -Iinclude/ProjectR.View -Iinclude/ProjectR.MapGen -I/usr/include/lua5.1
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -g -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Lbuild -ltcod_debug -ltcodgui_debug -ltcodxx_debug -lboost_system -lboost_filesystem -lboost_serialization
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += -lProjectR.Model -lProjectR.Logic -lProjectR.View -lProjectR.MapGen
  LDDEPS    += build/libProjectR.Model.so build/libProjectR.Logic.so build/libProjectR.View.so build/libProjectR.MapGen.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/ProjectR
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/ProjectR
  DEFINES   += -DNDEBUG
  INCLUDES  += -Iinclude -Iinclude/ProjectR -Iinclude/ProjectR.Interfaces -Iinclude/ProjectR.Model -Iinclude/ProjectR.Logic -Iinclude/ProjectR.View -Iinclude/ProjectR.MapGen -I/usr/include/lua5.1
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -O3 -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Lbuild -s -ltcod -ltcodgui -ltcodxx -lboost_system -lboost_filesystem -lboost_serialization
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += -lProjectR.Model -lProjectR.Logic -lProjectR.View -lProjectR.MapGen
  LDDEPS    += build/libProjectR.Model.so build/libProjectR.Logic.so build/libProjectR.View.so build/libProjectR.MapGen.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/ProjectR.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking ProjectR
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning ProjectR
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
ifeq (posix,$(SHELLTYPE))
	-$(SILENT) cp $< $(OBJDIR)
else
	$(SILENT) xcopy /D /Y /Q "$(subst /,\,$<)" "$(subst /,\,$(OBJDIR))" 1>nul
endif
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
endif

$(OBJDIR)/main.o: src/ProjectR/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/ProjectR.o: src/ProjectR/ProjectR.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)
