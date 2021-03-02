
solution "ssdb"
	location ( "build" )
	configurations { "Debug", "Release" }
	
configuration "Debug"
	defines { "DEBUG" }
	flags { "Symbols", "ExtraWarnings"}

configuration "Release"
	defines { "NDEBUG" }
	flags { "Optimize", "ExtraWarnings"}
		
		
project "ssdb"
	kind "ConsoleApp"
	language "C++"
	includedirs {
		"deps/jemalloc-4.1.0/include",
		"deps/leveldb-1.20/include",
		"deps/snappy-1.1.0",
		"deps/lua/src",
		"./src" 
	}
	
	files { 
		"src/**.h",
		"src/**.cpp",
	}

	links { 
		"lua",
	}





