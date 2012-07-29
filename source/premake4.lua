-- Maratis Game plugin tutorial
solution "Tutorial"
	configurations { "Debug", "Release" }
	language "C++"

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
		libdirs { os.getenv("MSDKDIR") .. "SDK/MCore/Libs",
					os.getenv("MSDKDIR") .. "SDK/MEngine/Libs"}
		includedirs { os.getenv("MSDKDIR") .. "SDK/MCore/Includes",
					os.getenv("MSDKDIR") .. "SDK/MEngine/Includes",
					"."}
		
		-- include all the files, including Maratis SDK ones
		files {
			"**.cpp",
			"**.h",
			os.getenv("MSDKDIR") .. "SDK/**.h"
		}
		
		-- split the files up a bit nicer inside Visual Studio
		vpaths { 
			["MCore/*"] = os.getenv("MSDKDIR") .. "SDK/MCore/Includes/**.h",
			["MEngine/*"] = os.getenv("MSDKDIR") .. "SDK/MEngine/Includes/**.h",
			["Game/*"] = { "**.h", "**.cpp" }
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

