require "mkmf-rice"

#abort "missing libosrm C++ library" unless have_library "osrm"
#abort "missing storage/storage_config.hpp" unless find_header "storage/storage_config.hpp", "/usr/include/osrm"

append_cflags("-I/usr/include/osrm")

have_library "osrm"

#create_makefile "libosrm/libosrm"
create_makefile "ruby_libosrm"