/*-
 * Copyright (c) 2022-23 Simon Peter <probono@puredarwin.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef TRASHHANDLER_H
#define TRASHHANDLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

// TODO: Support Trash on non-root volumes. Verify the following logic with a Mac and implement it:
// When you put a file in the Trash and that file is located on a removable drive
// (such as an external hard drive, USB flash drive, or network drive), the file is moved
// to a hidden directory on that removable drive.
// Within this ".Trashes" directory, there are subdirectories named after the user's UID
// (user identifier). The actual numeric UID of the user on the system is used as the name
// of these subdirectories to ensure separation of trashed files between different users.
// So, the path to the ".Trashes" directory on a removable drive would look something like this:
// "/Volumes/YourRemovableDrive/.Trashes"
// Inside the ".Trashes" directory, you would find subdirectories named after user UIDs, like:
// "/Volumes/YourRemovableDrive/.Trashes/501"
// And within each of these UID-named subdirectories, trashed files are stored.

/**
 * @brief The TrashHandler class provides functionality to manage a "Trash" (virtual trash) for files and directories.
 */
class TrashHandler : public QObject {
Q_OBJECT

public:
    /**
     * @brief Constructs a TrashHandler object.
     * @param parent The parent QWidget (optional).
     */
    TrashHandler(QWidget *parent = nullptr);

    /**
     * @brief Moves files and directories to the "Trash" (virtual trash).
     * @param paths List of paths to files and directories to be moved to the trash.
     */
    void moveToTrash(const QStringList& paths);

    /**
     * @brief Empties the "Trash" by deleting all files and directories in the virtual trash.
     * @return True if the trash was emptied successfully, false otherwise.
     */
    static bool emptyTrash();

    /**
     * @brief Retrieves the path to the "Trash" directory.
     * @return The path to the trash directory.
     */
    static QString getTrashPath();

    /**
     * @brief Checks if the "Trash" is empty.
     * @return True if the trash is empty, false otherwise.
     */
    static bool isEmpty();

private:
    static QString m_trashPath; /**< The path to the trash directory. */
    QWidget *m_parent; /**< The parent QWidget used for displaying message boxes. */
    bool m_dialogShown = false; /**< Flag to track if the empty trash confirmation dialog has been shown. */
};

#endif // TRASHHANDLER_H
