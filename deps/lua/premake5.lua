project "lua"
	language "C"
	kind "StaticLib"
	includedirs {
		"src"
	}
	
	files {
		"src/*.h","src/*.c" 
	}
	
	removefiles {
		"src/luac.c","src/lua.c"
	}
