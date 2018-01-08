libosrm Ruby bindings
=====================

- [Repository (Github)](https://github.com/Smarre/ruby-libosrm)
- [Documentation](http://www.rubydoc.info/github/Smarre/ruby-libosrm/master)
- [Bugs (Github)](https://github.com/Smarre/ruby-libosrm/issues)

Description
-----------

ruby-libosrm is a Ruby bindings for OSRM’s libosrm, the C++ bindings for OSRM, open source routing machine,
which provides fast and customizable interface compared to OSRM’s old HTTP API.

Synopsis
--------

Prepare a map data for OSRM:

```shell
$ libosrm-prepare map.pbf
```

Use the API:

```ruby
require "libosrm"

osrm = OSRM.new "map.osrm"

# Returns distance by roads as a float, as meters
distance = osrm.distance_by_roads { latitude: 60.1681473, longitude: 24.9417190 }, { latitude: 60.1694561, longitude: 24.9385663 }
```

Features
--------

- Straightforward API
- Customizable requests

Requirements
------------

- Ruby 2.3 or greater
- OSRM’s dependencies; see Installing section

Installing
----------

Since libosrm is bindings for OSRM’s C++ library, you need to install same dependencies as you would do when compiling only OSRM.

From [OSRM’s README](https://github.com/Project-OSRM/osrm-backend/tree/5.12), following dependencies are required:

- gcc-4.9 or greater or clang-3.4 or greater
- cmake-2.8.11 or greater
- boost-1.54 or greater
- libtbb
- threading support
- expat
- bzip2
- lua-5.2 (lua-5.1 works for now but is deprecated)
- osmium
- zlib

For Ubuntu 16.04, the packages to be installed would be

```shell
$ sudo apt install build-essential git cmake pkg-config \
libbz2-dev libstxxl-dev libstxxl1v5 libxml2-dev \
libzip-dev libboost-all-dev lua5.2 liblua5.2-dev libtbb-dev
```

You can find more information at [OSRM’s README](https://github.com/Project-OSRM/osrm-backend/tree/5.12).

After you have required dependencies, you can install libosrm gem:

```shell
$ gem install libosrm
```

or with Bundler

    # In Gemfile
    gem "libosrm"

and then install the bundle:

```shell
$ bundle install
```

If there is no missing dependencies, compilation of OSRM and libosrm should start. The compilation
should take a long time, so drink a cup of tea or hot chocolate. If everything went well,
you should now have a working instance of libosrm.

Basic usage
-----

1. Set up your project

If you already set up your project, skip this step.

Easiest way to manage your project is through [Bundler](http://bundler.io/). If you don’t have it,
you can install it with `[sudo] gem install bundler`.

```shell
$ mkdir project
$ cd project
$ bundle init
$ echo 'gem "libosrm"' >> Gemfile
$ bundle install
```

2. Prepare map data

For libosrm to be able to calculate anything, it requires map data. You can use either data of whole world
or a portion it, for example your country’s or specific city’s data.

One place to get the data from is {http://download.geofabrik.de/index.html Geofabrik}.

For example:

```shell
$ mkdir map
$ cd map
$ wget http://download.geofabrik.de/europe/finland-latest.osm.pbf
$ bundle exec libosrm-prepare finland-latest.osm.pbf
```

3. Testing that everything works

After the map data has been processed, you can start to use libosrm. To ensure everything
works, you can use following simple script:

```ruby
require "libosrm"

osrm = OSRM.new "map/finland-latest.osrm"

# Returns distance by roads as a float, as meters
distance = osrm.distance_by_roads { latitude: 60.1681473, longitude: 24.9417190 }, { latitude: 60.1694561, longitude: 24.9385663 }
```

Save this script as test.rb (at root directory of your project) and run it:

```shell
$ bundle exec ruby test.rb
```

If you have Finnish map data, this should return you a distance.
If you don’t have Finnish map data, an exception should be raised.

Compiling from the repository
-----------------------------

Installing from gem (see Installing section) is preferred, but it is also possible to
build from the source.

NOTE: building should take long time as osrm needs to be built too.


```shell
$ git clone https://github.com/Smarre/ruby-libosrm.git
$ cd ruby-libosrm
$ # Install bundler if required: gem install bundler
$ bundle install
$ # Compile the library.
$ bundle exec rake
$ # Run tests to ensure the library works
$ bundle exec cucumber
```

Now you should have working instance of ruby-libosrm. To use it, you most likely want to build a gem and use it through
the gem in your project:

```shell
$ # Build the gem
$ gem build libosrm.gemspec
$ # prepend with sudo if you don’t use user specific gem data
$ gem install libosrm-0.0.1.gem
```

Known issues
--------------

- some requests are not fully supported (TODO)
- OSRM profile is not configurable (hardcoded to OSRM supplied car.lua)
- Build files after gem installation are not cleaned
- Linking OSRM statically instead as a library would further reduce disk space usage

TODO
----

- Maybe we should by default bundle all libraries? That would make it easier to get everything compiled. Or at least check if system has version and only then use bundled one.

Developers
----------

    $ gem install bundler
    $ bundle install
    $ cucumber
    # write new feature
    $ cucumber
    # rinse and repeat :-)

Github
------

You can do pull requests at Github using the standard pattern :-)

1. Fork it
2. Create your feature branch (git checkout -b my-new-feature)
3. Commit your changes (git commit -am 'Add some feature')
4. Push to the branch (git push origin my-new-feature)
5. Create new Pull Request

License
-------

(The MIT License)

Copyright (c) 2017-2018 Samu Voutilainen

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.