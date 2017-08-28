Feature: OSRM has support for “table” requests, so Ruby bindings should support these requests too

  Scenario: I want to see a matrix of how long a travel from any of my addresses takes from to any other my address
    Given I have latitude 60.1681473 and longitude 24.9417190
    And I have latitude 60.1694561 and longitude 24.9385663
    When I calculate table data for these addresses
    Then I should have correct distances