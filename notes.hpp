/**
 * @file notes.hpp
 * @brief This file contains the core data structures and class definitions for the note-taking application.
 */

#ifndef NOTES_HPP
#define NOTES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
#include <algorithm>
#include <map>
#include <filesystem> // Required for directory operations
#include <fstream>      // For file I/O
#include <chrono>       // For logging timestamps
#include <set>

// Forward declarations to resolve circular dependencies
class Note;
class Folder;
class Tag;
class NoteVersion;
class Reminder;
class ColorLabel;

/**
 * @class Tag
 * @brief Represents a tag that can be associated with a note.
 *
 * Tags are simple string identifiers used for categorizing and searching notes.
 * Each tag has a unique ID and a name. The NoteManager handles the creation
 * and lifecycle of tags.
 *
 * Each tag has a unique ID and a name. Tags help in organizing and searching for notes.
 */
class Tag {
    friend class NoteManager;
private:
    int id;
    std::string name;
    static int next_id;

public:
    /**
     * @brief Default constructor for Tag.
     */
    Tag();

    /**
     * @brief Constructs a Tag with a given name.
     * @param name The name of the tag.
     */
    explicit Tag(const std::string& name);

    /**
     * @brief Gets the unique ID of the tag.
     * @return The ID of the tag.
     */
    int getId() const;

    /**
     * @brief Gets the name of the tag.
     * @return The name of the tag.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the tag.
     * @param name The new name for the tag.
     */
    void setName(const std::string& name);

    /**
     * @brief Displays the details of the tag.
     */
    void display() const;
};

/**
 * @class Note
 * @brief Represents a single note.
 *
 * A note contains a title, content, creation and modification dates, a list of
 * associated tags, version history, and calculated metadata.
 */
class Note {
    friend class NoteManager;
private:
    int id;
    std::string title;
    std::string content;
    time_t creation_date;
    time_t last_modified_date;
    std::vector<std::shared_ptr<Tag>> tags;
    bool is_in_trash;
    std::vector<NoteVersion> history; // For version control
    std::vector<std::string> attachments; // For file attachments
    std::vector<Reminder> reminders; // For reminders
    std::shared_ptr<ColorLabel> color_label; // For color labels
    bool is_encrypted;
    int word_count;
    int char_count;
    static int next_id;

    /**
     * @brief Recalculates the word and character count for the note.
     * This is a private helper method called whenever the content is updated.
     */
    void updateMetadata();

public:
    /**
     * @brief Adds a file attachment path to the note.
     * @param file_path The path to the file to attach.
     */
    void addAttachment(const std::string& file_path);

    /**
     * @brief Removes a file attachment from the note.
     * @param file_path The path of the attachment to remove.
     */
    void removeAttachment(const std::string& file_path);

    /**
     * @brief Gets the list of attachments for the note.
     * @return A constant reference to the vector of attachment paths.
     */
    const std::vector<std::string>& getAttachments() const;

    /**
     * @brief Adds a reminder to the note.
     * @param reminder The reminder to add.
     */
    void addReminder(const Reminder& reminder);

    /**
     * @brief Gets the list of reminders for the note.
     * @return A constant reference to the vector of reminders.
     */
    const std::vector<Reminder>& getReminders() const;

    /**
     * @brief Sets the color label for the note.
     * @param label A shared pointer to the color label.
     */
    void setColorLabel(std::shared_ptr<ColorLabel> label);

    /**
     * @brief Gets the color label of the note.
     * @return A shared pointer to the color label.
     */
    std::shared_ptr<ColorLabel> getColorLabel() const;

    /**
     * @brief Encrypts the note's content using a simple XOR cipher.
     * @param key The encryption key.
     */
    void encrypt(const std::string& key);

    /**
     * @brief Decrypts the note's content using a simple XOR cipher.
     * @param key The decryption key.
     */
    void decrypt(const std::string& key);

    /**
     * @brief Checks if the note is encrypted.
     * @return True if the note is encrypted, false otherwise.
     */
    bool isEncrypted() const;
    /**
     * @brief Gets the word count of the note's content.
     * @return The number of words in the note.
     */
    int getWordCount() const;

    /**
     * @brief Gets the character count of the note's content.
     * @return The number of characters in the note.
     */
    int getCharCount() const;

