# frozen_string_literal: true

require "date"

require_relative "lib/libosrm/version"

Gem::Specification.new do |s|
  s.name        = "libosrm"
  s.version     = LibOSRM::VERSION
  s.date        = Date.today
  s.summary     = "libosrm bindings for Ruby."
  s.description = <<-EOF
    Ruby bindings for OSRM’s C++ API, providing faster and more customizable interaction with OSRM than HTTP based API.

    This gem requires native dependencies, you can find list of dependencies in README.
  EOF
  s.authors     = [ "Samu Voutilainen" ]
  s.email       = "smar@smar.fi"
  s.files       = [
    "ext/libosrm/mini_portile_fixed_cmake.rb",
    "ext/libosrm/dependencies.yaml",
    "lib/libosrm.rb",
    "lib/libosrm/osrm.rb",
    "lib/libosrm/version.rb",
    "libexec/.keep",
    "osrm/profiles/.keep"
  ] +
    Dir.glob("ext/libosrm/*.cpp") +
    Dir.glob("ext/libosrm/*.hpp")
  s.extensions  = %w[ext/libosrm/extconf.rb]
  s.bindir      = "bin"
  s.executables = [ "libosrm-prepare" ]
  s.homepage    = "https://github.com/Smarre/ruby-libosrm"
  s.license     = "MIT"

  s.required_ruby_version = "> 2.3.0"

  s.add_runtime_dependency      "mini_portile2",  "~> 2.5"
  s.add_runtime_dependency      "rice",           "~> 2.1"
  s.add_development_dependency  "rake",           "~> 12.0"
  s.add_development_dependency  "rake-compiler",  "~> 1.0"
end
