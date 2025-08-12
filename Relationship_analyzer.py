import sys
from PySide6.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QVBoxLayout, QSlider,
    QHBoxLayout, QComboBox, QStackedWidget, QRadioButton, QButtonGroup, QLineEdit
)
from PySide6.QtCore import Qt

class IntroWindow(QWidget):
    def __init__(self, stacked_widget):
        super().__init__()
        self.stacked_widget = stacked_widget
        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()
        label = QLabel("Welcome to the Relationship Analyzer!")
        label.setAlignment(Qt.AlignCenter)
        layout.addWidget(label)

        self.gender_group = QButtonGroup(self)
        bf_button = QRadioButton("Compare Boyfriends")
        gf_button = QRadioButton("Compare Girlfriends")
        self.gender_group.addButton(bf_button)
        self.gender_group.addButton(gf_button)
        layout.addWidget(bf_button)
        layout.addWidget(gf_button)

        next_btn = QPushButton("Next")
        next_btn.clicked.connect(self.go_to_name_input)
        layout.addWidget(next_btn)
        self.setLayout(layout)

    def go_to_name_input(self):
        self.stacked_widget.setCurrentIndex(1)


class NameInputWindow(QWidget):
    def __init__(self, stacked_widget):
        super().__init__()
        self.stacked_widget = stacked_widget
        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()
        self.name1 = QLineEdit()
        self.name2 = QLineEdit()
        self.name1.setPlaceholderText("Enter first partner's name")
        self.name2.setPlaceholderText("Enter second partner's name")

        layout.addWidget(self.name1)
        layout.addWidget(self.name2)

        next_btn = QPushButton("Next")
        next_btn.clicked.connect(self.go_to_weight_input)
        layout.addWidget(next_btn)

        self.setLayout(layout)

    def go_to_weight_input(self):
        weight_window.partner_names = (self.name1.text(), self.name2.text())
        trait_window.partner_names = weight_window.partner_names
        self.stacked_widget.setCurrentIndex(2)


class WeightInputWindow(QWidget):
    def __init__(self, stacked_widget):
        super().__init__()
        self.stacked_widget = stacked_widget
        self.trait_weights = {}
        self.partner_names = ("Partner 1", "Partner 2")
        self.init_ui()

    def init_ui(self):
        self.layout = QVBoxLayout()
        self.layout.addWidget(QLabel("Assign importance (weights) to each trait:"))

        self.traits = [
            "Intelligence", "Spirituality", "Family Values",
            "Ambition", "Health", "Personality"
        ]

        for trait in self.traits:
            trait_layout = QHBoxLayout()
            label = QLabel(trait)
            slider = QSlider(Qt.Horizontal)
            slider.setRange(0, 10)
            slider.setValue(5)
            value_label = QLabel("5")
            slider.valueChanged.connect(lambda val, l=value_label: l.setText(str(val)))

            trait_layout.addWidget(label)
            trait_layout.addWidget(slider)
            trait_layout.addWidget(value_label)

            self.layout.addLayout(trait_layout)
            self.trait_weights[trait] = slider

        next_btn = QPushButton("Next")
        next_btn.clicked.connect(self.go_to_trait_input)
        self.layout.addWidget(next_btn)
        self.setLayout(self.layout)

    def go_to_trait_input(self):
        trait_window.weights = {
            trait: slider.value() for trait, slider in self.trait_weights.items()
        }
        trait_window.load_partner(0)
        self.stacked_widget.setCurrentIndex(3)


class TraitInputWindow(QWidget):
    def __init__(self, stacked_widget):
        super().__init__()
        self.stacked_widget = stacked_widget
        self.partner_data = [None, None]
        self.current_index = 0
        self.partner_names = ("Partner 1", "Partner 2")
        self.weights = {}
        self.init_ui()

    def init_ui(self):
        self.layout = QVBoxLayout()
        self.trait_sliders = {}

        self.label = QLabel()
        self.layout.addWidget(self.label)

        self.education = QComboBox()
        self.education.addItems(["High School", "College", "University"])
        self.layout.addWidget(QLabel("Education"))
        self.layout.addWidget(self.education)

        self.traits = [
            "Intelligence", "Spirituality", "Family Values",
            "Ambition", "Health", "Personality"
        ]

        for trait in self.traits:
            trait_layout = QHBoxLayout()
            label = QLabel(trait)
            slider = QSlider(Qt.Horizontal)
            slider.setRange(0, 10)
            slider.setValue(5)
            value_label = QLabel("5")
            slider.valueChanged.connect(lambda val, l=value_label: l.setText(str(val)))

            trait_layout.addWidget(label)
            trait_layout.addWidget(slider)
            trait_layout.addWidget(value_label)

            self.layout.addLayout(trait_layout)
            self.trait_sliders[trait] = slider

        self.vaccine_box = QComboBox()
        self.vaccine_box.addItems(["Yes", "No"])
        self.layout.addWidget(QLabel("Vaccinated?"))
        self.layout.addWidget(self.vaccine_box)

        self.next_btn = QPushButton("Next")
        self.next_btn.clicked.connect(self.save_data_and_continue)
        self.layout.addWidget(self.next_btn)

        self.setLayout(self.layout)

    def load_partner(self, index):
        self.current_index = index
        self.label.setText(f"Enter traits for {self.partner_names[index]}")

    def save_data_and_continue(self):
        data = {
            "Education": self.education.currentText(),
            "Traits": {trait: slider.value() for trait, slider in self.trait_sliders.items()},
            "Vaccinated": self.vaccine_box.currentText()
        }
        self.partner_data[self.current_index] = data

        if self.current_index == 0:
            self.load_partner(1)
        else:
            result_window.set_data(self.partner_names, self.partner_data, self.weights)
            self.stacked_widget.setCurrentIndex(4)


class ResultWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.layout = QVBoxLayout()
        self.result_label = QLabel()
        self.result_label.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.result_label)
        self.setLayout(self.layout)

    def set_data(self, names, data, weights):
        def score(partner):
            edu_weight = {"High School": 5, "College": 7, "University": 9}
            total = edu_weight[partner["Education"]]
            total += 10 if partner["Vaccinated"] == "Yes" else 0
            for trait, value in partner["Traits"].items():
                total += value * weights.get(trait, 1)
            return total

        score1 = score(data[0])
        score2 = score(data[1])

        if score1 == score2:
            better = "It's a tie!"
        else:
            better = names[0] if score1 > score2 else names[1]

        summary = f"{names[0]}'s Score: {score1}\n"
        summary += f"{names[1]}'s Score: {score2}\n\n"
        summary += f"💖 Better Match: {better}"
        self.result_label.setText(summary)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    stacked_widget = QStackedWidget()

    intro_window = IntroWindow(stacked_widget)
    name_window = NameInputWindow(stacked_widget)
    weight_window = WeightInputWindow(stacked_widget)
    trait_window = TraitInputWindow(stacked_widget)
    result_window = ResultWindow()

    stacked_widget.addWidget(intro_window)
    stacked_widget.addWidget(name_window)
    stacked_widget.addWidget(weight_window)
    stacked_widget.addWidget(trait_window)
    stacked_widget.addWidget(result_window)

    stacked_widget.setFixedSize(420, 520)
    stacked_widget.setCurrentIndex(0)
    stacked_widget.show()

    sys.exit(app.exec())
