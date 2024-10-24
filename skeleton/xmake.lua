add_rules("mode.debug", "mode.release")

add_requires("raylib")

target("app")
set_kind("binary")
add_files("src/*")
add_packages("raylib")
