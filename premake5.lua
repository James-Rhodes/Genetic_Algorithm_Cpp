-- premake5.lua

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

function CreateExampleProject(projName)
   project (projName)
      kind "ConsoleApp"
      language "C++"
      targetdir ("%{wks.location}/bin/" .. outputdir .. "/Examples/%{prj.name}")
      objdir ("%{wks.location}/bin-int/" .. outputdir .. "/Examples/%{prj.name}")
      location("%{wks.location}/Examples/%{prj.name}")

      includedirs{
         "%{wks.location}/Genetic_Algorithm_Cpp/include"
      }

      files { "Examples/%{prj.name}/**.h","Examples/%{prj.name}/**.hpp","Examples/%{prj.name}/**.cpp" }



      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"
         
         filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"
end


workspace "Genetic_Algorithm_Cpp"
   configurations { "Debug", "Release" }
   architecture "x86_64"
   startproject "basic_optimisation"
   cppdialect "C++20"

project "Genetic_Algorithm_Cpp"
   kind "StaticLib"
   language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
   location("%{wks.location}/%{prj.name}")

   includedirs{
      "%{wks.location}/%{prj.name}/include"
   }

   files { "%{wks.location}/%{prj.name}/**.hpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
      filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

CreateExampleProject("basic_optimisation")
CreateExampleProject("setting_custom_selection_function")
CreateExampleProject("pruning_population")
CreateExampleProject("three_dimensional_optimisation")



   

