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

		includedirs {"/usr/include/nspr4", "/usr/include/nss3"}

		configuration "Debug"
			defines "__DEBUG__"

		links {"smime3", "nss3"}