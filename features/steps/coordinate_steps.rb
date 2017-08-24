
Given(/^I have latitude (\d+\.\d+) and longitude (\d+\.\d+)$/) do |latitude, longitude|
  @coordinates ||= []
  @coordinates << { latitude: latitude, longitude: longitude }
end

Transform /^(\d+\.\d+)$/ do |decimal|
  decimal.to_f
end