
Given(/^I’m currently at latitude (\d+\.\d+), longitude (\d+\.\d+)$/) do |latitude, longitude|
  @coordinates = []
  @coordinates << { latitude: latitude, longitude: longitude }
end

When(/^I want to travel to latitude (\d+\.\d+), longitude (\d+\.\d+)$/) do |latitude, longitude|
  @coordinates << { latitude: latitude, longitude: longitude }
end

When(/^I want to get back to my original address$/) do
  # Nothing to do; trip will automatically redirect backk to origin with default roundtrip parameter.
end

Then(/^I want to get a trip information about this trip with shortest possible route$/) do
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  @result = osrm.trip @coordinates, roundtrip: true, last: true

  expect(@result.count).to eq(1000)
end
