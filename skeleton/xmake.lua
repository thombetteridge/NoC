-- Define build modes
add_rules("mode.debug", "mode.release")

-- Set C++ standard and warnings
set_languages("c++20")
set_warnings("all")
set_optimize("fast")     -- set optimization level for release mode

-- Add required packages
add_requires("raylib")

-- Define the target
target("app")
set_kind("binary")           -- Specify target type
add_files("src/*.cpp")       -- Add all source files
add_packages("raylib")       -- Link against raylib
