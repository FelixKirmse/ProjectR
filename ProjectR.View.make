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

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/ProjectR.View
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/libProjectR.View.so
  DEFINES   += -DDEBUG
  INCLUDES  += -Iinclude -Iinclude/ProjectR -Iinclude/ProjectR.Interfaces -Iinclude/ProjectR.Model -Iinclude/ProjectR.Logic -Iinclude/ProjectR.View -Iinclude/ProjectR.MapGen
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -Wall -ffast-math -g -fPIC -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -shared -ltcod_debug -ltcodgui_debug -ltcodxx_debug -lboost_system -lboost_filesystem -lboost_serialization -Lbuild
  LIBS      += -lProjectR.Model
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += build/libProjectR.Model.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
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
  LDFLAGS   += -s -shared -ltcod -ltcodgui -ltcodxx -lboost_system -lboost_filesystem -lboost_serialization -Lbuild
  LIBS      += -lProjectR.Model
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += build/libProjectR.Model.so
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/TitleScreenView.o \
	$(OBJDIR)/ConsoleView.o \
	$(OBJDIR)/RConsole.o \

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
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/TitleScreenView.o: src/ProjectR.View/TitleScreenView.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ConsoleView.o: src/ProjectR.View/ConsoleView.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RConsole.o: src/ProjectR.View/RConsole.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
