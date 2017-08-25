Feature: OSRM has support for “nearest” requests, so Ruby bindings should support these requests too

  Scenario: I want to see nearest n things
    When I want to see 5 things nearest to latitude 60.1681473 and longitude 24.9417190
    Then nearest things should be:
      | hint                                                                                                | distance          | name            | latitude  | longitude |
      | zh0BgP___38BAAAAMAAAAGIAAAAAAAAAAQAAADAAAABiAAAAAAAAAHsAAACuk3wBfBeWA5eUfAHTF5YDBAAPAE1tfBI=        | 16.11958158456255 | Mannerheimintie | 60.16806  | 24.941486 |