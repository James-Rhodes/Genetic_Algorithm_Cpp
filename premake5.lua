-- premake5.lua

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


workspace "Genetic_Algorithm_Cpp"
   configurations { "Debug", "Release" }
   architecture "x86_64"
   startproject "Examples"

project "Genetic_Algorithm_Cpp"
   kind "StaticLib"
   language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
   location("%{wks.location}/%{prj.name}")

   
   includedirs{
      "%{wks.location}/%{prj.name}/include"
   }

   files { "%{wks.location}/%{prj.name}/**.h","%{wks.location}/%{prj.name}/**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
      filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"


project "Examples"

   kind "ConsoleApp"
   language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
   location("%{wks.location}/%{prj.name}")

   includedirs{
      "%{wks.location}/Genetic_Algorithm_Cpp/include"
   }
   links{
      "Genetic_Algorithm_Cpp"
   }

   files { "Examples/basic_optimization/**.h","Examples/basic_optimization/**.cpp" }



   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
      filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
   

