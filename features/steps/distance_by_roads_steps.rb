
require_relative "../../lib/libosrm"
require_relative "../../lib/libosrm/osrm"

Given(/^I have address "([^"]*)"$/) do |address|
  @addresses ||= []
  @addresses << address
end

Then(/^distance between these addresses should be (\d+) km$/) do |distance|
  osrm = LibOSRM::OSRM.new
  result = osrm.distance_by_roads @addresses
  expect(result).to eq(distance)
end

