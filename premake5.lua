workspace "hardpython"
  configurations { "Debug", "Release" }

project "hardpython"
  kind "WindowedApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  links { "SDL2" }

  files { "**.h", "**.cpp" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
