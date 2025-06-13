/**
 * @file ui.hpp
 * @brief This file contains the declaration of the MainWindow class and other UI-related classes.
 */

#ifndef UI_HPP
#define UI_HPP

#include <QMainWindow>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QSplitter>
#include <QTextBrowser>
#include "notes.hpp"
#include "settingsdialog.hpp"
 
#include <QGraphicsView>
#include <QGraphicsScene>

/**
 * @class SearchDialog
 * @brief A dialog for performing advanced searches.
 */
 class SearchDialog : public QDialog {
     Q_OBJECT
 public:
    /**
     * @brief Constructs a SearchDialog.
     * @param parent The parent widget.
     */
    SearchDialog(QWidget* parent = nullptr);

    /**
     * @brief Gets the search criteria from the dialog.
     * @return The search criteria.
     */
    NoteManager::SearchCriteria getCriteria() const;
 private:
    QLineEdit* keywordEdit;
    QLineEdit* tagsEdit;
    QDateTimeEdit* startDateEdit;
    QDateTimeEdit* endDateEdit;
    QCheckBox* searchTrashCheck;
};

/**
 * @class NotePropertiesDialog
 * @brief A dialog for viewing and editing note properties.
 */
class NotePropertiesDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Constructs a NotePropertiesDialog.
     * @param note The note to display the properties of.
     * @param parent The parent widget.
     */
    NotePropertiesDialog(const std::shared_ptr<Note>& note, QWidget* parent = nullptr);

    /**
     * @brief Gets the title from the dialog.
     * @return The title.
     */
    std::string getTitle() const;

    /**
     * @brief Gets the tags from the dialog.
     * @return The tags.
     */
    std::string getTags() const;
private:
    QLineEdit* titleEdit;
    QLineEdit* tagsEdit;
};

/**
 * @class MainWindow
 * @brief The main window of the application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow.
     * @param manager A reference to the NoteManager.
     * @param parent The parent widget.
     */
    explicit MainWindow(NoteManager& manager, QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow() override;

private slots:
    // --- Action Slots ---
    /**
     * @brief Slot for creating a new note.
     */
    void onNewNote();

    /**
     * @brief Slot for creating a new folder.
     */
    void onNewFolder();

    /**
     * @brief Slot for creating a new tag.
     */
    void onNewTag();

    /**
     * @brief Slot for deleting an item.
     */
    void onDeleteItem();

    /**
     * @brief Slot for saving a note.
     */
    void onSaveNote();

    /**
     * @brief Slot for when a folder is selected.
     * @param item The selected item.
     * @param column The selected column.
     */
    void onFolderSelected(QTreeWidgetItem* item, int column);

    /**
     * @brief Slot for when a note is selected.
     * @param item The selected item.
     */
    void onNoteSelected(QListWidgetItem* item);

    /**
     * @brief Slot for performing an advanced search.
     */
    void onAdvancedSearch();

    /**
     * @brief Slot for showing the trash.
     */
    void onShowTrash();

    /**
     * @brief Slot for emptying the trash.
     */
    void onEmptyTrash();

    /**
     * @brief Slot for showing the logs.
     */
    void onShowLogs();

    /**
     * @brief Slot for moving a note.
     */
    void onMoveNote();

    /**
     * @brief Slot for showing the note properties.
     */
    void onNoteProperties();

    /**
     * @brief Slot for switching to the light theme.
     */
    void onLightTheme();

    /**
     * @brief Slot for switching to the dark theme.
     */
    void onDarkTheme();

    /**
     * @brief Slot for switching to the sepia theme.
     */
    void onSepiaTheme();

    /**
     * @brief Slot for switching to the yellow theme.
     */
    void onYellowTheme();

    /**
     * @brief Slot for showing the hotkeys.
     */
    void showHotkeys();

    /**
     * @brief Slot for closing the logs.
     */
    void closeLogs();
 
   /**
    * @brief Slot for opening the settings dialog.
    */
   void openSettings();

   /**
    * @brief Slot for renaming an item.
    */
   void onRenameItem();

   /**
    * @brief Slot for switching to the board view.
    */
   void switchToBoardView();
   void switchToMainView();
   void applyTheme(const QColor& backgroundColor, const QColor& textColor, const QString& fontFamily, const QString& backgroundType, const QString& backgroundImagePath);

  private:
      // --- UI Setup ---
      /**
       * @brief Sets up the UI.
       */
      void setupUI();

    /**
     * @brief Sets up the menu bar.
     */
    void setupMenuBar();

    /**
     * @brief Sets up the tool bar.
     */
    void setupToolBar();

    /**
     * @brief Sets up the connections.
     */
    void setupConnections();

    /**
     * @brief Applies the styles.
     */
    void applyStyles();

    // --- Data Loading & UI Refreshing ---
    /**
     * @brief Loads the folder tree.
     */
    void loadFolderTree();

    /**
     * @brief Populates a folder in the folder tree.
     * @param parentItem The parent item.
     * @param folder The folder to populate.
     */
    void populateFolder(QTreeWidgetItem* parentItem, const std::shared_ptr<Folder>& folder);

    /**
     * @brief Loads the notes for a folder.
     * @param folder The folder to load the notes for.
     */
    void loadNotesForFolder(const std::shared_ptr<Folder>& folder);

    /**
     * @brief Refreshes the UI.
     */
    void refreshUI();

    // --- Core Components ---
    NoteManager& noteManager;

    // --- Main Widgets ---
    QSplitter* mainSplitter;
    QTreeWidget* folderTree;
    QListWidget* noteList;
    QTextEdit* noteEditor;
    QTextBrowser* logViewer; // For displaying logs
    QGraphicsView* boardView;
    QGraphicsScene* boardScene;
 
    // --- Actions ---
    QAction* newNoteAction;
    QAction* newFolderAction;
    QAction* newTagAction;
    QAction* deleteAction;
    QAction* saveAction;
    QAction* searchAction;
    QAction* trashAction;
    QAction* emptyTrashAction;
    QAction* logAction;
    QAction* moveNoteAction;
    QAction* propertiesAction;
    QAction* lightThemeAction;
    QAction* darkThemeAction;
    QAction* sepiaThemeAction;
    QAction* yellowThemeAction;
    QAction* hotkeysAction;
    QAction* settingsAction;
    QAction* renameAction;
    QAction* boardViewAction;
    QAction* closeBoardViewAction;
 
        // --- State Tracking ---
        std::shared_ptr<Folder> currentFolder;
    std::shared_ptr<Note> currentNote;
};

#endif // UI_HPP
