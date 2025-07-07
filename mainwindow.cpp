#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {
    setCentralWidget(stackedWidget);

    // Initialize vectors for traits and weights
    girlfriend1Traits.resize(traitNames.size(), 0);
    girlfriend2Traits.resize(traitNames.size(), 0);
    traitWeights.resize(traitNames.size(), 0);

    // Add pages to the stacked widget
    stackedWidget->addWidget(createGreetingPage());
    stackedWidget->addWidget(createConfirmationPage());
    stackedWidget->addWidget(createNamesPage());
    stackedWidget->addWidget(createTraitsPage());
    stackedWidget->addWidget(createWeightsPage());
    stackedWidget->addWidget(createResultsPage());
}

void MainWindow::switchToNextPage() {
    int currentIndex = stackedWidget->currentIndex();
    if (currentIndex < stackedWidget->count() - 1) {
        stackedWidget->setCurrentIndex(currentIndex + 1);
    }
}

void MainWindow::proceedFromGreeting() {
    QString name = userNameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your name.");
        return;
    }
    currentGirlfriend = "Girlfriend 1";
    switchToNextPage();
}

void MainWindow::proceedFromConfirmation() {
    switchToNextPage();
}

void MainWindow::proceedFromNames() {
    QString girlfriend1 = girlfriend1NameEdit->text().trimmed();
    QString girlfriend2 = girlfriend2NameEdit->text().trimmed();

    if (girlfriend1.isEmpty() || girlfriend2.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both names.");
        return;
    }

    // Assign names to member variables
    girlfriend1Name = girlfriend1;
    girlfriend2Name = girlfriend2;

    // Start with the first girlfriend
    currentGirlfriendIndex = 0; // Index for girlfriend 1
    currentGirlfriendName = girlfriend1Name; // Set the name for girlfriend 1

    currentGirlfriend = girlfriend1Name;//"c"; // Optional, depending on usage

    switchToNextPage(); // Proceed to the traits page
}


void MainWindow::proceedFromTraits() {
    int value = currentSlider->value();

    if (currentGirlfriend == girlfriend1Name) {
        girlfriend1Traits[currentTraitIndex] = value;
    } else {
        girlfriend2Traits[currentTraitIndex] = value;
    }

    currentTraitIndex++;
    if (currentTraitIndex < traitNames.size()) {
        traitLabel->setText("Current Trait: " + traitNames[currentTraitIndex]);
        sliderLabel->setText(currentGirlfriend + " - " + traitNames[currentTraitIndex] + ": 0");
        currentSlider->setValue(0);
        return;
    }

    if (currentGirlfriend == girlfriend1Name) {
        currentGirlfriend = girlfriend2Name;
        currentTraitIndex = 0;
        traitLabel->setText("Current Trait: " + traitNames[currentTraitIndex]);
        sliderLabel->setText(currentGirlfriend + " - " + traitNames[currentTraitIndex] + ": 0");
        currentSlider->setValue(0);
        return;
    }

    switchToNextPage(); // Move to weights page after all traits are set
}

void MainWindow::updateSliderValue(int value) {
    sliderLabel->setText(currentGirlfriend + " - " + traitNames[currentTraitIndex] + ": " + QString::number(value));
}

void MainWindow::proceedFromWeights() {
    for (size_t i = 0; i < weightSliders.size(); ++i) {
        traitWeights[i] = weightSliders[i]->value();
    }

    emit resultsReady();

    switchToNextPage();
}

QWidget *MainWindow::createGreetingPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QLabel *label = new QLabel("Welcome to the Girlfriend Analyzer!");
    userNameEdit = new QLineEdit;
    userNameEdit->setPlaceholderText("Enter your name...");
    QPushButton *proceedButton = new QPushButton("Proceed");
    connect(proceedButton, &QPushButton::clicked, this, &MainWindow::proceedFromGreeting);

    layout->addWidget(label);
    layout->addWidget(userNameEdit);
    layout->addWidget(proceedButton);

    return page;
}

QWidget *MainWindow::createConfirmationPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QLabel *label = new QLabel("Would you like to use the Girlfriend Analyzer?");
    QPushButton *yesButton = new QPushButton("Yes");
    connect(yesButton, &QPushButton::clicked, this, &MainWindow::proceedFromConfirmation);

    layout->addWidget(label);
    layout->addWidget(yesButton);

    return page;
}

QWidget *MainWindow::createNamesPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QLabel *label = new QLabel("Enter the names of your two girlfriends:");
    girlfriend1NameEdit = new QLineEdit;
    girlfriend2NameEdit = new QLineEdit;
    girlfriend1NameEdit->setPlaceholderText("Girlfriend 1");
    girlfriend2NameEdit->setPlaceholderText("Girlfriend 2");

    QPushButton *proceedButton = new QPushButton("Proceed");
    connect(proceedButton, &QPushButton::clicked, this, &MainWindow::proceedFromNames);

    layout->addWidget(label);
    layout->addWidget(girlfriend1NameEdit);
    layout->addWidget(girlfriend2NameEdit);
    layout->addWidget(proceedButton);

    return page;
}

