add_rules("mode.debug", "mode.release")
set_languages("c++26")

target("poolday")
  set_kind("binary")
  add_files("src/*.cpp")
  add_includedirs("include/")