Feature: OSRM has support for “match” requests, so Ruby bindings should support these requests too

  Scenario: When I do a match request, it should return the data I’m expecting
    Given I have latitude 60.1681473 and longitude 24.9417190
    And I have latitude 60.1694561 and longitude 24.9385663
    When I want to do a match request
    Then my match request should be successful and the data should be as I expect it to be