    /**
     * @brief Adds a version to the note's history.
     * @param version The NoteVersion object to add.
     */
    void addVersion(const NoteVersion& version);

    /**
     * @brief Gets the entire version history of the note.
     * @return A constant reference to the vector of NoteVersion objects.
     */
    const std::vector<NoteVersion>& getHistory() const;

    /**
     * @brief Reverts the note's content to a specific version from its history.
     * @param version_index The index of the version to revert to.
     * @return True if the revert was successful, false otherwise (e.g., invalid index).
     */
    bool revertToVersion(size_t version_index);
    /**
     * @brief Checks if the note is currently in the trash.
     * @return True if the note is in the trash, false otherwise.
     */
    bool isInTrash() const;

    /**
     * @brief Sets the trash status of the note.
     * @param trashed The new trash status.
     */
    void setInTrash(bool trashed);
    /**
     * @brief Default constructor for Note.
     */
    Note();

    /**
     * @brief Constructs a Note with a title and content.
     * @param title The title of the note.
     * @param content The content of the note.
     */
    Note(const std::string& title, const std::string& content);

    /**
     * @brief Gets the unique ID of the note.
     * @return The ID of the note.
     */
    int getId() const;

    /**
     * @brief Gets the title of the note.
     * @return The title of the note.
     */
    std::string getTitle() const;

    /**
     * @brief Sets the title of the note.
     * @param title The new title for the note.
     */
    void setTitle(const std::string& title);

    /**
     * @brief Gets the content of the note.
     * @return The content of the note.
     */
    std::string getContent() const;

    /**
     * @brief Sets the content of the note.
     * @param content The new content for the note.
     */
    void setContent(const std::string& content);

    /**
     * @brief Gets the creation date of the note.
     * @return The creation date.
     */
    time_t getCreationDate() const;

    /**
     * @brief Gets the last modified date of the note.
     * @return The last modified date.
     */
    time_t getLastModifiedDate() const;

    /**
     * @brief Adds a tag to the note.
     * @param tag A shared pointer to the tag to be added.
     */
    void addTag(std::shared_ptr<Tag> tag);

    /**
     * @brief Removes a tag from the note.
     * @param tag_name The name of the tag to be removed.
     * @return True if the tag was removed, false otherwise.
     */
    bool removeTag(const std::string& tag_name);

    /**
     * @brief Gets the list of tags associated with the note.
     * @return A vector of shared pointers to the tags.
     */
    std::vector<std::shared_ptr<Tag> > getTags() const;

    /**
     * @brief Checks if the note has a specific tag.
     * @param tag_name The name of the tag to check for.
     * @return True if the note has the tag, false otherwise.
     */
    bool hasTag(const std::string& tag_name) const;

    /**
     * @brief Displays the details of the note.
     * @param detailed If true, shows detailed information including content and tags.
     */
    void display(bool detailed = false) const;
};

/**
 * @class Folder
 * @brief Represents a folder that can contain notes and other folders.
 *
 * Folders are used to organize notes in a hierarchical structure. Each folder
 * can contain notes and other subfolders, forming a tree-like organization.
 */
class Folder : public std::enable_shared_from_this<Folder> {
    friend class NoteManager;
private:
    int id;
    std::string name;
    std::weak_ptr<Folder> parent_folder;
    std::vector<std::shared_ptr<Note>> notes;
    std::vector<std::shared_ptr<Folder>> subfolders;
    bool is_in_trash;
    static int next_id;

public:
    /**
     * @brief Gets the total number of notes within this folder (non-recursively).
     * @return The count of notes directly in this folder.
     */
    size_t getNoteCount() const;

    /**
     * @brief Gets the total number of subfolders within this folder (non-recursively).
     * @return The count of subfolders directly in this folder.
     */
    size_t getSubfolderCount() const;

    /**
     * @brief Recursively calculates the total number of notes in this folder and all subfolders.
     * @return The total count of all notes contained within this folder's hierarchy.
     */
    size_t getTotalNoteCountRecursive() const;
    /**
     * @brief Checks if the folder is currently in the trash.
     * @return True if the folder is in the trash, false otherwise.
     */
    bool isInTrash() const;

