Feature: OSRM has support for “trip” requests, so Ruby bindings should support these requests too

  Scenario: I want to do a trip to several points and get back to start location in shortest possible time
    Given I’m currently at latitude 61.68688, longitude 27.27679
    When I want to travel to latitude 60.57497, longitude 27.1803
    And I want to travel to latitude 60.57329, longitude 27.18563
    And I want to get back to my original address
    Then I want to get a trip information about this trip with shortest possible route