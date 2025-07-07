#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void resultsReady();

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void switchToNextPage();
    void proceedFromGreeting();
    void proceedFromConfirmation();
    void proceedFromNames();
    void proceedFromTraits();
    void updateSliderValue(int value);
    void proceedFromWeights();

private:
    QStackedWidget *stackedWidget;

    // Pages and input fields
    QLineEdit *userNameEdit;
    QLineEdit *girlfriend1NameEdit;
    QLineEdit *girlfriend2NameEdit;
    QLabel *traitLabel;
    QLabel *sliderLabel;
    QSlider *currentSlider;
    QPushButton *nextButton;

    // Names and traits
    QString girlfriend1Name;
    QString girlfriend2Name;
    QString currentGirlfriendName;  // To store current girlfriend's name
    int currentGirlfriendIndex;     // To store the index of the current girlfriend (0 or 1)
    std::vector<int> girlfriend1Traits;
    std::vector<int> girlfriend2Traits;
    std::vector<int> traitWeights;

    // Trait names
    QStringList traitNames = {"Intelligence", "Spirituality", "Family Values", "Personality", "Ambition", "Health", "Body Weight"};

    // Weight sliders
    std::vector<QSlider*> weightSliders;

    // Current processing state
    int currentTraitIndex = 0;
    QString currentGirlfriend;

    // Create pages for each step
    QWidget *createGreetingPage();
    QWidget *createConfirmationPage();
    QWidget *createNamesPage();
    QWidget *createTraitsPage();
    QWidget *createWeightsPage();
    QWidget *createResultsPage();
};

#endif // MAINWINDOW_H


