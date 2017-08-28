
When(/^I calculate table data for these addresses$/) do
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  @result = osrm.table @coordinates
end

Then(/^I should have correct distances$/) do
  expect(@result["code"]).to eq("Ok")

  expect(@result["durations"].size).to eq(2)
  expect(@result["durations"][0][0]).to eq(0.0)
  expect(@result["durations"][0][1]).to eq(184.9)
  expect(@result["durations"][1][0]).to eq(158.9)
  expect(@result["durations"][1][1]).to eq(0.0)

  expect(@result["sources"].size).to eq(2)
  expect(@result["sources"][0]["name"]).to eq("Mannerheimintie")

  expect(@result["destinations"].size).to eq(2)
  expect(@result["destinations"][0]["name"]).to eq("Mannerheimintie")
end