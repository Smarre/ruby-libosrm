
When(/^get route data for the addresses$/) do
  osrm = LibOSRM::OSRM.new "test/helsinki_finland.osrm"
  @result = osrm.route @coordinates, with_geometry: true, steps: true, annotations: true
end

Then(/^I should have correct route data$/) do
  response = @result
  expect(response["code"]).to eq("Ok")

  expect(response["routes"].size).to eq(1)
  r = response["routes"][0]
  expect(r["distance"]).to      eq(1037.7)
  expect(r["duration"]).to      eq(184.9)
  expect(r["weight"]).to        eq(184.9)
  expect(r["weight_name"]).to   eq("routability")
  expect(r["geometry"]).to      eq("kqfnJikfwCaAdBT|@xCeFlGlWmM~RiG_Vr@oA")

  expect(r["legs"].size).to     eq(1)
  r["legs"].each do |l|
    expect(l["distance"]).to        eq(1037.7)
    expect(l["duration"]).to        eq(184.9)
    expect(l["weight"]).to          eq(184.9)
    expect(l["summary"]).to         eq("Annankatu, Simonkatu")

    expect(l["steps"].size).to      eq(7)

    # First step
    s = l["steps"][0]
    expect(s["distance"]).to                eq(46.4)
    expect(s["duration"]).to                eq(14.0)
    expect(s["geometry"]).to                eq("kqfnJikfwCk@bAMRGL")
    expect(s["weight"]).to                  eq(14.0)
    expect(s["name"]).to                    eq("Mannerheimintie")
    #expect(s["ref"]).to eq("mauw") # TODO
    #expect(s["pronuncation"]).to eq("mauw") # TODO
    #expect(s["destinations"]).to eq("mauw") # TODO
    #expect(s["exits"]).to eq("mauw") # TODO
    expect(s["mode"]).to                    eq("driving")
    #expect(s["intersections"]).to eq("mauw") # TODO
    #expect(s["rotary_name"]).to eq("mauw") # TODO
    #expect(s["rotary_pronunciation"]).to eq("mauw") # TODO
    expect(s["maneuver"]["modifier"]).to          eq("right")
    expect(s["maneuver"]["type"]).to              eq("depart")

    #Second step
    s = l["steps"][1]
    expect(s["distance"]).to                eq(128.4)
    expect(s["duration"]).to                eq(31.1)
    expect(s["geometry"]).to                eq('msfnJchfwCT|@FM^k@P[j@aA\\k@JOHQ')
    expect(s["weight"]).to                  eq(31.1)
    expect(s["name"]).to                    eq("Mannerheimintie")
    #expect(s["ref"]).to eq("mauw") # TODO
    #expect(s["pronuncation"]).to eq("mauw") # TODO
    #expect(s["destinations"]).to eq("mauw") # TODO
    #expect(s["exits"]).to eq("mauw") # TODO
    expect(s["mode"]).to                    eq("driving")
    #expect(s["intersections"]).to eq("mauw") # TODO
    #expect(s["rotary_name"]).to eq("mauw") # TODO
    #expect(s["rotary_pronunciation"]).to eq("mauw") # TODO
    expect(s["maneuver"]["modifier"]).to          eq("uturn")
    expect(s["maneuver"]["type"]).to              eq("continue")

    expect(l["annotation"]["distance"]).to      respond_to(:each)
    expect(l["annotation"]["duration"]).to      respond_to(:each)
    expect(l["annotation"]["datasources"]).to   respond_to(:each)
    expect(l["annotation"]["nodes"]).to         respond_to(:each)
    expect(l["annotation"]["weight"]).to        respond_to(:each)
    #expect(l["annotation"]["speed"]).to respond_to(:each) # TODO: speed seems to be missing
  end

  #expect(r["waypoints"]).to eq("ways") # TODO: guess there is no waypoints?
end
