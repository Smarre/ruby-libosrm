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

def symlink_osrm_data recipe
    FileUtils.ln_s "../#{recipe.work_path}/osrm-extract", "libexec/osrm-extract" unless File.exist? "libexec/osrm-extract"
    FileUtils.ln_s "../#{recipe.work_path}/osrm-contract", "libexec/osrm-contract" unless File.exist? "libexec/osrm-contract"
    FileUtils.ln_s "../../#{recipe.work_path}/../profiles/car.lua", "osrm/profiles/car.lua" unless File.exist? "osrm/profiles/car.lua"
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

        symlink_osrm_data recipe

        append_cflags("-I#{recipe.path}/include -I#{recipe.path}/include/osrm")

        # I can’t get OSRM library detection to work properly, so just adding it manually (it’s compiled by us so it ought to work)
        $LDFLAGS << " -Wl,-rpath,#{File.expand_path(recipe.work_path)} -L#{File.expand_path(recipe.work_path)} -losrm"

        # Adding boost_system as OSRM’s dependency
        $LDFLAGS << " -lboost_system"
    end
end

append_cflags("-DHAVE_CXX11")

#create_makefile "libosrm/libosrm"
create_makefile "libosrm/ruby_libosrm"