    /**
     * @brief Sets the trash status of the folder.
     * @param trashed The new trash status.
     */
    void setInTrash(bool trashed);
    /**
     * @brief Default constructor for Folder.
     */
    Folder();

    /**
     * @brief Constructs a Folder with a given name.
     * @param name The name of the folder.
     */
    explicit Folder(const std::string& name);

    /**
     * @brief Gets the unique ID of the folder.
     * @return The ID of the folder.
     */
    int getId() const;

    /**
     * @brief Gets the name of the folder.
     * @return The name of the folder.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the folder.
     * @param name The new name for the folder.
     */
    void setName(const std::string& name);

    /**
     * @brief Sets the parent folder.
     * @param parent A weak pointer to the parent folder.
     */
    void setParent(std::weak_ptr<Folder> parent);

    /**
     * @brief Gets the parent folder.
     * @return A shared pointer to the parent folder.
     */
    std::shared_ptr<Folder> getParent() const;

    /**
     * @brief Adds a note to the folder.
     * @param note A shared pointer to the note to be added.
     */
    void addNote(std::shared_ptr<Note> note);

    /**
     * @brief Removes a note from the folder by its ID.
     * @param note_id The ID of the note to be removed.
     * @return A shared pointer to the removed note, or nullptr if not found.
     */
    std::shared_ptr<Note> removeNote(int note_id);

    /**
     * @brief Adds a subfolder to the folder.
     * @param subfolder A shared pointer to the subfolder to be added.
     */
    void addSubfolder(std::shared_ptr<Folder> subfolder);

    /**
     * @brief Removes a subfolder from the folder by its ID.
     * @param folder_id The ID of the subfolder to be removed.
     * @return A shared pointer to the removed subfolder, or nullptr if not found.
     */
    std::shared_ptr<Folder> removeSubfolder(int folder_id);

    /**
     * @brief Finds a note in the folder by its ID.
     * @param note_id The ID of the note to find.
     * @return A shared pointer to the note, or nullptr if not found.
     */
    std::shared_ptr<Note> findNoteById(int note_id);

    /**
     * @brief Finds a subfolder in the folder by its name.
     * @param folder_name The name of the subfolder to find.
     * @return A shared pointer to the subfolder, or nullptr if not found.
     */
    std::shared_ptr<Folder> findSubfolderByName(const std::string& folder_name);
    std::shared_ptr<Folder> findSubfolderByIdRecursive(int folder_id);

    /**
     * @brief Gets the list of notes in the folder.
     * @return A vector of shared pointers to the notes.
     */
    std::vector<std::shared_ptr<Note> > getNotes() const;

    /**
     * @brief Gets the list of subfolders in the folder.
     * @return A vector of shared pointers to the subfolders.
     */
    std::vector<std::shared_ptr<Folder> > getSubfolders() const;

    /**
     * @brief Displays the contents of the folder.
     * @param indent The indentation string for hierarchical display.
     */
    void display(const std::string& indent = "") const;
};

/**
 * @class ColorLabel
 * @brief Represents a color label that can be applied to a note.
 */
class ColorLabel {
private:
    std::string name;
    std::string hex_code; // e.g., "#FF0000"

public:
    ColorLabel(const std::string& name, const std::string& hex_code);
    std::string getName() const;
    std::string getHexCode() const;
};

/**
 * @class Reminder
 * @brief Represents a reminder with a due date.
 */
class Reminder {
private:
    time_t due_date;
    std::string description;
    bool completed;

public:
    Reminder(time_t due, const std::string& desc);
    time_t getDueDate() const;
    std::string getDescription() const;
    bool isCompleted() const;
    void markAsCompleted();
};

/**
 * @class NoteVersion
 * @brief Represents a snapshot of a note's content at a specific time.
 *
 * This class is used to maintain a history of changes for a Note object,
 * allowing for version tracking and restoration.
 */
class NoteVersion {
private:
    time_t version_date;
    std::string content_snapshot;

public:
    /**
     * @brief Constructs a NoteVersion.
     * @param content The content of the note at the time of versioning.
     */
    explicit NoteVersion(const std::string& content);

    /**
     * @brief Gets the date this version was created.
     * @return The version date as a time_t.
     */
    time_t getDate() const;

    /**
     * @brief Gets the content snapshot of this version.
     * @return The note content as a string.
     */
    std::string getContent() const;
};

