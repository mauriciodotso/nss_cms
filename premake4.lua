solution "nss-cms"
	configurations{"Debug"}

	project "nss_cms"
		kind "ConsoleApp"
		language "C++"
		targetdir "bin"
		files {
			"src/*.cpp",
			"includes/*.hpp",
			"includes/*.h"
		}

		configuration "Debug"
			defines "__DEBUG__"

		links {"nss_cms"}