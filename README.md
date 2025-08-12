# Girlfriend Analyzer Project

## 📜 Overview
The **Girlfriend Analyzer** is a fun, data-driven project that evaluates and compares two potential partners based on multiple traits and risk factors.  
It has evolved through **three major versions**:

1. **Version 1:** C++ Console-Based Analyzer  
2. **Version 2:** Python GUI/CLI Hybrid  
3. **Version 3 (In Progress):** AI-Powered Chatbot using LLaMA and GPT-4/5 APIs

---

## 🖥 Version 1 – C++ Console-Based Analyzer
**Language:** C++  
**Interface:** Console Application  
**Purpose:** Compare two girlfriends based on predefined traits and weights, producing a "risk score."

### Features:
- **Education Level Weights:**  
  - High School = 5  
  - College = 7  
  - University = 9  
- **Vaccination Status Weights (COVID-19):**  
  - Yes = 5  
  - No = 10  
- **Traits Rated (0–10):**
  - Intelligence
  - Spirituality
  - Family Values
  - Personality
  - Ambition
  - Health
  - Body Weight
- **Importance Weights for Each Trait** (0–10) – allows user to give priority to certain qualities.
- **Final Score Calculation:**  
  Weighted sum for each girlfriend.  
  - Lower score = **Lower Risk**  
  - Higher score = **Higher Risk**

---

## 🐍 Version 2 – Python-Based Analyzer
**Language:** Python  
**Interface:** Initially CLI, later partial GUI using Tkinter  
**Purpose:** Provide the same functionality as Version 1 but with a more flexible and modular design.

### Improvements over Version 1:
- **Dynamic Trait Management:** Traits can be added/removed without rewriting core logic.
- **Data Persistence:** Ability to save and load girlfriend profiles from JSON files.
- **More Detailed Reports:** Includes score breakdown by category.
- **Cleaner Input Handling:** Validation for numeric ranges, easier user prompts.
- **GUI Integration (Tkinter):** Added sliders, dropdown menus, and buttons for easier input.

---

## 🤖 Version 3 – AI-Powered Girlfriend Analyzer Chatbot (In Progress)
**Languages:** Python + API Integration  
**AI Models Used:** LLaMA, GPT-4, GPT-5  
**Purpose:** Turn the analyzer into an interactive AI assistant that can:
- Guide the user through questions conversationally
- Suggest traits to consider based on preferences
- Explain results with natural language reasoning
- Make witty, context-aware commentary

### Key Tech:
- **LLaMA** – Initially used for lightweight, local inference and offline conversational logic.
- **DeepSeek** – Used experimentally for multi-turn reasoning and quick personality-driven answers.
- **GPT-4 API** – First cloud integration for high-quality text generation and explanations.
- **GPT-5 API** – Chosen as the final model for production because:
  - **Better reasoning & accuracy** for score explanations
  - **More natural conversation flow**
  - **Handles complex, weighted trait analysis more reliably**
  - **Lower hallucination rate** compared to earlier models
  - **Faster inference** with API streaming

### Planned Features:
- **Conversational Input:** Instead of filling forms, user chats with the AI.
- **Dynamic Trait Recommendations:** AI suggests what traits to add.
- **Memory:** AI remembers preferences and previous analyses in a session.
- **Fun Personality:** Light humor while maintaining analytical accuracy.

---

## 📈 Project Roadmap
- **[✔]** Version 1 (C++ Console)
- **[✔]** Version 2 (Python GUI/CLI)
- **[🔄]** Version 3 (AI Chatbot – In Progress)
- **[ ]** Mobile App Integration
- **[ ]** Web-Based Version with Real-Time API

---


---

## ⚠ Disclaimer
This project is intended for **educational and entertainment purposes only**.  
It is not a scientific tool and should not be used to make real-life relationship decisions.