/**
 * @class Logger
 * @brief A file logger with multiple logging levels.
 *
 * This logger writes timestamped and categorized messages to a specified file,
 * allowing for granular control over log output for debugging and monitoring.
 */
class Logger {
public:
    enum class Level { DEBUG, INFO, WARNING, ERROR };

    /**
     * @brief Constructs a Logger instance.
     * @param filename The path to the log file. Defaults to "app.log".
     */
    Logger(const std::string& filename = "app.log");

    /**
     * @brief Writes a message to the log file with a specific level.
     * @param level The logging level (e.g., Level::INFO).
     * @param message The message to be logged.
     */
    void log(Level level, const std::string& message);

private:
    std::ofstream log_file;
    std::string getTimestamp() const;
    std::string levelToString(Level level) const;
};

/**
 * @class ConfigManager
 * @brief Manages application configuration settings.
 *
 * This class handles reading from and writing to a configuration file (.conf),
 * allowing for persistent user settings like default author, date formats, etc.
 */
class ConfigManager {
public:
    /**
     * @brief Constructs a ConfigManager and loads settings from a file.
     * @param filename The name of the configuration file.
     */
    explicit ConfigManager(const std::string& filename = "app.conf");

    /**
     * @brief Gets a configuration value by key.
     * @param key The key of the setting to retrieve.
     * @param default_value The value to return if the key is not found.
     * @return The configuration value as a string.
     */
    std::string get(const std::string& key, const std::string& default_value = "") const;

    /**
     * @brief Sets a configuration value.
     * @param key The key of the setting to set.
     * @param value The value to store.
     */
    void set(const std::string& key, const std::string& value);

    /**
     * @brief Saves the current configuration to the file.
     * @return True if saving was successful, false otherwise.
     */
    bool save() const;

private:
    std::string config_filename;
    std::map<std::string, std::string> settings;

    /**
     * @brief Loads the configuration from the file.
     * @return True if loading was successful, false otherwise.
     */
    bool load();
};

/**
 * @class NoteManager
 * @brief Manages all notes, folders, and tags in the application.
 *
 * This class provides a high-level interface for all note-taking operations,
 * including file persistence, search, and trash management.
 */
class NoteManager {
private:
    std::shared_ptr<Folder> root_folder;
    std::shared_ptr<Folder> trash_folder; // For deleted items
    std::shared_ptr<Folder> current_folder;
    std::vector<std::shared_ptr<Tag>> all_tags;
    std::map<int, std::shared_ptr<Note>> all_notes_by_id;
    std::map<int, std::shared_ptr<Folder>> all_folders_by_id;
    std::unique_ptr<Logger> logger;
    std::unique_ptr<ConfigManager> config;

public:
    void log(const std::string& message);

    // --- Private Helper Methods ---

    /**
     * @brief Finds a tag by its name.
     * @param name The name of the tag to find.
     * @return A shared pointer to the tag, or nullptr if not found.
     */
    std::shared_ptr<Tag> findTagByName(const std::string& name);
    std::shared_ptr<Folder> findFolderByPath(const std::string& path);
    std::shared_ptr<Folder> findFolderByIdRecursive(std::shared_ptr<Folder> current, int id);
    std::shared_ptr<Note> findNoteByIdRecursive(std::shared_ptr<Folder> current, int id);
    std::shared_ptr<const Note> findNoteByIdRecursive(std::shared_ptr<const Folder> current, int id) const; // Const overload
    std::shared_ptr<Folder> findParentFolderOfNote(int note_id);
    std::string getPathForFolder(const std::shared_ptr<Folder>& folder) const;
    void createDirectoriesForFolder(const std::shared_ptr<Folder>& folder) const;
    void saveNoteToFile(const std::shared_ptr<Note>& note, const std::shared_ptr<Folder>& folder);
    void deleteNoteFile(const std::shared_ptr<Note>& note, const std::shared_ptr<Folder>& folder);
    void loadNotesFromDirectory(const std::string& path, std::shared_ptr<Folder> parent_folder);
    std::vector<std::string> parseTags(const std::string& tag_string);
    void recursivelyDeleteFolder(const std::shared_ptr<Folder>& folder);
    void recursivelyUpdatePaths(const std::shared_ptr<Folder>& folder, const std::string& old_base, const std::string& new_base);

public:
    /**
     * @brief Finds a note by its unique ID across all folders.
     * @param id The ID of the note to find.
     * @return A shared pointer to the note, or nullptr if not found.
     */
    std::shared_ptr<Note> findNoteById(int id);
    std::shared_ptr<const Note> findNoteById(int id) const; // Const overload
    std::shared_ptr<Folder> getRootFolder() const;
    std::shared_ptr<Folder> findFolderById(int id);
    /**
     * @brief Constructs a NoteManager and initializes the root folder.
     */
    NoteManager();

