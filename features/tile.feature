Feature: OSRM has support for “tile” requests, so Ruby bindings should support these requests too

  Scenario: I don’t trust the routing data OSRM gave to me, so I want to verify it is correct
    Given I have latitude 60.1681473 and longitude 24.9417190
    When I calculate tile data for these addresses
    Then I should have correct tile data