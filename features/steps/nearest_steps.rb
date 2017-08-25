
When(/^I want to see (\d+) things nearest to latitude (\d+\.\d+) and longitude (\d+\.\d+)$/) do |amount, latitude, longitude|
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  @amount = amount.to_i
  @result = osrm.nearest latitude, longitude, @amount
end

Then(/^nearest things should be:$/) do |table|
  rows = table.symbolic_hashes

  expect(@result["waypoints"].size).to eq(@amount)
  rows.each_with_index do |hash, index|
    w = @result["waypoints"][index]
    expect(w["hint"]).to      eq(hash[:hint])
    expect(w["distance"]).to  eq(hash[:distance].to_f)
    expect(w["name"]).to      eq(hash[:name])
    expect(w["location"]).to  eq(latitude: hash[:latitude].to_f, longitude: hash[:longitude].to_f)
  end
end

