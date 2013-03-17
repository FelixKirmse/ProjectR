local LIBTCOD_LIBRARIES = "-ltcod -ltcodgui -ltcodxx"
local LIBTCOD_LIBRARIES_DEBUG = "-ltcod_debug -ltcodgui_debug -ltcodxx_debug"
local BOOST_LIBRARIES = "-lboost_system -lboost_filesystem -lboost_serialization"
local LUA_LIBRARIES = "-llua5.1 -lluabind"

solution "ProjectR"
    configurations { "Debug", "Release" }
    flags { "ExtraWarnings","FloatFast" }
    includedirs { "include", "include/ProjectR", "include/ProjectR.Interfaces", "include/ProjectR.Model", "include/ProjectR.Logic", "include/ProjectR.View", "include/ProjectR.MapGen", "/usr/include/lua5.1" }

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "OptimizeSpeed" }

    project "ProjectR.Model"
        kind "SharedLib"
        language "C++"
        targetdir "build"
        files { "src/ProjectR.Model/**.cpp" }
        buildoptions { "-std=c++11" }
        configuration { "Release" }
          linkoptions { LIBTCOD_LIBRARIES, BOOST_LIBRARIES, LUA_LIBRARIES }
        configuration { "Debug" }
          linkoptions { LIBTCOD_LIBRARIES_DEBUG, BOOST_LIBRARIES, LUA_LIBRARIES }


    project "ProjectR.Logic"
        kind "SharedLib"
        language "C++"
        targetdir "build"
        files { "src/ProjectR.Logic/**.cpp" }
        links { "ProjectR.Model" }
        buildoptions { "-std=c++11" }
        configuration { "Release" }
          linkoptions { LIBTCOD_LIBRARIES, BOOST_LIBRARIES }
        configuration { "Debug" }
          linkoptions { LIBTCOD_LIBRARIES_DEBUG, BOOST_LIBRARIES }

    project "ProjectR.MapGen"
        kind "SharedLib"
        language "C++"
        targetdir "build"
        files { "src/ProjectR.MapGen/**.cpp" }
        links { "ProjectR.Model" }
        buildoptions { "-std=c++11" }        

    project "ProjectR.View"
        kind "SharedLib"
        language "C++"
        targetdir "build"
        files { "src/ProjectR.View/**.cpp" }
        links { "ProjectR.Model" }
        buildoptions { "-std=c++11" }
        configuration { "Release" }
          linkoptions { LIBTCOD_LIBRARIES, BOOST_LIBRARIES }
        configuration { "Debug" }
          linkoptions { LIBTCOD_LIBRARIES_DEBUG, BOOST_LIBRARIES }

    project "ProjectR"
        kind "WindowedApp"
        language "C++"        
        targetdir "build"
        files { "src/ProjectR/**.cpp" }
        links { "ProjectR.Model", "ProjectR.Logic", "ProjectR.View", "ProjectR.MapGen" }
        buildoptions { "-std=c++11" }
        configuration { "Release" }
          linkoptions { LIBTCOD_LIBRARIES, BOOST_LIBRARIES }
        configuration { "Debug" }
          linkoptions { LIBTCOD_LIBRARIES_DEBUG, BOOST_LIBRARIES }
