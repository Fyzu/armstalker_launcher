/***************************************************************************
 * This file is part of ArmSTALKER.
 *
 * ArmSTALKER is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArmSTALKER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ArmSTALKER. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef ARMSTALKER_LAUNCHER_LAUNCHER_VIEW_H
#define ARMSTALKER_LAUNCHER_LAUNCHER_VIEW_H

#include <QMainWindow>
#include <QPushButton>

#include "src/launcher/base/presenters/LauncherPresenter.h"
#include "src/core/base/view/BaseView.h"
#include "src/launcher/base/widgets/SlidingStackedWidget.h"

#define STYLE_PATH ":/qdarkstyle/darkstyle.css"

class LauncherPresenter;

class LauncherView : public QMainWindow, public BaseCore {

Q_OBJECT

public:

    LauncherView();

    ~LauncherView();

    void insertView(int index, QWidget *widget);

    void showView(int index);

private:

    LauncherPresenter *launcherPresenter;

    SlidingStackedWidget *stackedWidget;
    QPushButton *backButton;

    void setupUi();

signals:

    void viewChange(int);

public slots:

    void onBackButtonClicked();

    void onChangeViewFinished(int);
};


#endif //ARMSTALKER_LAUNCHER_LAUNCHER_VIEW_H
