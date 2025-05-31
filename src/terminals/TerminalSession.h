/**
 * @file TerminalSession.h
 * @brief Abstract base class for all user terminal sessions in the ChocAn system.
 * 
 * This class defines the common interface and shared behavior for different types
 * of terminal sessions such as Manager, Provider, and Operator terminals. It includes
 * the basic input handling and session control logic that is reused across child classes.
 * 
 * @date Created: May 16, 2025
 * @author 
 * Part of the Team Whitespace ChocAn Data Processing System – CS314 Project
 */

#ifndef TERMINAL_SESSION_H
#define TERMINAL_SESSION_H
#include <string>

/**
 * @class TerminalSession
 * @brief Abstract base class providing a generic terminal interface.
 * 
 * This class defines a standard interface and shared functionality
 * for derived classes that represent specific user roles.
 */
class TerminalSession {
    public:

        /// @brief Default constructor.
        TerminalSession();

        /// @brief Virtual destructor.
        virtual ~TerminalSession();
        
        /**
         * @brief Starts and manages the terminal session.
         * 
         * This function runs the menu loop by repeatedly displaying the menu
         * and processing user input until the user selects the exit option.
         */
        void    runSession();

        /**
         * @brief Sets the current user's ID.
         * @param ID The string ID of the user currently logged in.
         */
        void    setCurrentUserID(const std::string& ID);

        /**
         * @brief Displays the session menu options.
         * 
         * Must be overridden by derived classes to display role-specific options.
         * @return The number of valid menu options available.
         */
        virtual int     showMenu() =0;

         /**
         * @brief Handles the command associated with a given menu selection.
         * 
         * Must be implemented by derived classes to execute role-specific functionality.
         * @param input The integer input corresponding to the user's selected option.
         */
        virtual void    commandHandler(int input) =0;

    protected:
        std::string userID; // ID of the current user.

        ////////// Helper Function /////////

        /**
         * @brief Retrieves a validated integer input from the user.
         * @return An integer entered by the user.
         */
        int getInput() const;

         /**
         * @brief Prompts and retrieves a string input from the user.
         * @param input Reference to the string variable to store input.
         * @param prompt Custom prompt message for the input request.
         */
        void getInput(std::string &input, const std::string &prompt = "Enter a value: ");

        /**
         * @brief Validates the format of a user ID.
         * 
         * The ID must contain only digits and be 8 or 9 characters long.
         * @param ID The ID string to validate.
         * @return True if valid, false otherwise.
         */
        bool validateIDFormat(const std::string & ID) const;

        /**
         * @brief Checks whether a string consists only of numeric digits.
         * @param str The string to check.
         * @return True if the string contains only digits, false otherwise.
         */
        bool is_digits(const std::string &str) const;
};

#endif  // TERMINAL_SESSION_H