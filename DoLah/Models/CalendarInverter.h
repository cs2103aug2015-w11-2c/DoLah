#pragma once
#include <Models/Calendar.h>

namespace DoLah {
    /**
     * @class CalendarInverter CalendarInverter.h Models/CalendarInverter.h
     * @brief This class contains the methods used to abstract the inverse operation of the
     * operations defined by relevant AbstractCommand derivative classes.
     *
     * As such they should generally be called in the revert() method of AbstractCommand derivative 
     * classes only. Conversely, revert() methods should not call Calendar functions directly but
     * instead go through here.
     */
    class CalendarInverter {
    public:
        CalendarInverter();
        ~CalendarInverter();

        /**
         * @brief Performs the inverse of the add operation on the given Calendar.
         * 
         * @param task The task that was added.
         * @param calendar The calendar to operate on.
         */
        static void invertAdd(AbstractTask *, Calendar *);

        /**
         * @brief Performs the inverse of the delete operation on the given Calendar.
         *
         * @param task The task that was deleted.
         * @param calendar The calendar to operate on.
         */
        static void invertDelete(AbstractTask *, Calendar *);

        /**
         * @brief Performs the inverse of the Edit operation on the given Calendar.
         *
         * @param task The task that was edited.
         * @param calendar The calendar to operate on.
         */
        static void invertEdit(AbstractTask *, Calendar *);

        /**
         * @brief Performs the inverse of the Clear operation on the given Calendar.
         *
         * @param taskList The vector of tasks that were deleted.
         * @param calendar The calendar to operate on.
         */
        static void invertClear(std::vector<AbstractTask*>, Calendar *);

        /**
         * @brief Performs the inverse of the Search operation on the given Calendar.
         * Currently not in use.
         *
         * @param taskList The string to search for.
         * @param calendar The calendar to operate on.
         */
        static void invertSearch(std::string, Calendar *);

        /**
         * @brief Performs the inverse of the setDone/setUndone operation on 
         * the given Calendar.
         *
         * @param task The task that had the done flag toggled.
         * @param calendar The calendar to operate on.
         */
        static void invertDone(AbstractTask *, Calendar *);

    private:
    };
}