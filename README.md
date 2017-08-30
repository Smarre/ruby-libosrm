libosrm Ruby bindings
=====================

- [Repository (Github)](https://github.com/Smarre/ruby-libosrm)
- [Documentation](http://www.rubydoc.info/github/Smarre/ruby-libosrm/master)
- [Bugs (Github)](https://github.com/Smarre/ruby-libosrm/issues)

Description
-----------

ruby-libosrm is a Ruby bindings for libosrm, the C++ bindings for OSRM, open source routing machine.
Provides fast and customizable interface compared to OSRM’s old HTTP API.

Synopsis
--------

Prepare a map data for OSRM:

```shell
$ osrm-extract map.pbf
$ osrm-contract map.osrm
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

- Ruby 2.4
- OSRM map data

Installing
----------

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

Basic usage
-----

After OSRM has been set up, the usage is fairly straightforward, and this works as specified at the synopsis.
If you are not familiar with OSRM, it may make sense to set up an OSRM server in order to get used to how OSRM works.
This gem operates with OSRM’s C++ API, which means that the server component is not used, but instead the data is calculated
using native code directly and then the response is returned to Ruby side. This allows fast and more flexible
requests than the HTTP API would allow.

OSRM contains some utilities to produce map files for libosrm to use. There is instructions at
https://github.com/Project-OSRM/osrm-backend but here is a summary of necessary steps:

1. Clone osrm-backend

```shell
$ git clone https://github.com/Project-OSRM/osrm-backend.git
```

2. Compile osrm-backend

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ make install
```

3. Prepare map data

You can take map data for example from {http://download.geofabrik.de/index.html Geofabrik}.

    $ wget http://download.geofabrik.de/europe/germany/berlin-latest.osm.pbf
    $ osrm-extract berlin-latest.osm.pbf -p PATH_TO_OSRM_CLONE/profiles/car.lua
    $ osrm-contract berlin-latest.osrm

4. Test the map data

At this point, you should have everything you need in order to actually use libosrm.

```ruby
require "libosrm"

osrm = OSRM.new "map.osrm"

# Returns distance by roads as a float, as meters
distance = osrm.distance_by_roads { latitude: 60.1681473, longitude: 24.9417190 }, { latitude: 60.1694561, longitude: 24.9385663 }
```

Save this script and try to run it. If you have Finnish map data, this should return you a distance.
If you don’t have Finnish map data, an exception should be raised.


Known issues
--------------

- some requests are not fully supported (TODO)

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

Copyright (c) 2017 Samu Voutilainen

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