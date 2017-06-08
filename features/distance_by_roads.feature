Feature: When I have two addresses, I want to be able to calculate distance by roads between them.

    Scenario: When I have two addresses, I want know distance between them
        Given I have address "Mannerheimintie 1, Helsinki"
        And I have address "Mannerheimintie 20, 00100 Helsinki"
        Then distance between these addresses should be 20 km