    // --- Folder Operations ---

    /**
     * @brief Creates a new folder in the current folder.
     * @param name The name of the new folder.
     * @return True if the folder was created successfully, false otherwise.
     */
    bool createFolder(const std::string& name);

    /**
     * @brief Deletes a folder.
     * @param name The name of the folder to delete.
     * @return True if the folder was deleted successfully, false otherwise.
     */
    bool deleteFolder(const std::string& name, bool permanent = false);

    /**
     * @brief Moves a folder to a new parent folder.
     * @param folder_id The ID of the folder to move.
     * @param new_parent_id The ID of the new parent folder.
     * @return True if the move was successful, false otherwise.
     */
    bool moveFolder(int folder_id, int new_parent_id);

    /**
     * @brief Renames a folder.
     * @param folder_id The ID of the folder to rename.
     * @param new_name The new name for the folder.
     * @return True if the rename was successful, false otherwise.
     */
    bool renameFolder(int folder_id, const std::string& new_name);

    /**
     * @brief Changes the current directory to a specified folder.
     * @param path The path to the folder (e.g., "folder1/subfolder").
     * @return True if the directory was changed successfully, false otherwise.
     */
    bool changeDirectory(const std::string& path);

    /**
     * @brief Lists the contents of the current folder.
     */
    void listContents() const;

    /**
     * @brief Gets the current working directory path as a string.
     * @return The path of the current folder.
     */
    std::string getCurrentPath() const;

    // --- Note Operations ---

    /**
     * @brief Creates a new note in the current folder.
     * @param title The title of the note.
     * @param content The content of the note.
     */
    void createNote(const std::string& title, const std::string& content, const std::vector<std::string>& tags = {});

    /**
     * @brief Deletes a note by its ID from the current folder.
     * @param note_id The ID of the note to delete.
     * @return True if the note was deleted successfully, false otherwise.
     */
    bool deleteNote(int note_id, bool permanent = false);

    /**
     * @brief Moves a note to a different folder.
     * @param note_id The ID of the note to move.
     * @param new_folder_id The ID of the destination folder.
     * @return True if the move was successful, false otherwise.
     */
    bool moveNote(int note_id, int new_folder_id);

    /**
     * @brief Renames a note.
     * @param note_id The ID of the note to rename.
     * @param new_title The new title for the note.
     * @return True if the rename was successful, false otherwise.
     */
    bool renameNote(int note_id, const std::string& new_title);

    /**
     * @brief Views a note by its ID from the current folder.
     * @param note_id The ID of the note to view.
     */
    void viewNote(int note_id) const;

    /**
     * @brief Edits a note by its ID.
     * @param note_id The ID of the note to edit.
     * @param new_title The new title for the note.
     * @param new_content The new content for the note.
     * @return True if the note was edited successfully, false otherwise.
     */
    bool editNote(int note_id, const std::string& new_title, const std::string& new_content);
    bool editNote(int note_id, const std::string& new_title, const std::string& new_content, const std::vector<std::string>& new_tags);

    /**
     * @brief Reverts a note to a previous version.
     * @param note_id The ID of the note to revert.
     * @param version_index The index in the history vector to revert to.
     * @return True if the reversion was successful, false otherwise.
     */
    bool revertNoteToVersion(int note_id, size_t version_index);

    // --- Tag Operations ---

    /**
     * @brief Creates a new tag.
     * @param name The name of the new tag.
     * @return True if the tag was created successfully, false otherwise.
     */
    bool createTag(const std::string& name);

    /**
     * @brief Deletes a tag.
     * @param name The name of the tag to delete.
     * @return True if the tag was deleted successfully, false otherwise.
     */
    bool deleteTag(const std::string& name);

