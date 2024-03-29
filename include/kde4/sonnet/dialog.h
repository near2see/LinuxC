// -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; -*-
/**
 * dialog.h
 *
 * Copyright (C)  2003  Zack Rusin <zack@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */
#ifndef SONNET_DIALOG_H
#define SONNET_DIALOG_H

#include <kdialog.h>

class QListWidgetItem;
class QModelIndex;

namespace Sonnet
{
    class BackgroundChecker;

    /**
     * @short Spellcheck dialog
     *
     * \code
     * Sonnet::Dialog = dlg=new Sonnet::Dialog(new Sonnet::BackgroundChecker(
     *          this), this);
     * //connect signals
     * ...
     * dlg->setBuffer( someText );
     * dlg->show();
     * \endcode
     *
     * You can change buffer inside a slot connected to done() signal
     * and spellcheck will continue with new data automatically.
     */
    class KDEUI_EXPORT Dialog : public KDialog
    {
        Q_OBJECT
    public:
        Dialog(BackgroundChecker *checker,
               QWidget *parent);
        ~Dialog();

        QString originalBuffer() const;
        QString buffer() const;

        void show();
        void activeAutoCorrect(bool _active);

        // Hide warning about done(), which is a slot in QDialog and a signal here.
        using KDialog::done;

    public Q_SLOTS:
        void setBuffer(const QString &);

    Q_SIGNALS:
        /**
         * The dialog won't be closed if you setBuffer() in slot connected to this signal
         *
         * Also emitted after stop() signal
         */
        void done( const QString& newBuffer );
        void misspelling( const QString& word, int start );
        void replace( const QString& oldWord, int start,
                      const QString& newWord );

        void stop();
        void cancel();
        void autoCorrect( const QString & currentWord, const QString & replaceWord );

        /**
         * Signal sends when spell checking is finished/stopped/completed
         * @since 4.1
         */
        void spellCheckStatus(const QString &);

        /**
         * Emitted when the user changes the language used for spellchecking,
         * which is shown in a combobox of this dialog.
         *
         * @param dictionary the new language the user selected
         * @since 4.1
         */
        void languageChanged( const QString &language );

    private Q_SLOTS:
        void slotMisspelling(const QString& word, int start );
        void slotDone();

        void slotFinished();
        void slotCancel();

        void slotAddWord();
        void slotReplaceWord();
        void slotReplaceAll();
        void slotSkip();
        void slotSkipAll();
        void slotSuggest();
        void slotChangeLanguage( const QString& );
        void slotSelectionChanged(const QModelIndex &);
        void slotAutocorrect();

    private:
        void updateDialog( const QString& word );
        void fillSuggestions( const QStringList& suggs );
        void initConnections();
        void initGui();
        void continueChecking();

    private:
        class Private;
        Private* const d;
        Q_DISABLE_COPY( Dialog )
    };
}

#endif
