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
  OBJDIR     = obj/Debug/ProjectR.View
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/libProjectR.View.so
  DEFINES   += -DDEBUG
  INCLUDES  += -Iinclude -Iinclude/ProjectR -Iinclude/ProjectR.Interfaces -Iinclude/ProjectR.Model -Iinclude/ProjectR.Logic -Iinclude/ProjectR.View -Iinclude/ProjectR.MapGen
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -g -fPIC -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Lbuild -shared -ltcod_debug -ltcodgui_debug -ltcodxx_debug -lboost_system -lboost_filesystem -lboost_serialization
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += -lProjectR.Model
  LDDEPS    += build/libProjectR.Model.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/ProjectR.View
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/libProjectR.View.so
  DEFINES   += -DNDEBUG
  INCLUDES  += -Iinclude -Iinclude/ProjectR -Iinclude/ProjectR.Interfaces -Iinclude/ProjectR.Model -Iinclude/ProjectR.Logic -Iinclude/ProjectR.View -Iinclude/ProjectR.MapGen
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -O3 -fPIC -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Lbuild -s -shared -ltcod -ltcodgui -ltcodxx -lboost_system -lboost_filesystem -lboost_serialization
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += -lProjectR.Model
  LDDEPS    += build/libProjectR.Model.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/SimpleMapView.o \

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
	@echo Linking ProjectR.View
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
	@echo Cleaning ProjectR.View
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

$(OBJDIR)/SimpleMapView.o: src/ProjectR.View/SimpleMapView.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)