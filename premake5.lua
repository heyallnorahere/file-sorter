workspace "file-sorter"
    architecture "x64"
    targetdir "build"
    configurations {
        "Debug",
        "Release"
    }
    flags {
        "MultiProcessorCompile"
    }
    startproject "file-sorter"
    filter "system:windows"
        defines {
            "SYSTEM_WINDOWS"
        }
    filter "system:macosx"
        defines {
            "SYSTEM_MACOSX"
        }
    filter "system:linux"
        defines {
            "SYSTEM_LINUX"
        }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
group "dependencies"
project "zip"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files {
        "vendor/submodules/zip/src/zip.*"
    }
    filter "configurations:Debug"
        symbols "on"
    filter "configurations:Release"
        optimize "on"
group ""
group "tools"
project "file-sorter"
    location "file-sorter"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/platform/%{cfg.system}/**.cpp",
        "%{prj.name}/platform/%{cfg.system}/**.h",
        "%{prj.name}/platform/*.h"
    }
    includedirs {
        "%{prj.name}/platform",
        "%{prj.name}/src"
    }
    sysincludedirs {
        "vendor/submodules/zip/src"
    }
    links {
        "zip"
    }
    filter "system:windows"
        links {
            "shlwapi.lib"
        }
    filter "action:not gmake*"
        pchheader "pch.h"
        pchsource "%{prj.name}/src/pch.cpp"
    filter "configurations:Debug"
        symbols "on"
    filter "configurations:Release"
        optimize "on"
group ""