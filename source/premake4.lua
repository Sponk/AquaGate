-- Maratis Game plugin tutorial
solution "Tutorial"
	configurations { "Debug", "Release" }
	language "C++"
	
	local SDKDIR = os.getenv("MSDKDIR")

	-- OS defines
	if os.is("windows") then
		defines { "WIN32" }
	elseif os.is("linux") then
		defines { "linux" }
	elseif os.is("macosx") then
		defines { "__APPLE__" }
	end
 
	-- Build the game as a dll
	project "Game"
		kind "SharedLib"
		language "C++"
		
		-- make sure we can search and link properly
		libdirs { SDKDIR .. "/SDK/MCore/Libs",
					SDKDIR .. "/SDK/MEngine/Libs"}
		includedirs { SDKDIR .. "/SDK/MCore/Includes",
					SDKDIR .. "/SDK/MEngine/Includes",
					"."}
		
		-- include all the files, including Maratis SDK ones
		files {
			"**.cpp",
			"**.h",
			"../shaders/**",
			SDKDIR .. "/SDK/**.h"
		}
		
		-- split the files up a bit nicer inside Visual Studio
		vpaths { 
			["MCore/*"] = SDKDIR .. "/SDK/MCore/Includes/**.h",
			["MEngine/*"] = SDKDIR .. "/SDK/MEngine/Includes/**.h",
			["Game/*"] = { "**.h", "**.cpp" },
			["Shaders/*"] = { "../shaders/**" }
		}
		
		-- link to Maratis
		links { "MCore", "MEngine" }
		
		-- put the library back into the main project directory

		targetprefix ""
		targetdir "../"
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
	 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }  