QWidget *MainWindow::createTraitsPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Update the currentGirlfriendName based on currentGirlfriendIndex
    currentGirlfriendName = (currentGirlfriendIndex == 0) ? girlfriend1Name : girlfriend2Name;

    // Label for current trait
    traitLabel = new QLabel("Current Trait: " + traitNames[currentTraitIndex]);
    traitLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");

    // Label to display girlfriend's name and current trait value
    sliderLabel = new QLabel(currentGirlfriendName + " - " + traitNames[currentTraitIndex] + ": 0");
    sliderLabel->setStyleSheet("font-size: 14px;");

    // Slider for the current trait
    currentSlider = new QSlider(Qt::Horizontal);
    currentSlider->setRange(0, 10);
    currentSlider->setValue(0);
    connect(currentSlider, &QSlider::valueChanged, this, &MainWindow::updateSliderValue);

    // Button to proceed to the next trait
    nextButton = new QPushButton("Next Trait");
    nextButton->setStyleSheet("margin-top: 15px; font-size: 14px;");
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::proceedFromTraits);

    // Add widgets to the layout
    layout->addWidget(traitLabel);
    layout->addWidget(sliderLabel);
    layout->addWidget(currentSlider);
    layout->addWidget(nextButton);

    return page;
}


QWidget *MainWindow::createWeightsPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QLabel *label = new QLabel("Adjust weights for each trait:");
    label->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px;");
    layout->addWidget(label);

    for (const QString &trait : traitNames) {
        QHBoxLayout *traitLayout = new QHBoxLayout;

        // Trait label
        QLabel *traitLabel = new QLabel(trait);
        traitLabel->setStyleSheet("font-size: 14px;");

        // Slider
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setRange(0, 10);
        slider->setValue(5); // Default weight
        weightSliders.push_back(slider);

        // Value display
        QLabel *valueLabel = new QLabel(QString::number(slider->value()));
        valueLabel->setFixedWidth(30);
        valueLabel->setAlignment(Qt::AlignCenter);

        // Connect slider movement to update the label
        connect(slider, &QSlider::valueChanged, valueLabel, [valueLabel](int value) {
            valueLabel->setText(QString::number(value));
        });

        // Add widgets to the horizontal layout
        traitLayout->addWidget(traitLabel);
        traitLayout->addWidget(slider);
        traitLayout->addWidget(valueLabel);

        // Add the horizontal layout to the main layout
        layout->addLayout(traitLayout);
    }

    // Proceed button
    QPushButton *proceedButton = new QPushButton("Proceed");
    proceedButton->setStyleSheet("margin-top: 20px; font-size: 14px;");
    connect(proceedButton, &QPushButton::clicked, this, &MainWindow::proceedFromWeights);

    layout->addWidget(proceedButton);

    return page;
}


QWidget *MainWindow::createResultsPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QLabel *titleLabel = new QLabel("Results");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    QLabel *girlfriend1Label = new QLabel;
    QLabel *girlfriend2Label = new QLabel;

    QPushButton *exitButton = new QPushButton("Exit");
    connect(exitButton, &QPushButton::clicked, this, &QMainWindow::close);

    layout->addWidget(titleLabel);
    layout->addWidget(girlfriend1Label);
    layout->addWidget(girlfriend2Label);
    layout->addWidget(exitButton);

    // Calculate and set the results dynamically
    connect(this, &MainWindow::resultsReady, [=]() {
        int score1 = 0, score2 = 0;
        for (size_t i = 0; i < traitWeights.size(); ++i) {
            score1 += girlfriend1Traits[i] * traitWeights[i];
            score2 += girlfriend2Traits[i] * traitWeights[i];
        }

        QString resultText1 = QString("%1's Total Score: %2").arg(girlfriend1Name).arg(score1);
        QString resultText2 = QString("%1's Total Score: %2").arg(girlfriend2Name).arg(score2);

        girlfriend1Label->setText(resultText1);
        girlfriend2Label->setText(resultText2);

        if (score1 > score2) {
            girlfriend1Label->setStyleSheet("color: green; font-weight: bold;");
            girlfriend2Label->setStyleSheet("color: red;");
        } else if (score1 < score2) {
            girlfriend2Label->setStyleSheet("color: green; font-weight: bold;");
            girlfriend1Label->setStyleSheet("color: red;");
        } else {
            girlfriend1Label->setStyleSheet("color: orange; font-weight: bold;");
            girlfriend2Label->setStyleSheet("color: orange; font-weight: bold;");
        }
    });

    return page;
}


