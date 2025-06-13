/**
 * @file fileio.hpp
 * @brief This file contains the declarations for file I/O operations on notes.
 */

#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "notes.hpp"
#include <string>
#if __cplusplus < 201703L
#endif
#include <optional> // Ensure C++17 or later is enabled for std::optional

/**
 * @namespace fileio_notes
 * @brief This namespace contains functions for file I/O operations on notes.
 */
namespace fileio_notes {

/**
 * @brief Saves a note to a file.
 * @param note The note to save.
 * @return True if the note was saved successfully, false otherwise.
 */
bool saveNoteToFile(const Note& note);

/**
 * @brief Loads a note from a file by ID.
 * @param id The ID of the note to load.
 * @return An optional containing the note if it was loaded successfully, otherwise an empty optional.
 */
std::optional<Note> loadNoteFromFile(int id);

/**
 * @brief Deletes a note file.
 * @param id The ID of the note to delete.
 * @return True if the note file was deleted successfully, false otherwise.
 */
bool deleteNoteFile(int id);

/**
 * @brief Updates (rewrites) a note in a file.
 * @param note The note to update.
 * @return True if the note was updated successfully, false otherwise.
 */
bool updateNoteInFile(const Note& note);

} // namespace fileio_notes

#endif // FILEIO_NOTES_HPP
