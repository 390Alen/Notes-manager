/**
 * @file settingsdialog.hpp
 * @brief This file contains the declaration of the SettingsDialog class.
 */

#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP

#include <QDialog>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QFileDialog>
 
/**
 * @class SettingsDialog
 * @brief A dialog for changing application settings.
 */
 class SettingsDialog : public QDialog {
     Q_OBJECT
 
 public:
     /**
      * @brief Constructs a SettingsDialog.
      * @param parent The parent widget.
      */
     explicit SettingsDialog(QWidget *parent = nullptr);
 
     /**
      * @brief Gets the selected background color.
      * @return The selected background color.
      */
     QColor getBackgroundColor() const;

     /**
      * @brief Gets the selected text color.
      * @return The selected text color.
      */
     QColor getTextColor() const;

     /**
      * @brief Gets the selected font family.
      * @return The selected font family.
      */
     QString getFontFamily() const;

     /**
      * @brief Gets the selected background type.
      * @return The selected background type.
      */
     QString getBackgroundType() const;

     /**
      * @brief Gets the path to the selected background image.
      * @return The path to the selected background image.
      */
     QString getBackgroundImagePath() const;
 
 signals:
    void settingsChanged(const QColor& backgroundColor, const QColor& textColor, const QString& fontFamily, const QString& backgroundType, const QString& backgroundImagePath);

 private slots:
     /**
      * @brief Opens a color dialog to choose the background color.
      */
     void chooseBackgroundColor();
 
     /**
      * @brief Opens a color dialog to choose the text color.
      */
     void chooseTextColor();
 
     /**
      * @brief Opens a file dialog to choose a background image.
      */
     void chooseBackgroundImage();

     void applySettings();
 
 private:
     QPushButton* backgroundColorButton;
     QPushButton* textColorButton;
     QFontComboBox* fontComboBox;
     QComboBox* backgroundTypeComboBox;
     QPushButton* backgroundImageButton;
     QColor backgroundColor;
     QColor textColor;
     QString backgroundImagePath;
 };

#endif // SETTINGSDIALOG_HPP