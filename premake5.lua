workspace "hardpython"
  configurations { "Debug", "Release" }

project "hardpython"
  kind "WindowedApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  links { "SDL2", "dl" }

  files { "**.h", "**.cpp" }

  --[[postbuildcommands {
    "{COPY} content/* bin/%{cfg.buildcfg}/content"
  }--]]

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