    /**
     * @brief Lists all available tags.
     */
    void listTags() const;

    /**
     * @brief Adds a tag to a note.
     * @param note_id The ID of the note.
     * @param tag_name The name of the tag to add.
     * @return True if the tag was added successfully, false otherwise.
     */
    bool addTagToNote(int note_id, const std::string& tag_name);

    /**
     * @brief Removes a tag from a note.
     * @param note_id The ID of the note.
     * @param tag_name The name of the tag to remove.
     * @return True if the tag was removed successfully, false otherwise.
     */
    bool removeTagFromNote(int note_id, const std::string& tag_name);

    // --- Search Operations ---

    /**
     * @brief Searches for notes by a keyword in their title or content.
     * @param keyword The keyword to search for.
     * @return A vector of shared pointers to the matching notes.
     */
    std::vector<std::shared_ptr<Note>> searchNotesByKeyword(const std::string& keyword);

    /**
     * @brief Searches for notes by a tag.
     * @param tag_name The name of the tag to search for.
     * @return A vector of shared pointers to the matching notes.
     */
    std::vector<std::shared_ptr<Note>> searchNotesByTag(const std::string& tag_name);

    /**
     * @struct SearchCriteria
     * @brief Defines criteria for advanced note searching.
     */
    struct SearchCriteria {
        std::string keyword;
        std::vector<std::string> tags;
        time_t start_date = 0;
        time_t end_date = 0;
        bool search_in_trash = false;
    };

    /**
     * @brief Performs an advanced search for notes based on multiple criteria.
     * @param criteria The search criteria.
     * @return A vector of shared pointers to matching notes.
     */
    std::vector<std::shared_ptr<Note>> searchNotes(const SearchCriteria& criteria);

    // --- Trash Management ---

    /**
     * @brief Restores an item (note or folder) from the trash.
     * @param id The ID of the item to restore.
     * @param is_note True if the item is a note, false if it is a folder.
     * @return True if restoration was successful, false otherwise.
     */
    bool restoreItem(int id, bool is_note);

    /**
     * @brief Permanently deletes all items in the trash.
     */
    void emptyTrash();

    /**
     * @brief Gets the contents of the trash folder.
     * @return A pair containing a vector of trashed notes and a vector of trashed folders.
     */
    std::pair<std::vector<std::shared_ptr<Note>>, std::vector<std::shared_ptr<Folder>>> getTrashContents() const;


    // --- Import/Export Operations ---

    /**
     * @brief Exports a single note to a Markdown file.
     * @param note_id The ID of the note to export.
     * @param file_path The destination path for the Markdown file.
     * @return True if the export was successful, false otherwise.
     */
    bool exportNoteToMarkdown(int note_id, const std::string& file_path) const;

    /**
     * @brief Exports a single note to a JSON file.
     * @param note_id The ID of the note to export.
     * @param file_path The destination path for the JSON file.
     * @return True if the export was successful, false otherwise.
     */
    bool exportNoteToJson(int note_id, const std::string& file_path) const;

    /**
     * @brief Imports a note from a plain text file.
     * @param file_path The path to the text file to import.
     * @param destination_folder_id The ID of the folder to import the note into.
     * @return The ID of the newly created note, or -1 on failure.
     */
    int importNoteFromText(const std::string& file_path, int destination_folder_id);


    // --- Data Persistence ---
    /**
     * @brief Scans the data directory and loads all notes and folders into memory.
     * This is the main entry point for loading data when the application starts.
     * @param base_path The root directory for active notes.
     * @param trash_path The root directory for trashed items.
     */
    void initializeFromFileSystem(const std::string& base_path = "data", const std::string& trash_path = "trash");

    // --- Utility Functions ---
    /**
     * @brief Trims whitespace from the beginning and end of a string.
     * @param str The string to trim.
     * @return The trimmed string.
     */
    static std::string trim(const std::string& str);

    /**
     * @brief Converts a note's content from Markdown to HTML.
     * @param note_id The ID of the note to convert.
     * @return A string containing the HTML representation of the note's content.
     */
    std::string convertNoteToHtml(int note_id);
    std::set<std::shared_ptr<Tag>> getAllTags() const;
};

#endif // NOTES_HPP