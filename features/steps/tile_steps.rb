
When(/^I calculate tile data for these addresses$/) do
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  zoom = 19
  @result = osrm.tile_with_coordinates @coordinates[0][:latitude], @coordinates[0][:longitude], zoom
end

Then(/^I should have correct tile data$/) do
  expect(@result).to_not be_nil

  # TODO: I guess I should have at least some kind of proper validation
end

