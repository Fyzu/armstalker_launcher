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

#include <src/core/base/view/BaseView.h>
#include "ViewManager.h"

ViewManager::ViewManager(QWidget *parent) : QStackedWidget(parent), BaseCore("ViewManager") {

    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy1);
    setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);
    setLineWidth(0);
}

ViewManager::~ViewManager() {

}

void ViewManager::showView(int index) {

    showView(getView(index));
}

void ViewManager::showView(BaseView *nextView, enum Direction direction) {

    if (isActive || currentView() == nextView) {
        return;
    } else {
        isActive = true;
    }

    this->nextView = nextView;

    if (direction == AUTOMATIC) {
        if (currentIndex() < indexOf(nextView)) {
            direction = isVertical ? TOP_TO_BOTTOM : RIGHT_TO_LEFT;
        } else {
            direction = isVertical ? BOTTOM_TO_TOP : LEFT_TO_RIGHT;
        }
    }

    int offsetX = frameRect().width();
    int offsetY = frameRect().height();

    nextView->setGeometry(0, 0, offsetX, offsetY);

    if (direction == BOTTOM_TO_TOP) {
        offsetX = 0;
        offsetY = -offsetY;
    } else if (direction == TOP_TO_BOTTOM) {
        offsetX = 0;
        //offsetY=offsetY;
    } else if (direction == RIGHT_TO_LEFT) {
        offsetX = -offsetX;
        offsetY = 0;
    } else if (direction == LEFT_TO_RIGHT) {
        //offsetX=offsetX;
        offsetY = 0;
    }

    QPoint pointNext = nextView->pos();
    QPoint pointNow = currentView()->pos();

    nextView->move(pointNext.x() - offsetX, pointNext.y() - offsetY);
    nextView->show();
    nextView->raise();

    QPropertyAnimation *animationNow = new QPropertyAnimation(currentView(), "pos");
    animationNow->setDuration(animationSpeed);
    animationNow->setEasingCurve(animationType);
    animationNow->setStartValue(QPoint(pointNow.x(), pointNow.y()));
    animationNow->setEndValue(QPoint(offsetX + pointNow.x(), offsetY + pointNow.y()));

    QPropertyAnimation *animationNext = new QPropertyAnimation(nextView, "pos");
    animationNext->setDuration(animationSpeed);
    animationNext->setEasingCurve(animationType);
    animationNext->setStartValue(QPoint(-offsetX + pointNext.x(), offsetY + pointNext.y()));
    animationNext->setEndValue(QPoint(pointNext.x(), pointNext.y()));

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;
    animationGroup->addAnimation(animationNow);
    animationGroup->addAnimation(animationNext);

    connect(animationGroup, SIGNAL(finished()), this, SLOT(animationFinish()));

    animationGroup->start();

    emit nextView->resume();
}

void ViewManager::animationFinish() {

    BaseView *prevView = currentView();

    emit prevView->stop();

    setCurrentWidget(nextView);

    prevView->hide();
    prevView->move(QPoint(0, 0));

    isActive = false;

    emit changeViewFinished(indexOf(nextView));
}

void ViewManager::setAnimationSpeed(int animationSpeed) {
    ViewManager::animationSpeed = animationSpeed;
}

void ViewManager::setAnimationType(QEasingCurve::Type animationType) {
    ViewManager::animationType = animationType;
}

void ViewManager::setIsVertical(bool isVertical) {
    ViewManager::isVertical = isVertical;
}

BaseView *ViewManager::getView(int index) {
    return dynamic_cast<BaseView *>(widget(index));
}

BaseView *ViewManager::currentView() {
    return dynamic_cast<BaseView *>(currentWidget());
}

void ViewManager::addView(BaseView *view) {
    addWidget(view);
}
