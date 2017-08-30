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

Using
-----

TODO

Requirements
------------

TODO

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