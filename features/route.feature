Feature: OSRM has support for “route” requests, so Ruby bindings should support these requests too

  Scenario: I’m in a hurry but I don’t know route to my destination, so I want some guidance!
    Given I have latitude 60.1681474 and longitude 24.9417198
    And I have latitude 60.1694564 and longitude 24.9385667
    When get route data for the addresses
    Then I should have correct route data