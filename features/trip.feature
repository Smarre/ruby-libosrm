Feature: OSRM has support for “trip” requests, so Ruby bindings should support these requests too

  Scenario: I want to do a trip to several points and get back to start location in shortest possible time
    Given I’m currently at "Mannerheimintie 1, Helsinki"
    When I want to travel to "Mannerheimintie 30, Helsinki"
    And I want to travel to "Mannerheimintie 20, Helsinki"
    And I want to get back to my original address
    Then I want to get a trip information about this trip with shortest possible route