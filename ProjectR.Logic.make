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
  OBJDIR     = obj/Debug/ProjectR.Logic
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/libProjectR.Logic.so
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
  OBJDIR     = obj/Release/ProjectR.Logic
  TARGETDIR  = build
  TARGET     = $(TARGETDIR)/libProjectR.Logic.so
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
	$(OBJDIR)/PreGameLogic.o \
	$(OBJDIR)/MainMenuLogic.o \
	$(OBJDIR)/TitleScreenLogic.o \
	$(OBJDIR)/MenuController.o \
	$(OBJDIR)/LogicState.o \
	$(OBJDIR)/RInput.o \
	$(OBJDIR)/RLogic.o \
	$(OBJDIR)/OverworldLogic.o \

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
	@echo Linking ProjectR.Logic
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
	@echo Cleaning ProjectR.Logic
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

$(OBJDIR)/PreGameLogic.o: src/ProjectR.Logic/PreGameLogic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/MainMenuLogic.o: src/ProjectR.Logic/MainMenuLogic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/TitleScreenLogic.o: src/ProjectR.Logic/TitleScreenLogic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/MenuController.o: src/ProjectR.Logic/MenuController.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/LogicState.o: src/ProjectR.Logic/LogicState.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RInput.o: src/ProjectR.Logic/RInput.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RLogic.o: src/ProjectR.Logic/RLogic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/OverworldLogic.o: src/ProjectR.Logic/OverworldLogic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)
