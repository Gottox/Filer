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

#ifndef CUSTOMLISTVIEW_H
#define CUSTOMLISTVIEW_H

#include <QObject>
#include <QListView>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>

class CustomListView : public QListView {
    Q_OBJECT
public:
    
    CustomListView(QWidget* parent = nullptr);
    ~CustomListView();

    // We are subclassing QListView to access the protected function setPositionForIndex
    // which is used to set the icon coordinates for the icon view.
    // Also we paint the desktop picture behind the icons if requested.

    // Access the protected function setPositionForIndex directly
    inline void setPositionForIndex(const QPoint& position, const QModelIndex& index) {
        QListView::setPositionForIndex(position, index);
    }

    // Public function to get the item delegate for a given index
    QAbstractItemDelegate* getItemDelegateForIndex(const QModelIndex& index) const {
        return itemDelegate(index);
    }

    void requestDesktopPictureToBePainted(bool request);

    void paintEvent(QPaintEvent* event) override;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

signals:
    void dragEnterEventSignal(QDragEnterEvent *event);
    void dragMoveEventSignal(QDragMoveEvent *event);
    void dragLeaveEventSignal(QDragLeaveEvent *event);
    void dropEventSignal(QDropEvent *event);
    void startDragSignal(Qt::DropActions supportedActions);

private:
    bool should_paint_desktop_picture = false;


};

#endif // CUSTOMLISTVIEW_H