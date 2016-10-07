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
#include "SlidingStackedWidget.h"

SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
        : QStackedWidget(parent) {

    //Now, initialize some private variables with default values
    isVertical = false;
    //setVerticalMode(true);
    animationSpeed = 500;
    animationType = QEasingCurve::OutBack;  //check out the QEasingCurve documentation for different styles
    nextIndex = 0;
    pointNow = QPoint(0, 0);
    isActive = false;
}

SlidingStackedWidget::~SlidingStackedWidget() {

}

void SlidingStackedWidget::showWidget(int index) {

    Direction direction = AUTOMATIC;
    if (index > count() - 1) {
        direction = isVertical ? TOP_TO_BOTTOM : RIGHT_TO_LEFT;
        index = (index) % count();
    } else if (index < 0) {
        direction = isVertical ? BOTTOM_TO_TOP : LEFT_TO_RIGHT;
        index = (index + count()) % count();
    }
    showWidget(widget(index), direction);
}

void SlidingStackedWidget::showWidget(QWidget *nextWidget, enum Direction direction) {
    if (isActive) {
        return; // at the moment, do not allow re-entrance before an animation is completed.
        //other possibility may be to finish the previous animation abrupt, or
        //to revert the previous animation with a counter animation, before going ahead
        //or to revert the previous animation abrupt
        //and all those only, if the widget is not the same as that of the previous running animation.
    } else {
        isActive = true;
    }

    nextIndex = indexOf(nextWidget);
    if (currentIndex() == nextIndex) {
        isActive = false;
        return;
    }

    if (direction == AUTOMATIC) {
        if (currentIndex() < nextIndex) {
            direction = isVertical ? TOP_TO_BOTTOM : RIGHT_TO_LEFT;
        } else {
            direction = isVertical ? BOTTOM_TO_TOP : LEFT_TO_RIGHT;
        }
    }
    //NOW....
    //calculate the shifts

    int offsetX = frameRect().width(); //inherited from mother
    int offsetY = frameRect().height();//inherited from mother

    //the following is important, to ensure that the new widget
    //has correct geometry information when sliding in first time
    widget(nextIndex)->setGeometry(0, 0, offsetX, offsetY);

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
    //re-position the nextIndex widget outside/aside of the display area
    QPoint pointNext = widget(nextIndex)->pos();
    QPoint pointNow = widget(currentIndex())->pos();

    widget(nextIndex)->move(pointNext.x() - offsetX, pointNext.y() - offsetY);
    //make it visible/show
    widget(nextIndex)->show();
    widget(nextIndex)->raise();

    //animate both, the now and nextIndex widget to the side, using animation framework
    QPropertyAnimation *animationNow = new QPropertyAnimation(widget(currentIndex()), "pos");
    animationNow->setDuration(animationSpeed);
    animationNow->setEasingCurve(animationType);
    animationNow->setStartValue(QPoint(pointNow.x(), pointNow.y()));
    animationNow->setEndValue(QPoint(offsetX + pointNow.x(), offsetY + pointNow.y()));

    QPropertyAnimation *animationNext = new QPropertyAnimation(widget(nextIndex), "pos");
    animationNext->setDuration(animationSpeed);
    animationNext->setEasingCurve(animationType);
    animationNext->setStartValue(QPoint(-offsetX + pointNext.x(), offsetY + pointNext.y()));
    animationNext->setEndValue(QPoint(pointNext.x(), pointNext.y()));

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup;
    animationGroup->addAnimation(animationNow);
    animationGroup->addAnimation(animationNext);

    connect(animationGroup, SIGNAL(finished()), this, SLOT(animationFinish()));

    isActive = true;
    animationGroup->start();

    //note; the rest is done via a init from the animation ready;
    //animationGroup->finished() provides a signal when animation is done;
    //so we init this to some post processing slot,
    //that we implement here below in animationFinish.
}

void SlidingStackedWidget::animationFinish() {

    QWidget *preWidget = currentWidget();
    emit dynamic_cast<BaseView *>(preWidget)->stop();

    int oldIndex = currentIndex();
    //when ready, call the QStackedWidget slot setCurrentIndex(int)
    setCurrentIndex(nextIndex);  //this function is inherit from QStackedWidget
    //then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
    widget(oldIndex)->hide();
    //then set the position of the outshifted widget now back to its original
    widget(oldIndex)->move(pointNow);
    //so that the application could also still call the QStackedWidget original functions/slots for changings
    //widget(oldIndex)->update();
    //setCurrentIndex(nextIndex);  //this function is inherit from QStackedWidget
    isActive = false;
    emit animationFinished();
}

void SlidingStackedWidget::setAnimationSpeed(int animationSpeed) {
    SlidingStackedWidget::animationSpeed = animationSpeed;
}

void SlidingStackedWidget::setAnimationType(QEasingCurve::Type animationType) {
    SlidingStackedWidget::animationType = animationType;
}

void SlidingStackedWidget::setIsVertical(bool isVertical) {
    SlidingStackedWidget::isVertical = isVertical;
}
