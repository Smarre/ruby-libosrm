
require "forwardable"

class LibOSRM::RouteParameters
  include Enumerable
  extend Forwardable

  def initialize
    @coordinates = []
  end

  def_delegators :@coordinates, :<<
end
