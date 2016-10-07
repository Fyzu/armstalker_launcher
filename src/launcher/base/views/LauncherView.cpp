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

#include "LauncherView.h"

LauncherView::LauncherView() : QMainWindow(), BaseCore("LauncherView") {

    Logger::debug(TAG, "LauncherView");

    setupUi();

    connect(backButton, &QPushButton::clicked, this, &LauncherView::onBackButtonClicked);
    connect(stackedWidget, &QStackedWidget::currentChanged, this, &LauncherView::onChangeViewFinished);

    launcherPresenter = new LauncherPresenter(this);

}

LauncherView::~LauncherView() {

    Logger::debug(TAG, "~LauncherView");

    delete launcherPresenter;
    delete stackedWidget;
    delete backButton;
}

void LauncherView::setupUi() {

    // Настройки главного окна
    this->resize(667, 682);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    QFont font;
    font.setBold(false);
    font.setWeight(50);
    this->setFont(font);

    stackedWidget = new SlidingStackedWidget(this);
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
    stackedWidget->setSizePolicy(sizePolicy1);
    stackedWidget->setFrameShape(QFrame::NoFrame);
    stackedWidget->setFrameShadow(QFrame::Plain);
    stackedWidget->setLineWidth(0);
    setCentralWidget(stackedWidget);

    backButton = new QPushButton(this);
    backButton->setGeometry(QRect(160, 160, 25, 25));
    backButton->setMinimumSize(QSize(25, 25));
    backButton->setMaximumSize(QSize(25, 25));
    backButton->setFocusPolicy(Qt::NoFocus);
    backButton->setStyleSheet(
            "QPushButton { border-image: url(:/icons/images/darkstyle/return10.png) }\n"
                    "QPushButton::pressed { border-image: url(:/icons/images/return10.png) }"
    );
    backButton->move(14, 4);
}

void LauncherView::insertView(int index, QWidget *widget) {

    Logger::debug(TAG, "insertView") << "Insert view to stack -" << widget->objectName();

    stackedWidget->insertWidget(index, widget);
}

void LauncherView::showView(int viewTypeIndex) {

    Logger::debug(TAG, "showView") << "viewIndex -" << viewTypeIndex;



    stackedWidget->showWidget(viewTypeIndex);
    backButton->hide();
}

void LauncherView::onBackButtonClicked() {
    emit viewChange(LauncherPresenter::DASHBOARD);
}

void LauncherView::onChangeViewFinished(int currentIndex) {

    Logger::debug(TAG, "onChangeViewFinished") << "currentIndex -" << currentIndex;

    if (currentIndex == LauncherPresenter::DASHBOARD) {
        backButton->hide();
    } else if(currentIndex >= 0) {
        backButton->show();
    }
}
