
require "uri"

require_relative "../../lib/libosrm"
require_relative "../../lib/libosrm/osrm"

Given(/^I have address "([^"]*)"$/) do |address|
  @coordinates ||= []
  url = URI::HTTP.build(host: "nominatim.openstreetmap.org", path: "/search", query: "addressdetails=1&format=jsonv2&q=#{address}")
  data = JSON.parse(`curl -s "#{url}"`)
  expect(data.size).to be >= 1

  latitude = data[0]["lat"].to_f
  longitude = data[0]["lon"].to_f
  @coordinates << { latitude: latitude, longitude: longitude }
end

Then(/^distance between these addresses should be (\d+.\d+) meters$/) do |distance|
  osrm = LibOSRM::RubyOSRM.new
  result = osrm.distance_by_roads @coordinates
  expect(result).to eq(distance.to_f)
end

