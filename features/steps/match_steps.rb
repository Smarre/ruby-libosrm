
When(/^I want to do a match request$/) do
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  @result = osrm.match @coordinates
end

Then(/^my match request should be successful and the data should be as I expect it to be$/) do
  expect(@result["code"]).to eq("Ok")

  expect(@result["tracepoints"].size).to eq(5435)

  expect(@result["matchings"].size).to eq(5435)
end
