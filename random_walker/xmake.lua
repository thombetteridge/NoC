add_rules("mode.debug", "mode.release")

add_requires("raylib")

target("random-walker")
set_kind("binary")
add_files("src/main.cpp")
add_packages("raylib")
