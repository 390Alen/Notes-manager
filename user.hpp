/**
 * @file user.hpp
 * @brief This file contains the declaration of the User class.
 */

#ifndef USER_HPP
#define USER_HPP

#include "notes.hpp"

/**
 * @class User
 * @brief Represents a user of the application.
 *
 * This class currently holds a NoteManager instance. It can be expanded to include
 * user-specific settings and data.
 */
class User {
public:
    /**
     * @brief Default constructor for the User class.
     */
    User();

    /**
     * @brief Gets a reference to the NoteManager instance.
     * @return A reference to the NoteManager.
     */
    NoteManager& getNoteManager();

private:
    // The NoteManager instance for the user.
    NoteManager manager;
};

#endif // USER_HPP
