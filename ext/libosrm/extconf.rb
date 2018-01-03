require "mkmf-rice"

require "fileutils"
require "yaml"

def do_help
  print <<HELP
usage: ruby #{$0} [options]

    --use-system-libraries
        Use system libraries instead of building and using the bundled
        libraries.
HELP
  exit! 0
end

case
when arg_config("--help")
    do_help
end

def using_system_libraries?
    arg_config("--use-system-libraries", !!ENV["LIBOSRM_USE_SYSTEM_LIBRARIES"])
end

def create_osrm_symlinks recipe
    FileUtils.ln_s "../#{recipe.work_path}/osrm-extract", "bin/osrm-extract" unless File.exist? "bin/osrm-extract"
    FileUtils.ln_s "../#{recipe.work_path}/osrm-contract", "bin/osrm-contract" unless File.exist? "bin/osrm-contract"
end

case
when using_system_libraries?
    message "Building ruby-libosrm using system libraries.\n"

    # Using system libraries means we rely on the system libxml2 with
    # regard to the iconv support.

    dir_config("libosrm").any? or package_config("libosrm")

    append_cflags("-I/usr/include/osrm")
    have_library "osrm"
else
    message "Building ruby-libosrm using packaged libraries.\n"

    #puts Dir.pwd.inspect

    Dir.chdir "#{__dir__}/../.." do

        # The gem version constraint in the Rakefile is not respected at install time.
        # Keep this version in sync with the one in the Rakefile !
        require "rubygems"
        gem "mini_portile2", "~> 2.3.0"
        require "mini_portile2"

        # Current version doesn’t support out of tree builds
        require_relative "mini_portile_fixed_cmake"

        deps = YAML.load_file "ext/libosrm/dependencies.yaml"

        recipe = MiniPortileFixedCMake.new("libosrm", deps["libosrm"]["version"])
        recipe.files = [ deps["libosrm"]["download_uri"] ]
        recipe.cook
        recipe.activate

        create_osrm_symlinks recipe

        append_cflags("-I#{recipe.path}/include -I#{recipe.path}/include/osrm")
        find_library "osrm", nil, "#{recipe.path}/lib"
    end
end

append_cflags("-DHAVE_CXX11")

#create_makefile "libosrm/libosrm"
create_makefile "ruby_libosrm"