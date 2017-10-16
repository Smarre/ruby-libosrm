
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

  expect(@result["code"]).to eq("Ok")

  expect(@result["waypoints"].size).to eq(3)
  expect(@result["waypoints"][0]["waypoint_index"]).to eq(0.0)
  expect(@result["waypoints"][0]["location"][:latitude]).to eq(60.677418)
  expect(@result["waypoints"][0]["location"][:longitude]).to eq(25.373834)
  expect(@result["waypoints"][0]["name"]).to eq("Kontulantie")
  expect(@result["waypoints"][0]["hint"]).to eq("7QgDgBCyA4AAAAAAHAAAAKQAAACkAAAAAAAAABwAAACkAAAApAAAAHsAAACKLIMBKt2dA_Y1oAFgRK0DAgAPAE1tfBI=")
  expect(@result["waypoints"][0]["trips_index"]).to eq(0.0)

  # trips data is more or less same as route data, so not tested comprehensively here
  expect(@result["trips"].size).to eq(1)
  expect(@result["trips"][0]["legs"].size).to eq(3)
end
