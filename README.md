# Girlfriend Analyzer – Version 2 
#### (Name changed to Relationship_Analyzer)

## Overview
This is the **Python** implementation of the Girlfriend Analyzer, designed to evaluate and compare two girlfriends based on various weighted traits.  
It builds upon the original C++ console version by adding more flexibility, modularity, and user-friendly input handling.

## Features
- Compare two girlfriends using traits such as:
  - Intelligence
  - Spirituality
  - Family Values
  - Personality
  - Ambition
  - Health
  - Body Weight
- Assign custom importance weights to each trait (scale 0–10)
- Factor in Education Level with weights:
  - High School = 5
  - College = 7
  - University = 9
- Factor in Vaccination Status (COVID-19):
  - Yes = 5
  - No = 10
- Clean command-line input with validation
- Modular design to easily add or modify traits
- Optionally save and load girlfriend profiles (if implemented)
- Detailed score breakdown for transparent comparison

## How It Works
1. The user inputs traits and importance weights for both girlfriends.
2. The program calculates weighted scores for each trait.
3. Education and vaccination status weights are factored in.
4. The final score for each girlfriend is computed by summing weighted values.
5. The girlfriend with the **lower score** is considered the "lower risk" partner.


